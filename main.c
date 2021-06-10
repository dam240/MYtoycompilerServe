#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "model.h"
int func[26];
void gen_exe(void);


int 
main(int argc, char *argv[])
{
	/*
	 生成一个hello 的执行程序
	 这个是  一个玩具编译器后端
	 64位
	*/
	
int sbdbd;
     func[0] = -1;
	
	  elf_init64();  
	 cmplr_init();
gen_exe();
	


return 0;
}