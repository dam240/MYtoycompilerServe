#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
int add(char * b){
char * p=b;
printf("%s ",p);
return 10;
}



void ss(){
char s[2]={0};
int y=add(s);
printf("%d \n",y);
}

void ys()
{
char funCode[] ={0x55,0x48,0x89,0xe5,0x48,0x89,0x7d,0xf8,0xb8,0x09,0x00,0x0,0x00,0x5d,0xc3};

char *d=funCode;

}


int tesh(int b){
char funCode[] ={0x55,0x48,0x89,0xe5,0x48,0x89,0x7d,0xf8,0xb8,0x09,0x00,0x0,0x00,0x5d,0xc3};
   int (*Fun)(int);  
   Fun =funCode;
return Fun(b);
}


unsigned char machineCode[] ={0x55,0x48,0x89,0xe5,0x48,0x89,0x7d,0xf8,0xb8,0x0a,0x00,0x0,0x00,0x5d,0xc3};

// 第一种执行方式  
void  mone()  
{  
    int result;  
      
    int (*Fun)(int);  
    Fun = (void*)machineCode;  
      
    result = Fun(7);  
      
    printf("%d dydddddd\n",result);  
}  

// 第二种执行方式  
void  mac_two()  
{  
    int result;  
      
    typedef int(*Fun)(int);  
    Fun p=NULL;  
      
    p = (Fun)machineCode;  
      
    result = p(7);  
      
    printf("%d/r/n",result);  
}  
  
  
// 第三种执行方式  
void  mac_three()  
{  
    int result;  
      
    result = (  ( int (*)(int) ) machineCode )(7);  
      
    printf("%d \n",result);  
}  




char  * readfile(char * filename){ 


        int r_id=open(filename,O_RDWR);
	 if(r_id==-1){
            printf("找不到文件\n");       
           return NULL;
        }

	 char * index=(char *)malloc(2048);
           
      int  r=read(r_id,index,2048);


       
     if(r==-1){
    printf("clsee--> %s\n",filename);
		
    return NULL;
    }

    if(close(r_id)==-1){
     printf("clsee--> %s\n",filename);
     }

	 return index;


}


char endian(){
unsigned ui=~0-1;
return ((*(unsigned char*)&ui==0xfe)?'L':'B');

}

char * addressConvert(char * txt){
	   
   printf("%p\n",txt);
	char x[6];
int little_loop=0,inx;
int *op=txt;
if(endian()=='L'){
for(inx=5;inx>=0;--inx,++little_loop)
x[little_loop]=*((unsigned char *)&op+inx);



}else{

for(inx=0;inx!=6;++inx)
x[inx]=*((unsigned char *)&op+inx);

}

	int i=0; 
   for(;i<=3;i++){
 printf("%#x   ",x[i]);     
   }
 return  x;
}


int main(){
printf("%p \n",main);

printf("hello \n");
/*
int i=2;
char dg[200];
char id[]="ddhdhydyeeeeeedydydd";
char * bs=readfile("conf.txt");
printf("%s  %d \n",bs,strlen(bs));
char sd[]="call sdd";
sprintf(dg, "call %s",bs);
printf("%s   \n",dg);
asm("lea -0x30(%rbp),%rax; mov %rax,%rdi;");
asm("call ios");
add(id);
*/
char funCode[] ={0x55,0x48,0x89,0xe5,0x48,0x83,0xec,0x30,
0x48,0x89,0x7d,0xd8,
0x48,0x8b,0x55,0xd8,
 0xb8,0x00,0x00,0x00,0x00,
0xff,0xd2,   
 0xb8,0x08,0x00,0x00,0x00,
0xc9,0xc3
};

//{0x55,0x48,0x89,0xe5,0x48,0x89,0x7d,0xf8,0xb8,0x08,0x00,0x0,0x00,0x5d,0xc3};
char codes[17];

int k=0;
int osd=sizeof(funCode);
 printf("  %d  ",osd);
for(;k<9;k++){
codes[k]=funCode[k];
 printf("%#X   %d  ",funCode[k],k);

}
 printf("\n   ");

if(k!=9)
k=9;
codes[k]=0xe8;
k++;



char haed[]={0x55,0x48,0x89,0xe5,0x48,0x83,0xec,0x30,  //对应==test (){ char d[]="111"; printf("%s \n",d);  }
0xc6,0x45,0xa0, 0x31,
0xc6,0x45,0xa1,0x31,
0xc6,0x45,0xa2,0x31,
0xc6,0x45,0xa3,0x0a,
0x48, 0xc7,0xc0,0x01,0x00,0x00,0x00, 
0x48, 0xc7,0xc7,0x01,0x00,0x00,0x00, 
0x48, 0x8d, 0x4d,0xa0,
0x48, 0x89,0xce,
0x48, 0xc7,0xc2,0x0d,0x00,0x00,0x00, 
0x0f,0x05,
 0xc9,
0xc3,
};






int i=0,size=strlen(funCode);

    void *mem = mmap(NULL, sizeof(haed), PROT_WRITE | PROT_EXEC,MAP_ANON | MAP_PRIVATE, -1, 0);

        memcpy(mem, haed, sizeof(haed));
   char * ip=addressConvert(mem);
 void *mem2 = mmap(NULL, sizeof(funCode), PROT_WRITE | PROT_EXEC,MAP_ANON | MAP_PRIVATE, -1, 0);
        memcpy(mem2,funCode, sizeof(funCode));
 printf("机器码写的函数 begin \n");

 int (*Fun)();  
 int (*Fum)();  
 Fun = (void*)mem;  
int a=2;
int b=65;
//a=a+b;
Fun();

char  funCodes[]={0x55,0x48,0x89,0xe5,0x48,0x83,0xec,0x30,       //机器码对应的c代码  = int a(int i){return 15}   int  b(){return a(7); }   
0xc6,0x45,0xa0,0x55,
0xc6,0x45,0xa1,0x48,
0xc6,0x45,0xa2,0x89,
0xc6,0x45,0xa3,0xe5,
0xc6,0x45,0xa4,0x48,
0xc6,0x45,0xa5,0x89,
0xc6,0x45,0xa6,0x7d, 
0xc6,0x45,0xa7,0xf8,
0xc6,0x45,0xa8,0xb8,
0xc6,0x45,0xa9,0x0f,
0xc6,0x45,0xaa,0x00,
0xc6,0x45,0xab,0x00,
0xc6,0x45,0xac,0x00,
0xc6,0x45,0xad,0x5d,
0xc6,0x45,0xae,0xc3,
0x48, 0x8d, 0x45,0xa0,
0xbf, 0x07,0x00,0x00,0x00,
0xff,0xd0,
0xc9,
0xc3 };
mone();
//free(mem);
//void *mem3 = mmap(NULL, sizeof(haed2), PROT_WRITE | PROT_EXEC,MAP_ANON | MAP_PRIVATE, -1, 0);

      //  memcpy(mem3, haed2, sizeof(haed2));
 Fun = (void*)mem2;  
a=Fun(mem);
//tesh(20);

//Fum =(void*)funCodes; 
//a=0;
//a=Fum();
printf("%d  \n",a);

 printf("机器码写的函数 end \n");
return 0;
}