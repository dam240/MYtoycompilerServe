#include <stdio.h>
#include <string.h>
#include <stdlib.h>>
#include <errno.h>
#include "model.h"
#include <sys/stat.h>
#define EI_NIDENT   16

typedef struct { 
    u8 e_ident[EI_NIDENT];
    u16 e_type;
    u16 e_machine;
    u32 e_version;
    u32 e_entry;
    u32 e_phoff;
    u32 e_shoff;
    u32 e_flags;
    u16 e_ehsize;
    u16 e_phentsize;
    u16 e_phnum;
    u16 e_shentsize;
    u16 e_shnum;
    u16 e_shstrndx;
} Elf32_Ehdr;



#define EH_SIZE         52
#define EI_MAG0         0x7F
#define EI_MAG1         'E'
#define EI_MAG2         'L'
#define EI_MAG3         'F'
#define ELFCLASS32      0x1
#define ELFDATA2LSB     0x1
#define EV_CURRENT      0x1
#define ELFOSABI_NONE   0x0
#define ET_EXEC         0x2
#define EM_386          0x3

typedef struct {
	u32 p_type;
	u32 p_offset;
	u32 p_vaddr;
	u32 p_paddr;
	u32 p_filesz;
	u32 p_memsz;
	u32 p_flags;
	u32 p_align;
} Elf32_Phdr;

#define PH_SIZE         32
#define PT_LOAD         0x1
#define PF_X            0x1
#define PF_W            0x2
#define PF_R            0x4

#define SH_SIZE         40




// Linux



typedef struct _section_info
{
    Elf32_Phdr scn_hdr;
    pu8 scn_data;
    u32 scn_size;
    u32 scn_file_size;
    u32 scn_file_offset;
    u32 scn_virtual_size;
} section_info, *psection_info;



typedef struct _exe_info
{
    psection_info data_scn; // 全局区
    psection_info code_scn; //代码区
    psection_info rdata_scn; //常量区

    Elf32_Ehdr eh;
    u32 scn_count;
    psection_info scn_list[CEED_MAX_SECTION_COUNT];
} exe_info, *pexe_info;

psection_info 
elf_new_section(pexe_info ei, u32 scn_va, u32 attr) //创建区的内存
{
    psection_info si = malloc(sizeof(section_info));
    memset(si, 0, sizeof(section_info));
    si->scn_hdr.p_type = PT_LOAD;
    si->scn_hdr.p_flags = attr;
    si->scn_hdr.p_vaddr = scn_va;
    si->scn_hdr.p_align = CEED_SECTION_ALIGN;
    ei->scn_list[ei->scn_count++] = si;
    return si;
}





pvoid
elf_alloc_exe_info()//创建data ,rodata,code 的区的内存
{
    pexe_info ei = malloc(sizeof(exe_info));
    memset(ei, 0, sizeof(exe_info));

    ei->data_scn = elf_new_section(ei, CEED_DATA_SECTION_VA, PF_R | PF_W);
    ei->code_scn = elf_new_section(ei, CEED_CODE_SECTION_VA, PF_X | PF_R);
    ei->rdata_scn = elf_new_section(ei, CEED_RDATA_SECTION_VA, PF_R);

    return ei;
}

void printfd1(Elf32_Ehdr * her){

for(int i=0;i<EI_NIDENT;i++){
	printf("%#x ",her->e_ident[i]);
}
printf("%#x ",her->e_type);
printf("%#x ",her->e_machine);
printf("%#x ",her->e_version);
printf("%#x ",her->e_entry);
printf("%#x ",her->e_phoff);
printf("%#x ",her->e_shoff);
printf("%#x ",her->e_flags);
printf("%#x ",her->e_ehsize);
printf("%#x ",her->e_phentsize);
printf("%#x ",her->e_phnum);
printf("%#x ",her->e_shentsize);
printf("%#x ",her->e_shnum);
printf("%#x \n",her->e_shstrndx);

	
}


void printfd2(Elf32_Phdr * her){


printf("%#x ",her->p_type);
printf("%#x ",her->p_offset);
printf("%#x ",her->p_vaddr);
printf("%#x ",her->p_paddr);
printf("%#x ",her->p_filesz);
printf("%#x ",her->p_memsz);
printf("%#x ",her->p_flags);
printf("%#x \n",her->p_align);
	
}




pvoid
elf_set_scn(psection_info si, pu8 scn_data, u32 scn_size)
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
elf_set_exe_code_scn(pvoid einfo, pu8 scn_data, u32 scn_size)
{
    pexe_info ei = einfo;
		printf("elf_set_exe_code_scn===%d\n",scn_size);
    return elf_set_scn(ei->code_scn, scn_data, scn_size);
}

pvoid
elf_set_exe_data_scn(pvoid einfo, pu8 scn_data, u32 scn_size)
{		printf("elf_set_exe_data_scn===%d\n",scn_size);

    pexe_info ei = einfo;
    return elf_set_scn(ei->data_scn, scn_data, scn_size);
}

pvoid
elf_set_exe_rdata_scn(pvoid einfo, pu8 scn_data, u32 scn_size)
{
    pexe_info ei = einfo;
		printf("elf_set_exe_rdata_scn===%d\n",scn_size);
    return elf_set_scn(ei->rdata_scn, scn_data, scn_size);
}

u32
elf_get_code_va(pvoid einfo)
{
    return CEED_CODE_SECTION_VA;
}

u32
elf_get_data_va(pvoid einfo)
{
    return CEED_DATA_SECTION_VA;
}

u32
elf_get_rdata_va(pvoid einfo)
{
    return CEED_RDATA_SECTION_VA;
}

void
elf_write_hdr(pexe_info ei, FILE *file)
{
    u32 i;
    i = 0;

    ei->eh.e_ident[i++] = EI_MAG0;
    ei->eh.e_ident[i++] = EI_MAG1;
    ei->eh.e_ident[i++] = EI_MAG2;
    ei->eh.e_ident[i++] = EI_MAG3;
    ei->eh.e_ident[i++] = ELFCLASS32;       // EI_CLASS
    ei->eh.e_ident[i++] = ELFDATA2LSB;      // EI_DATA
    ei->eh.e_ident[i++] = EV_CURRENT;       // EI_VERSION
    ei->eh.e_ident[i++] = ELFOSABI_NONE;    // EI_OSABI

	
    ei->eh.e_type = ET_EXEC;
    ei->eh.e_machine = EM_386;
    ei->eh.e_version = EV_CURRENT;

    ei->eh.e_phoff = EH_SIZE;
    ei->eh.e_ehsize = EH_SIZE;
    ei->eh.e_phentsize = PH_SIZE;
    ei->eh.e_shentsize = SH_SIZE;

    ei->eh.e_phnum = ei->scn_count;
    ei->eh.e_entry = CEED_CODE_SECTION_VA + func[0];
	fwrite(&ei->eh, sizeof(Elf32_Ehdr), 1, file);
	
	printfd1(&ei->eh);


    
}





void
elf_write_prg_hdrs(pexe_info ei, FILE *file)
{
    u32 hdr_size;
    u32 cur_offset;

    hdr_size = EH_SIZE + (PH_SIZE * ei->scn_count);
    cur_offset = hdr_size;
	printf("elf_write_prg_hdrs   cur_offset= %d\n",cur_offset);
    for (int i = 0; i < ei->scn_count; i++)
    {
        psection_info si = ei->scn_list[i];
        cur_offset = round_up(cur_offset, CEED_SECTION_ALIGN);
        si->scn_hdr.p_offset = cur_offset;
        cur_offset += si->scn_virtual_size;
		 fwrite(&si->scn_hdr, sizeof(Elf32_Phdr), 1, file);
         printfd2(&si->scn_hdr);
	printf("\n");
		printf("elf_write_prg_hdrs end   cur_offset= %d\n",cur_offset);

    }
}

void
elf_write_section_data(psection_info si, FILE *file)
{
    fseek(file, si->scn_hdr.p_offset, SEEK_SET);
    fwrite(si->scn_data, si->scn_file_size, 1, file);
		printf("elf_write_section_data   p_offset= %d\n",si->scn_hdr.p_offset);

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
elf_gen_data_section(pexe_info ei)
{
    //
    // Only 26 global variables of 4-byte int size are supported.
    //
    elf_set_exe_data_scn(ei, data_buffer, (CEED_MAX_VARIABLES * 4)); 
}

void
elf_gen_exe_file(pvoid einfo)
{
    pexe_info ei = einfo;
    FILE *exe_file;

    if (func[0] == -1)
    {
        printf("Entry point function '_a' not found.\n");
        exit(-1);
    }
    char namess[]="a.out";
    exe_file = fopen(namess, "wb+");
    if (exe_file == NULL)
    {
        printf("Failed to create output file (a.exe).\n");
        exit(errno);
    }

    elf_gen_data_section(ei);
    elf_write_hdr(ei, exe_file);
    elf_write_prg_hdrs(ei, exe_file);
	
    for (int i = 0; i < ei->scn_count; i++)
    {  
        psection_info si = ei->scn_list[i];
        elf_write_section_data(si, exe_file);
    }

  if (chmod(namess, 755) == -1) {
    printf("chmod failed\n");
  }

    fclose(exe_file);
}

void
elf_emit_main_init()
{
}

void
elf_emit_main_exit()
{
	
	printf("elf_emit_main_exit===\n");
	
	
	
  // 	printf("elf_emit_main_exit==ss=\n");
	//emit8(0x5d);
	// emit8(0xc3);
	
 //   mov ebx, eax     // set return code
	
   emit8(0x89);
   emit8(0xc3);

  //   mov eax, 1       // syscall_exit
    emit8(0xb8);
   emit32(0x1);

  //  int 0x80         // invoke syscall
     emit8(0xcd);
   emit8(0x80);
	
	   	printf("elf_emit_main_exit==4dd44=\n");
}

void
elf_emit_write_reg_input()
{
    // mov ebx, 1 (stdout)
    emit8(0xbb);
    emit32(0x1);

    // mov eax, 4 (syscall_write)
    emit8(0xb8);
    emit32(0x4);

    // int 0x80
    emit8(0xcd);
    emit8(0x80);
}

void
elf_emit_write(u32 buf_addr, u32 buf_len)
{
	printf("elf_emit_write   \n");
	
    // mov edx, str_len
    emit8(0xba);
    emit32(buf_len);

    // mov ecx, str_addr
    emit8(0xb9);
    // emit32(0x9049000 + p->con.value);
    emit32(buf_addr);

    elf_emit_write_reg_input();
		printf("elf_emit_write  1 \n");
}

void
elf_emit_read(u32 buf_addr, u32 buf_len)
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
elf_init()
{
    ei = elf_alloc_exe_info();
    gen_exe_file = elf_gen_exe_file;
    set_exe_code_scn = elf_set_exe_code_scn;
    set_exe_rdata_scn = elf_set_exe_rdata_scn;
    get_code_va = elf_get_code_va;
    get_data_va = elf_get_data_va;
    get_rdata_va = elf_get_rdata_va;
    emit_main_init = elf_emit_main_init;
    emit_main_exit = elf_emit_main_exit;
    emit_write = elf_emit_write;
    emit_write_reg_input = elf_emit_write_reg_input;
    emit_read = elf_emit_read;
}