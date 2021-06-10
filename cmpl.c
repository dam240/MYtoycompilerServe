#include <stdio.h>
#include <string.h>
#include "model.h"


#define CEED_MAX_CODE_SIZE      0x100000        // 1MB
#define CEED_MAX_RDATA_SIZE     0x100000        // 1MB
static u32 code_pos = 0;
static pu8 code;
static u32 rdata_pos = 0;
pu8 rdata;
extern u8 itoa_code[];
extern u8 atoi_code[];
static u32 value_i=2;
sym_const indexs;
pvoid ei;




pfn_gen_exe_file gen_exe_file;
pfn_set_exe_scn set_exe_code_scn;
pfn_set_exe_scn set_exe_rdata_scn;
pfn_get_va get_code_va;
pfn_get_va get_data_va;
pfn_get_va get_rdata_va;
pfn_emit_main_init emit_main_init;
pfn_emit_main_exit emit_main_exit;
pfn_emit_write emit_write;
pfn_emit_write_reg_input emit_write_reg_input;
pfn_emit_read emit_read;

#define CEED_OP_ADD     0
#define CEED_OP_SUB     1
#define CEED_OP_GT      0
#define CEED_OP_EQ      1

#define CEED_TYPE_VAL   1
#define CEED_TYPE_ADDR  2


#define CEED_TEMP_ATOI_ITOA_BUF_ADDR    0x900



#define CEED_TEMP_ATOI_ITOA_BUF_LEN     0x10

void
chk_code_size(u32 size) //检查代码区是不是大于设的内存
{
    if ((size + code_pos) > CEED_MAX_CODE_SIZE) {
        printf("Error: Exceeded maximum CODE size of %d bytes.\n",
               CEED_MAX_CODE_SIZE);
        exit(-1);
    }
}

/*

写入机器码到代码区
*/

void
emit8(u8 i) //
{
    chk_code_size(1);
    memcpy(&code[code_pos], &i, 1);
    code_pos++;
}

void 
emit16(u16 i)
{
    chk_code_size(2);
    memcpy(&code[code_pos], &i, 2);
    code_pos += 2;
}

void 
emit32(u32 i)
{
    chk_code_size(4);
    memcpy(&code[code_pos], &i, 4);
    code_pos += 4;
}

void emit64(long i)
{
  
    chk_code_size(8);
    memcpy(&code[code_pos], &i, 8);
    code_pos += 8;
}



void 
emit32at(u32 pos, u32 i)
{
    memcpy(&code[pos], &i, 4);
}


void 
emit64at(long pos, long i)
{
    memcpy(&code[pos], &i, 8);
}



u32
add_str(pu8 str)
{
    u32 str_len;
    u32 ret_pos;

    str_len = strlen(str);
	printf("%s-- %d\n",str,str_len);
    str[str_len - 1] = '\0'; 
    if ((rdata_pos + str_len) > CEED_MAX_RDATA_SIZE) {//数据多于设置的data区就失败
        printf("Error: Exceeded maximum RDATA size of %d bytes.\n",
               CEED_MAX_RDATA_SIZE);
        exit(-1);
    }
    strcpy(&rdata[rdata_pos], str);  //把字符串复制到data区,
    ret_pos = rdata_pos; //取字符串的开始位置
    rdata_pos += str_len;//移到一个准备开始位置，等一次
    return ret_pos;
}

long
add_str64(pu8 str)
{
    long str_len;
    long ret_pos;

    str_len = strlen(str);
	printf("%s-- %d\n",str,str_len);
    str[str_len - 1] = '\0'; 
    if ((rdata_pos + str_len) > CEED_MAX_RDATA_SIZE) {//数据多于设置的data区就失败
        printf("Error: Exceeded maximum RDATA size of %d bytes.\n",
               CEED_MAX_RDATA_SIZE);
        exit(-1);
    }
    strcpy(&rdata[rdata_pos], str);  //把字符串复制到data区,
    ret_pos = rdata_pos; //取字符串的开始位置
    rdata_pos += str_len;//移到一个准备开始位置，等一次
    return ret_pos;
}

void emit_prologx64(){ //64 位机器分配函数的堆栈机器码
	 emit8(0x55); // push rbp
	  emit8(0x48); // mov rsp ,rbp
	   emit8(0x89);
	    emit8(0xe5);
		
		 emit8(0x48);  //sub rsp,0x1000
		  emit8(0x81);
		   emit8(0xec);
		    emit8(0x00);
			  emit8(0x10);
		    emit8(0x00);
		 emit8(0x00);
}



void 
emit_prolog() //32 位机器分配函数的堆栈机器码
{
    // push ebp
    emit8(0x55);

    // mov ebp, esp
    emit8(0x89);
    emit8(0xe5);

    // sub esp, (26 * 4)
    emit8(0x83);
    emit8(0xec);
    emit8(26 * 4);
}


void 
emit_epilog_commonx64()
{
    // mov esp, ebp
//emit8(0x48);
  // emit8(0x89);
    //emit8(0xe5);

    // pop ebp
   emit8(0xc9);
 //emit8(0x5d);
emit8(0xc3);
}


void 
emit_epilog_common()
{
    // mov esp, ebp
    emit8(0x89);
    emit8(0xec);

    // pop ebp
    emit8(0x5d);

}

void 
emit_epilog() //出栈还原和返回操作
{
    emit_epilog_common();

    // ret
    emit8(0xc3);
}

void 
emit_epilog_final() 
{
    emit_epilog_commonx64();
    emit_main_exit();
	//emit8(0xc3);
}

int  testshow(){


	
char haed[]={0x55,0x48,0x89,0xe5,0x48,0x83,0xec,0x30,  //对应==test (){ char d[]="111"; printf("%s \n",d);  }
0xc6,0x45,0xa0, 0x31,
0xc6,0x45,0xa1,0x31,
0xc6,0x45,0xa2,0x31,
0xc6,0x45,0xa3,0x0a,
0x48,0xc7,0xc0,0x01,0x00,0x00,0x00, 
0x48, 0xc7,0xc7,0x01,0x00,0x00,0x00, 
0x48, 0x8d, 0x4d,0xa0,
0x48, 0x89,0xce,
0x48, 0xc7,0xc2,0x0d,0x00,0x00,0x00, 
0x0f,0x05,
 0xc9,
0xc3,
};
int size=sizeof(haed);

for(int i=0;i<size;i++){
	
	 emit8(haed[i]);
}
	
	
	   /*
		 emit8(0x45);
		 emit8(0xa0);
		  emit8(0x31);
		  
		    emit8(0xc6);
			 	 emit8(0x45);
		 emit8(0xa1);
		  emit8(0x31);
		  
	*/
	return size;
	
}

void showhello(){ 
	
   //emit_epilog_common();
  
	printf("====4442\n");
	char i2[]="hello---------\r\0";
	   emit_write_str_da(i2);
	   char i1[]="----da-------\0";
	    emit_write_str_da(i1);
	 char i4[]={0x0A};
	     emit_write_str_da(i4);
   
	
}

u32 
emit_var(sym *p)
{
   if (p->ident.index >= 0 && p->ident.index <= 25) {
       // Local variable.

       // mov ecx, ebp
       emit8(0x89);
       emit8(0xe9);

       // sub ecx, x
       emit8(0x83);
       emit8(0xe9);
       emit8((p->ident.index + 1) * 4);
   } else if (p->ident.index >= 26 && p->ident.index <= 51) {
       
       emit8(0xb9);
       emit32(get_data_va(ei) + ((p->ident.index - 26) * 4));
   }
   return CEED_TYPE_ADDR;
}

u32 
emit_const(sym *p)
{
    // Mov eax, imm32
    emit8(0xb8);
    emit32(p->con.value);
    return CEED_TYPE_VAL;
}


//void  emit_if_else






void 
emit_arith(sym *p, int sym_list)
{
    emit_expr_val(p->stmt.sym_list[1]);
    
    // push eax
    emit8(0x50);

    emit_expr_val(p->stmt.sym_list[0]);

    // pop ebx
    emit8(0x5b);

    if (sym_list == CEED_OP_ADD) {
        // add eax, ebx
        emit8(0x01);
        emit8(0xd8);
    } else {
        // sub eax, ebx
        emit8(0x29);
        emit8(0xd8);
    }
}

void 
emit_logical(sym *p, int sym_list)
{
    emit_expr_val(p->stmt.sym_list[1]);

    // Push eax
    emit8(0x50);

    emit_expr_val(p->stmt.sym_list[0]);

    // pop ebx
    emit8(0x5b);

    // cmp eax, ebx
    emit8(0x39);
    emit8(0xd8);

    if (sym_list == CEED_OP_GT) {
        // jg 0x4
        emit8(0x7f);
        emit8(0x4);
    } else {
        // je 0x4
        emit8(0x74);
        emit8(0x4);
    }
    
    // xor eax, eax
    emit8(0x31);
    emit8(0xc0);

    // jmp 0x5
    emit8(0xeb);
    emit8(0x5);

    // mov eax, 1
    emit8(0xb8);
    emit32(0x1);
}

void 
emit_set_var(sym *p)
{
    u8 tmp;
    u8 id = p->stmt.sym_list[0]->ident.index;

  
    emit_expr_val(p->stmt.sym_list[1]);


    if (id >= 0 && id <= 25) {
        // mov [ebp + tmp], eax
        tmp = (0 - ((id + 1) * 4));
        emit8(0x89);
        emit8(0x45);
        emit8(tmp);
    } else if (id >= 26 && id <= 51) {
       
        emit8(0xa3);
        emit32(get_data_va(ei) + ((id - 26) * 4));
    } else {
        printf("Error: Unexpected identifier: %d\n", id);
        exit(-1);
    }
}



void 
emit_func_call(sym *p)
{ 
	
    int val = func[1];

    // mov eax, <func_addr>
    emit8(0xb8);
    emit32(val + get_code_va(ei));

    // call eax
    emit8(0xff);
    emit8(0xd0);
}


void 
emit_func_call64(int up)
{
//  0000000  0000000000000000  0000000000000005	

	 emit8(0xe8);
    if(up==0){
	int  val=code_pos+4; //code_pos的位置是0xe8 再加遍移4个格内存 向前面的函数直接调取地址
	int bin=0xfffffffe;//上
	bin=bin-val+2;
    emit32(bin);
		printf("emit_func_call64=%#x  \n",bin);
	}else{
		//20-8
	   
	int  val=func[1]-code_pos; //调用函数地址减掉现在地址  向后面的函数直接call
	//int bin=0x0;//下
	emit32(val);
	//bin=bin-val+2;
	
	}

    // call eax
    //emit8(0xff);
    //emit8(0xd2);
}
int ins;

void 
emit_func_def(sym *p) //32位——64位 x86 测试生成机器码和生成可执行程序，测试功能：call  ，打印,退出
{
    u32 fn_id=p->ident.index; 

    // fn_id = p->stmt.sym_list[0]->ident.index - 52; //这个是计算现在生成的函数的下标,如果是第二个，id=1，如果是最后一个就是0，就是main程序入口
    printf("fn_id =%d \n",fn_id);
    func[fn_id] = code_pos;
	//printf()
    //
    // Generate actual function code.
    //
  // emit_code(p->stmt.sym_list[1]);
//0 就是main程序入口，不是0就其他函数  
    if (fn_id == 0) { //程序入口是不需要自己分配堆栈，因为操作系统分，我们编译器只分其他函数的堆栈
		printf("-----2 \n");
		//main方法必须是编译器自己加在程序最后退出，不然一直循环直到系统分的内存完
		//testshow();
	// showhello();
	//  emit8(0xc9);
		// emit8(90);
       // testshow();
	 //  emit_prologx64();
	// emit_prologx64();
       
		// emit_epilog();
		 //emit_main_exit();
		     emit_func_call64(0);
	    //showhello();
		 showhello();
		emit_main_exit(); 
	  
		// emit8(0xc3);
		printf("--222---2 \n");
    } else {
       
	      emit_prologx64();
		//testshow();
		  showhello();
		 emit_epilog_commonx64();
			printf("-----5 \n");
	    //showhello();
		
	//   testshow();
		
    }
}



void 
emit_write_str(sym *p)
{
	printf("emit_write_str   %s  %d\n ",rdata, strlen(rdata+3));
    u32 str_len;
    str_len = strlen(rdata + p->con.value);
		printf("str_len %d  %d\n ", p->con.value,str_len);

		
    emit_write(get_rdata_va(ei) + p->con.value, str_len);
    // printf("emit_write: %x, %d\n", get_rdata_va(ei) + p->con.value, str_len);
}




void emit_write_str_da(char * str)
{	printf("emit_write_str_da  \n");
	
			
   u32 buf_addr=	add_str(str); //返回数据位置
   u32 str_len;
    str_len =  strlen(rdata + value_i); 
    emit_write(get_rdata_va(ei) + buf_addr, str_len);
	value_i+=str_len+1;

   	printf("1\n");
	 

   //	printf("elf_emit_main_exit==11= %x \n",buf_addr);
   
   
//  elf_emit_write(buf_addr,0x05);
}


void 
emit_write_int()
{
   

    // mov ebx, itoa_buf
    emit8(0xbb);
    emit32(get_data_va(ei) + CEED_TEMP_ATOI_ITOA_BUF_ADDR);

    // mov ecx, <func_addr> (itoa)
    emit8(0xb9);
    emit32(get_code_va(ei));

    // call ecx
    emit8(0xff);
    emit8(0xd1);

  

    emit_write_reg_input();
}

void 
emit_read_int()
{
    
    emit16(0x05c6);
    emit32(get_data_va(ei) + CEED_TEMP_ATOI_ITOA_BUF_ADDR);
    emit8(0x0);

    emit_read(get_data_va(ei) + CEED_TEMP_ATOI_ITOA_BUF_ADDR,
              CEED_TEMP_ATOI_ITOA_BUF_LEN);

    // mov ebx, buf_addr
    emit8(0xbb);
    emit32(get_data_va(ei) + CEED_TEMP_ATOI_ITOA_BUF_ADDR);

    // mov ecx, <func_addr> (atoi)
    emit8(0xb9);
    emit32(get_code_va(ei) + 0x80);

    // call ecx
    emit8(0xff);
    emit8(0xd1);
}






void 
gen_exe()
{  
  sym_ident inte;
  inte.index=1;

 sym *p=malloc(sizeof(sym));
   p->type=sym_typ_stmt;
   p->ident=inte;
	emit_func_def(p);
    p->ident.index=0;
 
	emit_func_def(p);
	
	 printf("============444======\n");
    set_exe_code_scn(ei, code, code_pos);
    set_exe_rdata_scn(ei, rdata, rdata_pos);
        // code = malloc(CEED_MAX_CODE_SIZE);
		 	printf("==========2========\n");

	 printf("============222======\n");
    gen_exe_file(ei);
}

void
cmplr_init()
{
    code = malloc(CEED_MAX_CODE_SIZE);
    rdata = malloc(CEED_MAX_RDATA_SIZE);

    if (code == NULL || rdata == NULL) {
        printf("Insufficient memory.\n");
        exit(-1);
    }

    memset(code, 0, CEED_MAX_CODE_SIZE);
    memset(rdata, 0, CEED_MAX_RDATA_SIZE);

  
    rdata[0] = '\n';
    rdata_pos = 2;


    
   // memcpy(code, itoa_code, 0x80);
    //code_pos += 0x80;
    //memcpy(&code[code_pos], atoi_code, 0x80);
   // code_pos += 0x80;
}

