#include <stdio.h>
#include <string.h>
#include <stdlib.h>>
#include <errno.h>
#include "model.h"
#include <elf.h>


typedef struct _section_info64
{
    Elf64_Phdr scn_hdr;
    pu8 scn_data;
    long scn_size;
    long scn_file_size;
    long scn_file_offset;
    long scn_virtual_size;
} section_info64, *psection_info64;



typedef struct _exe_info64
{
    psection_info64 data_scn; // 全局区
    psection_info64 code_scn; //代码区
    psection_info64 rdata_scn; //常量区

    Elf64_Ehdr eh;
    long scn_count;
    psection_info64 scn_list[CEED_MAX_SECTION_COUNT];
} exe_info64, *pexe_info64;



void
elf_write_hdr64(pexe_info64 ei, FILE *file)
{
    u32 i;
    i = 0;

    ei->eh.e_ident[i++] = ELFMAG0;
    ei->eh.e_ident[i++] = ELFMAG1;
    ei->eh.e_ident[i++] = ELFMAG2;
    ei->eh.e_ident[i++] = ELFMAG3;
    ei->eh.e_ident[i++] = ELFCLASS64;       // EI_CLASS
    ei->eh.e_ident[i++] = ELFDATA2LSB;      // EI_DATA
    ei->eh.e_ident[i++] = EV_CURRENT;       // EI_VERSION
    ei->eh.e_ident[i++] = ELFOSABI_SYSV;    // EI_OSABI

	
    ei->eh.e_type = ET_EXEC;
    ei->eh.e_machine = EM_X86_64;
    ei->eh.e_version = EV_CURRENT;

    ei->eh.e_phoff =  sizeof(Elf64_Ehdr);
    ei->eh.e_ehsize = sizeof(Elf64_Ehdr);
    ei->eh.e_phentsize = sizeof(Elf64_Phdr);
    ei->eh.e_shentsize = sizeof(Elf64_Ehdr);
    ei->eh.e_shoff=0;
    ei->eh.e_flags=0x0;
    ei->eh.e_phnum = ei->scn_count;
    ei->eh.e_entry = CEED_CODE_SECTION_VA + func[0];
	fwrite(&ei->eh, sizeof(Elf64_Ehdr), 1, file);
	
	printfd1(&ei->eh);


    
}




void elf_header64(FILE *fp,  int phnum, int shnum) {
  Elf64_Ehdr ehdr = {
    .e_ident     = { ELFMAG0, ELFMAG1, ELFMAG2 ,ELFMAG3,
                     ELFCLASS64, ELFDATA2LSB, EV_CURRENT, ELFOSABI_SYSV },
    .e_type      =  ET_EXEC,
    .e_machine   = EM_X86_64,
    .e_version   = EV_CURRENT,
    .e_entry     = CEED_CODE_SECTION_VA + func[0],
    .e_phoff     =  sizeof(Elf64_Ehdr),
    .e_shoff     = 0, // dummy
    .e_flags     = 0x0,
    .e_ehsize    = sizeof(Elf64_Ehdr),
    .e_phentsize =  sizeof(Elf64_Phdr),
    .e_phnum     = phnum,
    .e_shentsize = sizeof(Elf64_Shdr),
    .e_shnum     = shnum,
    .e_shstrndx  = shnum > 0 ? shnum - 1 : 0,
  };
  fwrite(&ehdr, sizeof(Elf64_Ehdr), 1, fp);
}



psection_info64 
elf_new_section64(pexe_info64 ei, long scn_va, long attr) //创建区的内存
{
    psection_info64 si = malloc(sizeof(section_info64));
    memset(si, 0, sizeof(section_info64));
    si->scn_hdr.p_type = PT_LOAD;
    si->scn_hdr.p_flags = attr;
    si->scn_hdr.p_vaddr = scn_va;
    si->scn_hdr.p_align = CEED_SECTION_ALIGN;
    ei->scn_list[ei->scn_count++] = si;
    return si;
}



pvoid
elf_alloc_exe_info64()//创建data ,rodata,code 的区的内存
{
    pexe_info64 ei = malloc(sizeof(exe_info64));
    memset(ei, 0, sizeof(exe_info64));

  ei->data_scn = elf_new_section64(ei, CEED_DATA_SECTION_VA, PF_R | PF_W);
    ei->code_scn = elf_new_section64(ei, CEED_CODE_SECTION_VA, PF_X | PF_R);
    ei->rdata_scn = elf_new_section64(ei, CEED_RDATA_SECTION_VA,  PF_R);

    return ei;
}



pvoid
elf_set_scn64(psection_info64 si, pu8 scn_data, long scn_size)
{
    si->scn_data = scn_data;
    si->scn_size = scn_size;
    si->scn_virtual_size = round_up(scn_size, CEED_SECTION_ALIGN);
    si->scn_file_size = round_up(scn_size, CEED_FILE_ALIGN);

    si->scn_hdr.p_memsz = si->scn_virtual_size;
    si->scn_hdr.p_filesz = si->scn_file_size;
    return NULL;
}



pvoid
elf_set_exe_code_scn64(pvoid einfo, pu8 scn_data, long scn_size)
{
    pexe_info64 ei = einfo;
		printf("elf_set_exe_code_scn64===%d\n",scn_size);
    return elf_set_scn64(ei->code_scn, scn_data, scn_size);
}

pvoid
elf_set_exe_data_scn64(pvoid einfo, pu8 scn_data, long scn_size)
{		printf("elf_set_exe_data_scn64===%d\n",scn_size);

    pexe_info64 ei = einfo;
    return elf_set_scn64(ei->data_scn, scn_data, scn_size);
}

pvoid
elf_set_exe_rdata_scn64(pvoid einfo, pu8 scn_data, long scn_size)
{
    pexe_info64 ei = einfo;
		printf("elf_set_exe_rdata_scn64===%d\n",scn_size);
    return elf_set_scn64(ei->rdata_scn, scn_data, scn_size);
}

u32
elf_get_code_va64(pvoid einfo)
{
    return CEED_CODE_SECTION_VA;
}

u32
elf_get_data_va64(pvoid einfo)
{
    return CEED_DATA_SECTION_VA;
}

u32
elf_get_rdata_va64(pvoid einfo)
{
    return CEED_RDATA_SECTION_VA;
}



void
elf_write_prg_hdrs64(pexe_info64 ei, FILE *file)
{
    long hdr_size;
    long cur_offset;

    hdr_size = sizeof(Elf64_Ehdr) + (sizeof(Elf64_Phdr) * ei->scn_count);
    cur_offset = hdr_size;
	printf("elf_write_prg_hdrs64   cur_offset= %d\n",cur_offset);
    for (int i = 0; i < ei->scn_count; i++)
    {
        psection_info64 si = ei->scn_list[i];
        cur_offset = round_up(cur_offset, CEED_SECTION_ALIGN);
        si->scn_hdr.p_offset = cur_offset;
        cur_offset += si->scn_virtual_size;
		 fwrite(&si->scn_hdr, sizeof(Elf64_Phdr), 1, file);
        // printfd2(&si->scn_hdr);
	printf("\n");
		printf("elf_write_prg_hdrs64 end   cur_offset= %d\n",cur_offset);

    }
}


void
elf_write_section_data64(psection_info64 si, FILE *file)
{
    fseek(file, si->scn_hdr.p_offset, SEEK_SET);
    fwrite(si->scn_data, si->scn_file_size, 1, file);
     printf("elf_write_section_data64   p_offset= %d\n",si->scn_hdr.p_offset);

   // int len=strlen(si->scn_data);
/*
for(int i=0;i<si->scn_file_size;i++){
	printf("%#x ",si->scn_data);
	si->scn_data++;
}
	printf("\n");
	*/

}




u8 data_buffer[4096];
#define CEED_MAX_VARIABLES  26
void
elf_gen_data_section64(pexe_info64 ei)
{
    //
    // Only 26 global variables of 4-byte int size are supported.
    //
    elf_set_exe_data_scn64(ei, data_buffer, (CEED_MAX_VARIABLES * 4)); 
}


void
elf_gen_exe_file64(pvoid einfo)
{
    pexe_info64 ei = einfo;
    FILE *exe_file;

    if (func[0] == -1)
    {
        printf("Entry point function '_a' not found.\n");
        exit(-1);
    }
    char namess[]="b.out";
    exe_file = fopen(namess, "wb+");
    if (exe_file == NULL)
    {
        printf("Failed to create output file (a.exe).\n");
        exit(errno);
    }

    elf_gen_data_section64(ei);
    elf_write_hdr64(ei, exe_file);
    elf_write_prg_hdrs64(ei, exe_file);
	
    for (int i = 0; i < ei->scn_count; i++)
    {  
        psection_info64 si = ei->scn_list[i];
        elf_write_section_data64(si, exe_file);
    }

  if (chmod(namess, 755) == -1) {
    printf("chmod failed\n");
  }

    fclose(exe_file);
}





void program_header64(FILE *fp, int sec, long offset, long vaddr, long filesz,
                        long memsz) {
  static const int kFlags[] = {
    PF_R | PF_X,  // code
    PF_R | PF_W,  // rwdata
  };
  printf("program_header64-------------------%ld,--------%ld,%ld,--------%ld\n",offset,vaddr,filesz,memsz);
  Elf64_Phdr phdr = {
    .p_type   = PT_LOAD,
    .p_offset = offset,
    .p_vaddr  = vaddr,
    .p_paddr  = 0, // dummy
    .p_filesz = filesz,
    .p_memsz  = memsz,
    .p_flags  = kFlags[sec],
    .p_align  = 0x10,
  };




  fwrite(&phdr, sizeof(Elf64_Phdr), 1, fp);
}








void
elf_emit_main_init64()
{
}

void
elf_emit_main_exit64()
{
	
	printf("elf_emit_main_exit64===\n");
	
  // 	printf("elf_emit_main_exit==ss=\n");
	// emit8(0x5d);
	 //emit8(0xc3);
	
    // mov ebx, eax     // set return code
	//  4000cf:	48 c7 c0 3c 00 00 00 	mov    $0x3c,%rax
 // 4000d6:	48 c7 c7 00 00 00 00 	mov    $0x0,%rdi
 // 4000dd:	0f 05                	syscall 

    emit8(0x48);
    emit8(0xc7);
    emit8(0xc0);
    emit8(0x3c);
    emit8(0x00);
    emit8(0x00);
     emit8(0x00);


    emit8(0x48);
    emit8(0xc7);
    emit8(0xc7);
    emit8(0x00);
    emit8(0x00);
    emit8(0x00);
   emit8(0x00);



   
    // int 0x80         // invoke syscall
    emit8(0x0f);
    emit8(0x05);
	
	   	printf("elf_emit_main_exit64==4dd44=\n");
}



void
elf_emit_write_reg_input64()
{  	printf("elf_emit_write_reg_input64===\n");
	//48 c7 c0 01 00 00 00 	mov    $0x1,%rax
  //4000b7:	48 c7 c7 01 00 00 00 	mov    $0x1,%rdi

   //mov rax , 1
     emit8(0x48);
      emit8(0xc7);
	  emit8(0xc0);
	   emit32(0x01);
    // mov rdi, 1 (stdout)
  
        emit8(0x48);
       emit8(0xc7);
	   emit8(0xc7);
	    emit32(0x01);
  

    // int 0x80 中断 
    emit8(0x0f);
    emit8(0x05);
}

void
elf_emit_write64(int buf_addr, int buf_len)
{
	printf("elf_emit_write64   \n");
	
    // mov rsi, buf_addr
	//48 c7 c6
    emit8(0x48); 
	 emit8(0xc7);
	emit8(0xc6);
     emit32(buf_addr);

    // mov rdx, str_addr
		//48 c7 c2 0c 00 00 00 	
		//48 c7 c6
    emit8(0x48);
	 emit8(0xc7);
		 emit8(0xc2);
  //  emit8(0xb9);
    // emit32(0x9049000 + p->con.value);
    emit32(buf_len);

    elf_emit_write_reg_input64();
		printf("elf_emit_write64  1 \n");
}

void
elf_emit_read64(long  buf_addr, long buf_len)
{
    // mov edx, buf_len
    emit8(0xba);
    emit32(buf_len);

    // mov ecx, buf_addr
    emit8(0xb9);
    emit32(buf_addr);

    // mov ebx, 0 (stdin)
    emit8(0xbb);
    emit32(0x0);

    // mov eax, 3 (syscall_read)
    emit8(0xb8);
    emit32(0x3);

    // int 0x80
    emit8(0xcd);
    emit8(0x80);

}
int sddddd;





void
elf_init64()
{
    ei = elf_alloc_exe_info64();
    gen_exe_file = elf_gen_exe_file64;
    set_exe_code_scn = elf_set_exe_code_scn64;
    set_exe_rdata_scn = elf_set_exe_rdata_scn64;
    get_code_va = elf_get_code_va64;
    get_data_va = elf_get_data_va64;
    get_rdata_va = elf_get_rdata_va64;
    emit_main_init = elf_emit_main_init64;
    emit_main_exit = elf_emit_main_exit64;
    emit_write = elf_emit_write64;
    emit_write_reg_input = elf_emit_write_reg_input64;
    emit_read = elf_emit_read64;
}











