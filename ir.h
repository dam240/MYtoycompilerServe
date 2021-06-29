#include <ctype.h>
#include "readfile.h"  


typedef enum OP
{   AND=80100,//&&
	OR=80200,//||
	FE=80300,//
	AN=81100,//&
	R=81200,//|
	ADD=82100,//+
	INC=82300,//++
	DIN=82301,//--
	SUB=82200,// -
	END=90000,
	SURP=82303,// *
	DIVD=82400,//
	EQ=11100,//==
	BIG=11200,//>
	SM=11300,//<
	BG=11400,//>=
	SG=11500,//<=
	NOT=12000,//!
	NOTG=12100,//!=
	LOAD=28000,//=
	QU=52000,//存队列
	QUQ=52001,//取队列
	CALL=810,

MOV=28001,
    RET=30000,
      AX=10000,//模拟寄存器
	  BX=10003,
	  CX=10007,
	   SX=10009,
JPM=820,
	  DX=10008,
	  PUS=20001,
	  POP=20002,
	WP=80,//witre
	RP=90,//read
INT=90001,
	CHAR=90002,
}OPER;




extern code arcs;
extern memorys mey;


void ir_asm(char * file);