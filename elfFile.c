
#include "elfFile.h"




void out_elf_header(FILE *fp, uintptr_t entry, int phnum, int shnum) {
  Elf64_Ehdr ehdr = {
    .e_ident     = { ELFMAG0, ELFMAG1, ELFMAG2 ,ELFMAG3,
                     ELFCLASS64, ELFDATA2LSB, EV_CURRENT, ELFOSABI_SYSV },
    .e_type      = phnum > 0 ? ET_EXEC : ET_REL,
    .e_machine   = EM_X86_64,
    .e_version   = EV_CURRENT,
    .e_entry     = entry,
    .e_phoff     = phnum > 0 ? sizeof(Elf64_Ehdr) : 0,
    .e_shoff     = 0, // dummy
    .e_flags     = 0x0,
    .e_ehsize    = sizeof(Elf64_Ehdr),
    .e_phentsize = phnum > 0 ? sizeof(Elf64_Phdr) : 0,
    .e_phnum     = phnum,
#if !defined(__NO_ELF_OBJ)
    .e_shentsize = shnum > 0 ? sizeof(Elf64_Shdr) : 0,
#else
    .e_shentsize = 0,
#endif  // !defined(__NO_ELF_OBJ)
    .e_shnum     = shnum,
    .e_shstrndx  = shnum > 0 ? shnum - 1 : 0,
  };
//  printf("shnum=%d entry =%ld\n",shnum,entry);
  fwrite(&ehdr, sizeof(Elf64_Ehdr), 1, fp);
}

void out_program_header(FILE *fp, int sec, uintptr_t offset, uintptr_t vaddr, size_t filesz,
                        size_t memsz) {
  static const int kFlags[] = {
    PF_R | PF_X,  // code
    PF_R | PF_W,  // rwdata
  };
 // printf("out_program_header-------------------%ld,--------%ld,%ld,--------%ld\n",offset,vaddr,filesz,memsz);
  Elf64_Phdr phdr = {
    .p_type   = PT_LOAD,
    .p_offset = offset,//
    .p_vaddr  = vaddr, //起START_ADDRESS
    .p_paddr  = 0, // dummy
    .p_filesz = filesz,//代码加常量一共多少字节
    .p_memsz  = memsz,//代码加常量一共多少字节
    .p_flags  = kFlags[sec],
    .p_align  = 0x10,
  };




  fwrite(&phdr, sizeof(Elf64_Phdr), 1, fp);
}




static void put_padding(FILE *fp, uintptr_t  start) {
	//printf("put_padding----------------\n");
  long cur =ftell(fp);
//  printf("cur=== %ld  ",cur);
  if (start > (size_t)cur) {
    size_t size = start-(uintptr_t)cur;
    char *buf = calloc(1, size);
	printf("%s %ld ",buf,size);
    fwrite(buf, size, 1, fp);
	//IntToChars(size,buf);
    free(buf);
  }
  //	printf("--------\n");
}



void outfile(char * name){


	
 ir_asm(name);




 FILE *fp;
 //char name[]="hooo";

    fp = fopen("b.out", "wb");
    if (fp == NULL) {
      printf( "Failed to open output file: \n");
      return 1;
    }

int i=0;


for(;i<arcs->code_len;i++){
	
	printf(" %x ",arcs->code[i]);
}
printf("   \n");

for(i=0;i<arcs->rdate_len;i++){
	
	printf(" %x ",arcs->rdate[i]);
}
printf("   \n");

printf("  %d  %d \n",arcs->rdate_len,arcs->code_len);
int rdates=arcs->code_len+arcs->rdate_len;

//int rdates=sizeof(code)+sizeof(date); //总共字节数
//uintptr_t addrt=START_ADDRESS+haed[0];
//printf("  %d  %d \n",sizeof(code),sizeof(date));
out_elf_header(fp,START_ADDRESS,2,0); //设置开始位置

out_program_header(fp, 0, PROG_START, START_ADDRESS, rdates, rdates);
//printf("%ld  \n ",addrt);
put_padding(fp,PROG_START);
//fwrite(code, sizeof(code), 1, fp);

fwrite(arcs->code, arcs->code_len, 1, fp);
//put_padding(fp,RDATA_ADDRESS);
//put_padding(fp,PROG_START);
//fwrite(date, sizeof(date), 1, fp);

fwrite(arcs->rdate, arcs->rdate_len, 1, fp);

 fclose(fp);

  if (chmod(name, 0755) == -1) {
    perror("chmod failed\n");
    return 1;
  }



}
