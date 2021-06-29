#include <stdlib.h>  // malloc
#include <string.h>
#include <stdio.h>
#include "list.h"
#define START_ADDRESS    (0x01000000 + PROG_START)

#define PROG_START   (0x100)
typedef struct memoryName{
 char * name;//变量名
 int start;//rdata的开始位置
 int end;//rdata的end位置
 int codelen;//变量占的内存
}memoryNamem,*memoryNames;	

typedef struct memory{
 char   code[2024]; //rdata区大小
 int code_len; //总共多少机器码
 int len;//2024
 struct Arraylist * memoryline;//多少变量和常量的
}memoryco,*memorys;


typedef struct retnb{
 int ret;//多少字节
 int code_len;
}rt,*ret;



typedef struct txt{
 char   code[2024]; //多少字节
 char   rdate[2024]; 
 int code_len;
 int rdate_len;
}coder,*code;





typedef struct node{
 char * asmscode;
 char   code[20]; 
 int code_index; //机器码的位置
 int len_code;//多少字节
 int arenode;
}node,*nodes;




typedef struct model{
	
	char  * name;
	char start[100];
	struct Arraylist * line;
     int code_len;
}method,* methods;


void readfile(FILE *fp,char * buf,int MAX_LINE);
char * returnsCH(char * code,int b,int e);
struct Arraylist *  modelsplit(struct Arraylist * list);
struct Arraylist *  readMode(char * buf);
char * getschar(int b,int e,char * p);
int cCount(char c,char * p);
struct Arraylist *  splitchar(char  * p,char c);