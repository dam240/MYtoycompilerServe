#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/stat.h>
#include "ir.h"

void out_elf_header(FILE *fp, uintptr_t entry, int phnum, int shnum) ;


void out_program_header(FILE *fp, int sec, uintptr_t offset, uintptr_t vaddr, size_t filesz,size_t memsz);
static void put_padding(FILE *fp, uintptr_t  start); 
void outfile(char * name);