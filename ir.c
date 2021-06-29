#include "ir.h"
#define RDATA_ADDRESS    (0x02000000)


 memorys mey;
code arcs;


void emit(int size,char * code){
	//printf("emit\n");
	memcpy(&arcs->code[arcs->code_len], code,size);
	arcs->code_len+=size;
	
}


void emitrdate(int size,char * code){
	memcpy(&arcs->rdate[arcs->rdate_len], &code,size);
	arcs->rdate_len+=size;
}










int  expr(nodes no){//中间代码转机器代码  寄存器都是64位置操作，没有其他
	//	printf("expr===============\n");
	int codelen=0;
	char * dest=NULL,* src=NULL,* machine=NULL;
	int is=0;
	if(no->arenode==0){
	
	struct Arraylist * list = splitchar(no->asmscode,',');
	 int  val;
	int i;
    for(i=0;i<list->length;i++){
	 switch(i){
        case 0:
          machine=getarray(list,i); 
		  break;
		  case 1:
          dest=getarray(list,i);
		  break;
		  case 2:
          src=getarray(list,i);
		  break;
		  default:
         printf("expr=================error\n");
		  break;
	 }		 
	
	}

  // printf("expr========1======%d=\n",list->length);
   //printf(" %s   ,%d\n",machine,strlen(machine));
   //  printf("%s ,%d\n",dest,strlen(dest));
	 //   printf("%s ,%d\n",src,strlen(src));
	
	memoryNames mna=NULL;
	
	switch(atoi(machine)){
		case INT:
		mna=malloc(sizeof(memoryNamem));
	
		mna->name=malloc(20);
		strcpy(mna->name,dest);
		mna->start=mey->code_len;
		if(isdigit(src[0])){
				 
				 
				 
				 
				 
				int is=atoi(src);
				//printf("expr========1======%d=\n",is);
		    memcpy(&mey->code[mey->code_len], &is, 4);
		}else{
				 int is=atoi("0");
			memcpy(&mey->code[mey->code_len], &is, 4);
			
		
		}
        mey->code[mey->code_len+1]=0;
		mey->code_len+=5;
		mna->end=mey->code_len-1;
        mna->codelen=5;
        add(mey->memoryline,mna);
	
		 printf(" int    %s ,%d\n",mna->name, mna->end);
		break;
		case  CHAR:
		mna=malloc(sizeof(struct memoryName));
		//mna->name=dest;
		
	    mna->name=malloc(20);
		strcpy(mna->name,dest);
		mna->start=mey->code_len;
		int lens=strlen(src);
		for(i=0;i<lens;i++){
			mey->code[mey->code_len]=src[i];
			mey->code_len++;
		}
		printf("%s  name---\n",src);
		//memcpy(&mey->code[mey->code_len], &src,lens);
		  mey->code[mey->code_len+1]=0;
		mey->code_len+=1;
		mna->end=mey->code_len-1;
        mna->codelen=lens;
        add(mey->memoryline,mna);
		
		break;
		case MOV:
		case LOAD:
		
		//char sn=;
		//no->code[0]=0x48;
		//no->code[0]=0xc7;
		
		switch(atoi(dest)){
			
			case  AX:
			switch(atoi(src)){
			
			case  BX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xd8;
		 
		   	no->len_code=3;
		    return 3;
			break;
			
			
			case  CX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xc8;
		 
		   	no->len_code=3;
		    return 3;
			
			
			break;
			
			
			case  DX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xd0;
		 
		   	no->len_code=3;
		    return 3;
			
			break;
			default:
			//48 8d 05 
			is=atoi(src);
			if(is==0){
			no->code[0]=0x48;
		    no->code[1]=0x8d;
		    no->code[2]=0x04;
			no->len_code=7;
		    return 7;
			}else{
		    no->code[0]=0x48;
		    no->code[1]=0xc7;
		    no->code[2]=0xc0;
			
			memcpy(&no->code[3], &is,4);
			no->len_code=7;
		    return 7;
				
			}
			
			break;
			
			
			}
			
			
			break;
			
			
			
			case  BX:
			
			
			
			switch(atoi(src)){
			
			case  AX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xc3;
		 
		   	no->len_code=3;
		    return 3;
			break;
			
			
			case  CX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xcb;
		 
		   	no->len_code=3;
		    return 3;
			
			
			break;
			
			
			case  DX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xd3;
		 
		   	no->len_code=3;
		    return 3;
			
			break;
		default:
		is=atoi(src);
			if(is==0){ //48 8d 1d
			no->code[0]=0x48;
		    no->code[1]=0x8d;
		    no->code[2]=0x1d;
		
			no->len_code=7;
		    return 7;
			
		
			}else{
		    no->code[0]=0x48;
		    no->code[1]=0xc7;
		    no->code[2]=0xc3;
			memcpy(&no->code[3], &is,4);
			no->len_code=7;
		    return 7;
				
			}
			
			break;
			
			
			}
			
			
			
			
			
			break;
			
			
			case  CX:
			
				switch(atoi(src)){
			
			case  AX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xC1;
		 
		   	no->len_code=3;
		    return 3;
			break;
			
			
			case  BX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xd9;
		 
		   	no->len_code=3;
		    return 3;
			
			
			break;
			
			
			case  DX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xd1;
		 
		   	no->len_code=3;
		    return 3;
			
			break;
			 default:
			 	is=atoi(src);
			if(is==0){
			no->code[0]=0x48;
		    no->code[1]=0x8d;
		    no->code[2]=0x0d;
			no->len_code=7;
		    return 7;
			
				}else{
		    no->code[0]=0x48;
		    no->code[1]=0xc7;
		    no->code[2]=0xc1;
			memcpy(&no->code[3], &is,4);
			no->len_code=7;
		    return 7;
				
			}
			break;
			
			
			}
			
			
			
			
			
			break;
			
			
			case  DX:
			
			
			
				switch(atoi(src)){
			
			case  AX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xc2;
		 
		   	no->len_code=3;
		    return 3;
			break;
			
			
			case  BX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xDa;
		 
		   	no->len_code=3;
		    return 3;
			
			
			break;
			
			
			case  CX: //mov rdx,rcx
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xca;
		 
		   	no->len_code=3;
		    return 3;
			
			break;
			 default: //mov rdx,mn
			
			 	is=atoi(src);
			//	 printf("=======================rdx48 8d 15=%d====\n",is);
			if(is==0){
				no->code[0]=0x48;
		    no->code[1]=0x8d;
		    no->code[2]=0x15;
			  no->len_code=7;
		    return 7;
			}else{
		    no->code[0]=0x48;
		    no->code[1]=0xc7;
		    no->code[2]=0xc2;
			memcpy(&no->code[3], &is,4);
			no->len_code=7;
		    return 7;
				
			}
			break;
			
			}
			
			
			break;
			
			
			case  SX:
			
			 switch(atoi(src)){
			
			case  AX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xc2;
		 
		   	no->len_code=3;
		    return 3;
			break;
			
			
			case  BX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xDa;
		 
		   	no->len_code=3;
		    return 3;
			
			
			break;
			
			
			case  CX: //mov rdx,rcx
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0xca;
		 
		   	no->len_code=3;
		    return 3;
			
			break;
			 default: //mov rdx,mn
			// printf("=======================rdx=====\n");
			no->code[0]=0x48;
		    no->code[1]=0x8d;
		    no->code[2]=0x35;
			no->len_code=7;
		    return 7;
			
			break;
			
			}
			
			
			break;	
			
		 default:
			switch(atoi(src)){  //mov nm,rax
			
			
		     case  AX:
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0x04;
			no->code[3]=0x25;
			no->len_code=8;
		    return 8;
			
			
		   
			break;
				
				  case  BX:
			
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0x1c;
			no->code[3]=0x25;
			no->len_code=8;
		    return 8;
			
		   
			break;
				
				  case  CX:
			
		    no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0x0c;
			no->code[3]=0x25;
			no->len_code=8;
		    return 8;
		   
			break;
			
			  case  DX:
			no->code[0]=0x48;
		    no->code[1]=0x89;
		    no->code[2]=0x14;
			no->code[3]=0x25;
			no->len_code=8;
		    return 8;
			
		   
			break;
			
		 default:
			printf("内存不能直接对内存\n");
			exit(-1);
			break;
				
				
			}
			
			
			
			break;
			
			
			
			
			
			
			
			
			
		}
		
		
		
		
		
		
		
		break;
		
		case  RET:
		
		no->code[0]=0xc3;
		no->len_code=1;
		return 1;
		
		
		break;
	    case ADD:
		
				switch(atoi(dest)){
					case AX:
					
					
				
					switch(atoi(src)){ //add rax,r/mn
					case BX:
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xd8;
		               	no->len_code=3;
		                  return 3;
					
					
					
					  break;
					  case CX:
					
					    no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xc8;
		               	no->len_code=3;
		                  return 3;
					
					  break;
					  case DX:
					
					
					    no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xd0;
		               	no->len_code=3;
		                  return 3;
					
					  break;
					   default:
					  
					
					   val=atoi(src);
					   
					   if(val){//
						 no->code[0]=0x48;
		                 no->code[1]=0x05;
						//no->code[2]=0xc0;
					    memcpy(&no->code[2], &val,4);
						no->len_code=6;
						return 6;
					   }else{//内存
						    no->code[0]=0x48;
		                    no->code[1]=0x03;
							no->code[2]=0x04;
		                    no->code[3]=0x25;
							
							no->len_code=8;
							
							return 8;
						   
					   }
					
					
					
					  break;
					  
					  
					}
					
					
					
					
					
					
					break;
					
					case BX:
					
					
					
					switch(atoi(src)){
					case AX:
					
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xc3;
		               	no->len_code=3;
		                  return 3;
					
					
					  break;
					  case CX:
					
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xcb;
		               	no->len_code=3;
		                  return 3;
					
					
					
					  break;
					  case DX:
					
					
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xd3;
		               	no->len_code=3;
		                  return 3;
					
					  break;
					   default:
					
					
					   val=atoi(src);
					   
					   if(val){//48 81 c1 
						 no->code[0]=0x48;
		                 no->code[1]=0x81;
						no->code[2]=0xc3;
					      memcpy(&no->code[2], &val,4);
					 	no->len_code=7;
						return 7;
					   }else{//内存
						    no->code[0]=0x48;
		                    no->code[1]=0x03;
							no->code[2]=0x1c;
		                    no->code[3]=0x25;
							
							no->len_code=8;
							
							return 8;
						   
					   }
					
					
					
					
					
					  break;
					  
					  
					}
					
					break;
					
					
					
					case CX:
					
					switch(atoi(src)){
					
					  case AX:
					
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xc1;
		               	no->len_code=3;
		                  return 3;
					
					
					  break;
					  
					  case BX:
					
					
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xd9;
		               	no->len_code=3;
		                  return 3;
					
					  break;
					  case DX:
					
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xd1;
		               	no->len_code=3;
		                  return 3;
					
					  break;
					   default:
					
					    val=atoi(src);
					   
					   if(val){//48 81 c1 
						 no->code[0]=0x48;
		                 no->code[1]=0x81;
						no->code[2]=0xc1;
					      memcpy(&no->code[2], &val,4);
						no->len_code=7;
						return 7;
					   }else{//内存
						    no->code[0]=0x48;
		                    no->code[1]=0x03;
							no->code[2]=0x0c;
		                    no->code[3]=0x25;
							
							no->len_code=8;
							
							return 8;
						   
					   }
			
					
					
					
					  break;
					  
					  
					}
					
					
					break;
					
					
					case DX:
					
					switch(atoi(src)){
						  case AX:
					
					
						no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xc2;
		               	no->len_code=3;
		                  return 3;
					
					
					  break;
					 case BX:
					
					    no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xda;
		               	no->len_code=3;
		                  return 3;
					
					
					  break;
					  case CX:
					
					   no->code[0]=0x48;
		                no->code[1]=0x01;
		                no->code[2]=0xca;
		               	no->len_code=3;
		                  return 3;
					
					
					  break;
					
					   default:
					  
					  
				   val=atoi(src);
					   
					   if(val){//48 81 c1 
						 no->code[0]=0x48;
		                 no->code[1]=0x81;
						 no->code[2]=0xc2;
					     memcpy(&no->code[2], &val,4);
						 no->len_code=7;
						return 7;
					   }else{//内存
						    no->code[0]=0x48;
		                    no->code[1]=0x03;
							no->code[2]=0x14;
		                    no->code[3]=0x25;
							
							no->len_code=8;
							
							return 8;
						   
					   }
					  
					  
					
					  break;
					  
					  
					}
					
					
					break;
					
					
					 default:
					
					
					     val=atoi(dest);
					   
					   if(val){//48 81 c1 
					
					   printf(" add &11,rax  error\n");
					    exit(-1);
						///return 7;
					   }
					   //内存
					   
					   
					   switch(atoi(src)){
						   
						   case AX:
						   
						   
						       no->code[0]=0x48;
		                    no->code[1]=0x01;
							no->code[2]=0x04;
		                    no->code[3]=0x25;
						
						
						
						   	no->len_code=8;
							
							return 8;
						   
						   break;
						   
						     case BX:
						   
						        no->code[0]=0x48;
		                    no->code[1]=0x01;
							no->code[2]=0x1c;
		                    no->code[3]=0x25;
						
						
						
						   	no->len_code=8;
							
							return 8;
						   
						   
						   break;
						   
						     case CX:
						       no->code[0]=0x48;
		                    no->code[1]=0x01;
							no->code[2]=0x0c;
		                    no->code[3]=0x25;
						
						
						
						   	no->len_code=8;
							
							return 8;
						   break;
						   
						     case DX:
						     no->code[0]=0x48;
		                    no->code[1]=0x01;
							no->code[2]=0x14;
		                    no->code[3]=0x25;
						
						
						
						   	no->len_code=8;
							
							return 8;
						   break;
						   
					   
					   
					   }
					   
						  
						   
					   
					
					
					
					
					
					
					break;
					
					
					
					
					
					
				}
		
	
		
		
		break;
		case  INC:
	
       	switch(atoi(dest)){
              case AX:

                           no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xc0;
						   	no->len_code=3;
							
							return 3;
               break;
			   
		       case BX:

                             no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xc3;
						   	no->len_code=3;
							
							return 3;

               break;
			   
			    case CX:

                           no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xc1;
						   	no->len_code=3;
							
							return 3;
               break;
			   
			    case DX:

                          no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xc2;
						   	no->len_code=3;
							
							return 3;
               break;
			
			 default:
			
			printf("error\n");
			exit(-1);
			break;
			
		}
		
		
		
		
		break;
		case DIN:
		
		  	switch(atoi(dest)){
              case AX:

                            no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xc8;
						   	no->len_code=3;
							
							return 3;
               break;
			   
		       case BX:

                             no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xcb;
						   	no->len_code=3;
							
							return 3;

               break;
			   
			    case CX:

                           no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xc9;
						   	no->len_code=3;
							
							return 3;
               break;
			   
			    case DX:

                          no->code[0]=0x48;
		                    no->code[1]=0xff;
							no->code[2]=0xca;
						   	no->len_code=3;
							
							return 3;
               break;
			
			 default:
			
			printf("error\n");
			exit(-1);
			break;
			
		}
		
		break;
		
		case  SUB:
		                   no->code[0]=0x48;
		                    no->code[1]=0x29;
			switch(atoi(dest)){
				
				
              case AX:

                 switch(atoi(src)){
                   case BX:
				         
							no->code[2]=0xd8;
						   	no->len_code=3;
							return 3;
				   
				   break;
                   
                    case CX:
				        
							no->code[2]=0xc8;
						   	no->len_code=3;
							
							return 3;
				   
				   break;
				   
                      case DX:
					      
							no->code[2]=0xd0;
						   	no->len_code=3;
							
							return 3;
					  
				   break;

				 }

                        
               break;
			   
		       case BX:

                        switch(atoi(src)){
                   case AX:
	
							no->code[2]=0xc3;
						   	no->len_code=3;
							
							return 3;
				   
				   break;
                    case CX:
					       no->code[2]=0xcb;
						   	no->len_code=3;
							
							return 3;
				   break;

                  case DX:
					   no->code[2]=0xd3;
					   no->len_code=3;
							
							return 3;
				   break;

				 }
    

               break;
			   
			    case CX:
                  switch(atoi(src)){
                   case AX:
				           no->code[2]=0xc1;
						   	no->len_code=3;
							
							return 3;
				   
				   break;
                   
                    case BX:
					      no->code[2]=0xd9;
						   	no->len_code=3;
							
							return 3;
					
				   break;

                      case DX:
					        no->code[2]=0xd1;
						   	no->len_code=3;
							
							return 3;
				   break;

				 }

               break;
			   
			    case DX:
                    switch(atoi(src)){
                   case AX:
				        no->code[2]=0xc2;
						   	no->len_code=3;
							
							return 3;
				   break;
                   
                    case BX:
				         	no->code[2]=0xda;
						   	no->len_code=3;
							
							return 3;
				   break;

                      case CX:
					  
					        no->code[2]=0xca;
						   	no->len_code=3;
							
							return 3;
				   break;

				 }

               break;
			
			 default:
			
			printf("error\n");
			exit(-1);
			break;
			
		}
		
		
		
		
		
		break;
		
	
		case  SURP:
		
		         no->code[0]=0x48;
		         no->code[1]=0x0f;
				 no->code[2]=0xaf;
			switch(atoi(dest)){
				
				case AX:
				switch(atoi(src)){
				case BX:
				 no->code[3]=0xc3;
				 	no->len_code=4;
				 return 4;
				break;
				case CX:
				 no->code[3]=0xc1;
				 	no->len_code=4;
				 return 4;
				break;
				case DX:
				 no->code[3]=0xc2;
				 	no->len_code=4;
				 return 4;
				break;
				 default:
				 printf("error\n");
				  exit(-1);
				  break;
				}
				
				break;
				
				case BX:
				
				switch(atoi(src)){
				case AX:
				 no->code[3]=0xd8;
				 	no->len_code=4;
				 return 4;
				break;
				case CX:
				 no->code[3]=0xd9;
				 	no->len_code=4;
				 return 4;
				break;
				case DX:
				 no->code[3]=0xda;
				 	no->len_code=4;
				 return 4;
				break;
				 default:
				 printf("error\n");
				  exit(-1);
				  break;
				}
				
				break;
				
				case CX:
				
			 switch(atoi(src)){
				case AX:
				 no->code[3]=0xc8;
				 	no->len_code=4;
				 return 4;
				break;
				case BX:
				 no->code[3]=0xcb;
				 	no->len_code=4;
				 return 4;
				break;
				case DX:
				 no->code[3]=0xca;
				 	no->len_code=4;
				 return 4;
				break;
				 default:
				 printf("error\n");
				  exit(-1);
				  break;
				}
				
				
				break;
				
				case DX:
				
				
			switch(atoi(src)){
				case AX:
				 no->code[3]=0xd0;
				 no->len_code=4;
				 return 4;
				break;
				case BX:
				 no->code[3]=0xd3;
				 	no->len_code=4;
				 return 4;
				break;
				case CX:
				 no->code[3]=0xd1;
				 	no->len_code=4;
				 return 4;
				break;
				 default:
				 printf("error\n");
				  exit(-1);
				  break;
				}
				break;
				 default:
				
				 printf(" *  error\n");
				exit(-1);
			}
				
		
		
		
		break;
		case DIVD:
			 no->code[0]=0x48;
			 no->code[1]=0xf7;
		switch(atoi(dest)){
			case AX:
			 no->code[2]=0xf8;
			 	no->len_code=3;
			 return 3;
			break;
		
		   case BX:
			no->code[2]=0xfb;
				no->len_code=3;
			 return 3;
			break;
			
			case CX:
			no->code[2]=0xf9;
				no->len_code=3;
			 return 3;
			break;
			
			case DX:
			no->code[2]=0xfa;
			no->len_code=3;
			 return 3;
			break;
			 default:
			printf(" / error\n");
			exit(-1);
		}
		
		
		
		break;
		
		case  EQ: //==
		
		    no->code[0]=0x48;
		    no->code[1]=0x39;
		
	     switch(atoi(dest)){
		
		   case AX:
		   switch(atoi(src)){
			  
		   
		   case BX:
		    no->code[2]=0xd8;
		   
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xc8;
		   break;
		   
		     case DX:
		     no->code[2]=0xd0;
		   break;
		   
		   
		   
		   }
		   break;
	    
 	    	case BX:
		    switch(atoi(src)){
		   
		   case AX:
		    no->code[2]=0xc3;
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xcb;
		   break;
		   
		     case DX:
		     no->code[2]=0xd3;
		   break;
		   
		   
		   
		   }
		   
		   
		   break;
		   
		   case CX:
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xC1;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xd9;
		   break;
		   
		     case DX:
		     no->code[2]=0xd1;
		   break;
		   
		   
		   
		   }
		   
		   break;
		   
		   case DX:
		   
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xc2;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xda;
		   break;
		   
		     case CX:
		     no->code[2]=0xca;
		   break;
		   
		   
		   
		   }
		   
		   break;
		
		 
		 }
		 
		 
		 
		 no->code[3]=0x74;
        no->len_code=5;
		return 5;
		//0f 84 6d
		
		break;
	    case BIG://>=
		case BG:
		
		
		
		    no->code[0]=0x48;
		    no->code[1]=0x39;
		
	     switch(atoi(dest)){
		
		   case AX:
		   switch(atoi(src)){
			  
		   
		   case BX:
		    no->code[2]=0xd8;
		   
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xc8;
		   break;
		   
		     case DX:
		     no->code[2]=0xd0;
		   break;
		   
		   
		   
		   }
		   break;
	    
 	    	case BX:
		    switch(atoi(src)){
		   
		   case AX:
		    no->code[2]=0xc3;
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xcb;
		   break;
		   
		     case DX:
		     no->code[2]=0xd3;
		   break;
		   
		   
		   
		   }
		   
		   
		   break;
		   
		   case CX:
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xC1;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xd9;
		   break;
		   
		     case DX:
		     no->code[2]=0xd1;
		   break;
		   
		   
		   
		   }
		   
		   break;
		   
		   case DX:
		   
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xc2;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xda;
		   break;
		   
		     case CX:
		     no->code[2]=0xca;
		   break;
		   
		   
		   
		   }
		   
		   break;
		
		 
		 }
		
		no->code[3]=0x7d;
		no->len_code=5;
		return 5;
		
		break;
		case  SM://<=
		case  SG:
		
		
		
		    no->code[0]=0x48;
		    no->code[1]=0x39;
		
	     switch(atoi(dest)){
		
		   case AX:
		   switch(atoi(src)){
			  
		   
		   case BX:
		    no->code[2]=0xd8;
		   
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xc8;
		   break;
		   
		     case DX:
		     no->code[2]=0xd0;
		   break;
		   
		   
		   
		   }
		   break;
	    
 	    	case BX:
		    switch(atoi(src)){
		   
		   case AX:
		    no->code[2]=0xc3;
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xcb;
		   break;
		   
		     case DX:
		     no->code[2]=0xd3;
		   break;
		   
		   
		   
		   }
		   
		   
		   break;
		   
		   case CX:
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xC1;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xd9;
		   break;
		   
		     case DX:
		     no->code[2]=0xd1;
		   break;
		   
		   
		   
		   }
		   
		   break;
		   
		   case DX:
		   
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xc2;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xda;
		   break;
		   
		     case CX:
		     no->code[2]=0xca;
		   break;
		   
		   
		   
		   }
		   
		   break;
		
		 
		 }
		
		no->code[3]=0x7e;
		no->len_code=5;
		return 5;
		break;
		
		
		
		case NOT:
		
		break;
		
		case  NOTG: //!=
		
		    no->code[0]=0x48;
		    no->code[1]=0x39;
		
	     switch(atoi(dest)){
		
		   case AX:
		   switch(atoi(src)){
			  
		   
		   case BX:
		    no->code[2]=0xd8;
		   
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xc8;
		   break;
		   
		     case DX:
		     no->code[2]=0xd0;
		   break;
		   
		   
		   
		   }
		   break;
	    
 	    	case BX:
		    switch(atoi(src)){
		   
		   case AX:
		    no->code[2]=0xc3;
		   
		   break;
		   
		     case CX:
		     no->code[2]=0xcb;
		   break;
		   
		     case DX:
		     no->code[2]=0xd3;
		   break;
		   
		   
		   
		   }
		   
		   
		   break;
		   
		   case CX:
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xC1;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xd9;
		   break;
		   
		     case DX:
		     no->code[2]=0xd1;
		   break;
		   
		   
		   
		   }
		   
		   break;
		   
		   case DX:
		   
		    switch(atoi(src)){
		   
		   case AX:
		     no->code[2]=0xc2;
		   
		   break;
		   
		     case BX:
		     no->code[2]=0xda;
		   break;
		   
		     case CX:
		     no->code[2]=0xca;
		   break;
		   
		   
		   
		   }
		   
		   break;
		
		 
		 }
	    no->code[3]=0x75;
			no->len_code=5;
		return 5;
		
		
		break;
	    case QU:
		
		break;
		case  QUQ:
		
		break;
		case CALL:
	//	printf("CALL------------------\n");
	 
		if(atoi(dest)==WP||atoi(dest)==RP){
			 no->len_code=0;
			return 0;
		}
		 no->code[0]=0xe8;
		 no->len_code=5;
		return 5;
			//printf("CALL--------2----------\n");
		break;
		
		case JPM:
		//	printf("JPM------------------\n");
	    //no->code[0]=0xeb;
		no->len_code=0;
		return 0;
		//printf("JPM------2------------\n");
		break;
		
		
		case PUS:
		switch(atoi(dest)){
		
		case  AX:
		
	    //char sn=;
		no->code[0]=0x50;
		no->len_code=1;
		return 1;
		break;
		
		case  BX:
			no->code[0]=0x53;
		no->len_code=1;
		return 1;
		break;
		case  CX:
	   no->code[0]=0x51;
		no->len_code=1;
		return 1;
		
		break;
		
		case  DX:
	   no->code[0]=0x52;
		no->len_code=1;
		return 1;
		
		break;
		
		
		}
		break;
		
		case  POP:
		
	switch(atoi(dest)){
		
		case  AX:
		 no->code[0]=0x58;
		
		  no->len_code=1;
		return 1;
		
		
		break;
		
		case  BX:
		 no->code[0]=0x5b;
		
		no->len_code=1;
		return 1;
		break;
		case  CX:
		 no->code[0]=0x59;
		
		no->len_code=1;
		return 1;
		
		break;
		
		case  DX:
		no->code[0]=0x5a;
		no->len_code=1;
		return 1;
		break;
		
		}
		
		
		
		
		break;
	    case WP: //调用系统 
		
		  switch(atoi(dest)){
			case AX:
			no->code[0]=0x48;
			no->code[1]=0x89;
			no->code[2]=0xc6;
              break;  
			 case BX:
  
          	no->code[0]=0x48;
			no->code[1]=0x89;
			no->code[2]=0xde;
             break;  
			 case CX:
         	no->code[0]=0x48;
			no->code[1]=0x89;
			no->code[2]=0xce;

             break;  
			  
			 case DX:
    	    no->code[0]=0x48;
			no->code[1]=0x89;
			no->code[2]=0xd6;

              break; 
           default:
    		 no->code[0]=0x90;
			no->code[1]=0x90;
			no->code[2]=0x90;

              break; 
		  
		  }
		
		
		
		
			no->code[3]=0x48;
			no->code[4]=0xc7;
			no->code[5]=0xc0;
			no->code[6]=0x01;
			//6+
			no->code[10]=0x48;
			no->code[11]=0xc7;
			no->code[12]=0xc7;
			no->code[13]=0x01;


            no->code[17]=0x0f;
			no->code[18]=0x05;
		
	    no->len_code=19;
		return 19;
		
		
		break;
		case  RP:
		no->len_code=20;
		return 20;
		
		break;
		
		
		
		
	}
	
	
	
	
	
	
	}
	
	
	return 0;
	
	
	
}




void enterMethods(methods mode){
	//printf("enterMethods===============\n");
	struct Arraylist * list=mode->line;
     int i;
	 int ret;
	for( i=0;i<list->length;i++){
		nodes no=getarray(list,i);
		ret=expr(no);
		if(ret!=0){
			no->code_index=mode->code_len;
			mode->code_len+=ret;
		}
		
		//printf("enterMethods========1=======\n");
	}


}

void  enterSet(struct Arraylist * list){
	
	//printf("enterSet===============\n");
	//splitchar
	int i;
	for(i=0;i<list->length;i++){
	   methods mode=getarray(list,i); 
	enterMethods(mode);
			//printf("enterSet========1=======\n");
	
	}
	
	
	
	
	
}



void printfx86(int len,char * arr,int boot){
	int i;
	
	for(i=0;i<len;i++){
		
	//	printf("%#x ",arr[i]);
		if(boot==0){
			arcs->rdate[arcs->rdate_len]=arr[i];
			arcs->rdate_len++;
		}
	}
//	printf(" \n");

	//emit(len,arr);
// else
	
}




void printfMethods(methods mode){
	//printf("printfMethods=========%s======\n",mode->name);
	if(mode->line==NULL)
		return;
	
	struct Arraylist * list=mode->line;
     int i;
	 int ret;
	for( i=0;i<list->length;i++){
		nodes no=getarray(list,i);
		//printf("%s  ---",no->asmscode);
		if(atoi(no->asmscode)!=END)
	    printfx86(no->len_code,no->code,1);
		//printf("enterMethods========1=======\n");
	}
	
	
	
	
}



void  printfms(struct Arraylist * list){
	
//	printf("printfms===============\n");
	//splitchar
	int i;
	for(i=0;i<list->length;i++){
	   methods mode=getarray(list,i); 
	   printfMethods(mode);
			//printf("enterSet========%d=======\n",mode->code_len);
	
	}
	
	
	
	
	
}


struct Arraylist *  sequence(struct Arraylist *  list){
	 struct Arraylist * methodlist=inif();
	 
	 methods mode=malloc(sizeof(method));
	 mode->name=malloc(10);
	 strcpy(mode->name,"start");
	 mode->line=NULL;
  	char code[]= {0xe8,0x00,0x00,0x00,0x00,0x48,0xc7,0xc0,0x3c,0x00,0x00,0x00,0x48,0xc7,0xc7,0x00,0x00,0x00,0x00,0x0f,0x05};
  	mode->code_len=21;
	memcpy(&mode->start[0], &code,mode->code_len);
    add(methodlist,mode);  
	methods mode1=NULL;
    int i=0;
	int codecont=0;
	
   for(;i<list->length;i++){
      mode1= getarray(list,i);
      add(methodlist,mode1);
	      
     	 int in= strcmp("main",mode1->name);
		 //printf("%s %d\n", mode1->name,strlen( mode1->name));
	  if(in==0){
		 // printf("%s \n",mode1->name);
		    codecont+=16;
		 	memcpy(&mode->start[1],&codecont,4);
		 
	  }else{
	  	  codecont+=mode1->code_len;
		 // printf("%d  %d \n",codecont,mode1->code_len);
	  }
   }
  // printf("%d  %d\n",codecont,mode->code_len);
   
   for(i=0;i<mode->code_len;i++){
    printf("%x  , ",mode->start[i]);
   
   }
   printf("\n");
  free(list->obj);
  free(list);
  return methodlist;
  
}


int computersAdder(int index,struct Arraylist *  list){
	int i=index;
     int count=0;
	 
	 
    for(;i<list->length;i++){
           methods mode =getarray(list,i); 
		  count+= mode->code_len;
	}
//	printf(" computersAdder %d \n",count);
	return count;
}



int compareNames(char * name,char * name2){
	// printf("compareNames=====%s===============%s \n",name,name2);

	int size=strlen(name2);
	if(strlen(name)<size)
		return 0;
	int s=0,i;

	for( i=0;i<size;i++){
		
		if(name2[i]==name[i]&&name2[i]!=' '&&name2[i]!='\0'&&name2[i]!=0){
	
			s++;
		}else
		{
			return 0;
		}

	}

	if(s==size){
		//printf("compareNames   emds \n");
		return 1;
	}

	return 0;

}




int  AdderaADD(int nextconde,int methodslen,nodes no){

char * dest=NULL,* src=NULL,* machine=NULL;   
int re=0,re2=0,j=0;
 int index=0;
    if(no->arenode==0){
	
	struct Arraylist * list = splitchar(no->asmscode,',');
	 int  val;
	int i;
    for(i=0;i<list->length;i++){
	 switch(i){
        case 0:
          machine=getarray(list,i); 
		  break;
		  case 1:
          dest=getarray(list,i);
		  if(dest[0]=='#'){
			  
			  re=strlen(dest);
			  for(;j<re;j++){
				  dest[j]=dest[j+1];
			  }
			  
			      dest[j]='\0';
			  
				// printf("-----------------%s\n",dest);
		  }
		
		 
		  break;
		  case 2:
          src=getarray(list,i);
		   if(src[0]=='#'){
			  
			  re=strlen(src);
			  for(;j<re;j++){
				  src[j]=src[j+1];
			  }
			   src[j]='\0';
			   // printf("-----------------%s\n",src);
		  }
		 
		  break;
		  default:
         printf("AdderaADD=================error\n");
		  break;
	 }		 
	
	}
	
	
//	printf("AdderaADD=========%s=====2===\n",no->asmscode);
	switch(atoi(machine)){
	case MOV:
	case LOAD:
	
	 re=atoi(dest);
	 j=0;
	 re2=atoi(src);
	 switch(re2){
		 case AX:
		   case BX:
		   case CX:		  
		   case DX:
		  break;
		 default:
		 j=re2;
		  re2=0;
		
		  break;
	 }
	 
	 
	 
//	printf("AdderaADD=========%d=====re2 %d===\n",re,re2);
   if(re==0||re2==0){
	
	  index=(methodslen-no->code_index)-no->len_code;
	  
	 // printf("%d   %d----\n",index,no->code_index);
	
	 index+=nextconde;
	  // printf("index====%d====%d===%d\n",mey->code_len,methodslen-no->code_index,index);
	 if(re==0&&re2==0){
	    printf("error\n");
		exit(-1);
	  }
	  // i=0;
	  int len= mey->memoryline->length;
	  char *names=NULL;
	  int boot=0;
	  if(re==0)
		names=dest;
		  
	  
	  
	  if(re2==0)
	  names=src;
  
      if(re!=0&&j!=0){
	   return 0;
	  }
  
  
    for(i=0;i<len;i++){
		
	
		  memoryNames mis =getarray(mey->memoryline,i);
       //   printf("%s  %s  %d  %d \n",names,mis->name,strlen(names),strlen(mis->name));
		  if(compareNames(names,mis->name)==1){ 
		  //   printf("AdderaADD======2===%d=====%d===\n",index,mis->start);
		        index=index+mis->start;
		    
			   boot+=1;
		       break;
			}
		     if(boot>0){
				     //  printf("name= %s  indexcode=%d \n",mis->name,mis->start);
				   break;
			 }
		  }
		  //  printf("AdderaADD=========1=====22===\n");
		  if(boot==0){
		    memoryNames mna=malloc(sizeof(memoryNamem));
	        mna->name=names;
	    	mna->start=mey->code_len;
			
			 if(j!=0){
				 
				 memcpy(&mey->code[mey->code_len], &j, 4);
				 mey->code[mey->code_len+4]=0;
				 mey->code_len+=4;
	          mna->end=mey->code_len-1;
              mna->codelen=4;
			 }else{
	     	//memcpy(&mey->code[mey->code_len], &names, strlen(names));
			int ii=0;
			int iil=strlen(names);
			for(;ii<iil;ii++){
				
				 mey->code[mey->code_len]=names[ii];
				 mey->code_len++;
			}
			
			  mey->code[mey->code_len+strlen(names)+1]=0;
          //printf("AdderaADD======%s==22===\n",names);
		   mey->code_len+=strlen(names)+1;
	       mna->end=mey->code_len-1;
           mna->codelen=strlen(names)+1;
			 }
            add(mey->memoryline,mna);
	       
	    //    printf("AdderaADD=========%d=====%d===\n",index,mna->start);
			 index=index+mna->start;
		  }
	  
            int codex =no->len_code-4;
		//  printf("addr %d   %d\n",index,codex);
		  memcpy(&no->code[codex],&index,4);
  
  //         for(i=0;i<no->len_code;i++){
    //           printf("%x ",no->code[i]);
		//   }
        //printf("\n");
  
	   return 0;
	}
	
	
	
	
	
	
	
	break;
	default:
	return -1;
	
	break;
	}
	


	}


  return -1;
}


int areJPM(nodes no){
	
	char * machine=NULL;  
	
  if(no->arenode==0){
	
	struct Arraylist * list = splitchar(no->asmscode,',');
	 int  val;
	
       machine=getarray(list,0); 
	   
	   switch(atoi(machine)){
	    
		  case JPM:
		    case EQ:
		    case BIG:
	         case SM:
		    case BG:
		    case SG:
	        case NOTG:
			
			return 1;
	      break;
		  case CALL:
		  
		  return 2;
		  
		  break;
		  default:
		  
		  break;
		  
	   }
	   
		
	}
	

     return 0;

}
//void computersJPMAdder(int nextconde,int methodslen,nodes no)


void setJPM(struct Arraylist *  list,int index){

	 nodes no  =getarray(list,index);
	 int boot=0;
	struct Arraylist * list1 = splitchar(no->asmscode,',');
	int jpm=0;
	char * machine=NULL,* src=NULL; 
	 machine=getarray(list1,0); 
	 switch(atoi(machine)){
		 case JPM:
		 boot=0;
		 break;
		 default:
     	boot=1;
		 break;
		 
	 }
	
	if(boot==1){
		// printf("----setJPM---2---\n");
		 nodes no1  =getarray(list,index+1);
		// no1->len_code=0;
	     struct Arraylist * list2 = splitchar(no1->asmscode,',');
	      machine=getarray(list2,0); 
	    switch(atoi(machine)){
		 case JPM:
		 boot=0;
		//  printf("----setJPM---6---\n");
		 break;
		 default:
     	boot=-1;
	//	 printf("----setJPM---7---\n");
		 break;
		 
	 }
	
	 if(boot==0){
	// printf("----setJPM---3---\n");
	   src=getarray(list2,1); 
	    int len= list->length;
	    int i=0;
	    for(;i<len;i++){
	 
		 nodes drse   =getarray(list,i);
		 
		 if(jpm==1){
			struct Arraylist * list22 = splitchar(drse->asmscode,',');
			  machine=getarray(list22,0);
			 if(drse->code_index==0&&atoi(machine)==820){
				 drse   =getarray(list,i+1);
			 }
			  jpm=drse->code_index;
			// printf(" jpm ---%d- %d\n",jpm,drse->code_index);
			 break;
			 
		 }
		 
	     
		
		
		//  printf("----setJPM---11---%s  %d\n",drse->asmscode,drse->arenode);
		 
		 if(drse->arenode==1){
			//  printf("----setJPM------%s==%s --%d-- %d-\n",src,drse->asmscode,strlen(src),strlen(drse->asmscode));
			 if(compareNames(drse->asmscode,src)==1){
			 
			 //   printf("----setJPM---1---\n");
			 
		      jpm=1;
			 
			 }
			 
		 }
		 
		}
		int addr=0;
		if((no->code_index+no->len_code)<jpm){
			addr=jpm-(no->code_index+no->len_code);
		// printf(" addr ---%d- %d- \n",jpm,(no->code_index+no->len_code));
		}else{
			addr=(no->code_index+no->len_code)-jpm;
			addr=~addr;
		//	printf(" addr --1-%d- %d- \n",jpm,(no->code_index+no->len_code));
		}
		
	//   printf(" addr ===%x %d \n",addr,addr);
		
		  int codex =no->len_code-1;
		  memcpy(&no->code[codex],&addr,1);
		
		
	 }
	 
	 
	 
		
	}else{ //jpm
		
		
		printf("==========jpm==============\n");
		
		
		
	}
	
	
	
	
	
}




 ret formethods(struct Arraylist *  list,int index,char * name){
	
	int i=1,j=0;   
	            ret jpm=malloc(sizeof(rt));
				 jpm->code_len=0;
				  jpm->ret=0;
				 
	for(;i<list->length;i++){

         methods mode =getarray(list,i); 
	//	 printf("formethods   %s %s  %d %d \n",mode->name,name,strlen(mode->name),strlen(name));
	     if(compareNames(name,mode->name)==1){
			
		    if(i<index){
				// 	 printf("formethods   %----  11\n");
				for(j=i;j<index;j++){
				 methods mode1 =getarray(list,j); 
				 jpm->code_len+=mode1->code_len;
				 
				}
					// printf("formethods   %d  1\n",jpm->code_len);
				//jpm->ret=0;
				return  jpm;
				
				
			}else{
				//	 printf("formethods   %----  2\n");
				if(index+1==i){
				 jpm->code_len+=0;
				 jpm->ret=1;
				 // printf("formethods   %d  2\n",jpm->code_len);
			     return  jpm;
				}
				
				
				for(j=index+1;j<i;j++){
				 methods mode1 =getarray(list,j); 
				 jpm->code_len+=mode1->code_len;
				}
				jpm->ret=1;
				// printf("formethods   %d  2\n",jpm->code_len);
				return  jpm;
				
			}
		
		 }else{
			  printf("formethods   not find 2\n");
			 
		 }
		 
		 
		 
	
	}
	jpm->ret=-1;
	
	return jpm;
	
	
	
}


void setcall(struct Arraylist *  list, nodes no,int index,int count){
	
	
	if(no->len_code==0)
	  return;
	
  struct Arraylist * list1 = splitchar(no->asmscode,',');
	ret jpm=NULL;
	int addr=0;
	 char * machine=NULL,* src=NULL; 
	 machine=getarray(list1,0); 
	 switch(atoi(machine)){
		 case CALL:
		
		 break;
		 default:
		 
     	 return;
		 break;
		 
	 }
	
	 src=getarray(list1,1);
	// printf("setcall========%s \n",src);
	jpm = formethods(list,index,src);
	 
	 
	 
	 

	if(jpm->ret==0){
		
		addr+=jpm->code_len;
		addr+=no->code_index+4;
		addr=~addr;
	    int codex =no->len_code-4;
    	memcpy(&no->code[codex],&addr,4);

		//	printf("setcall   ===2  === %d\n",addr);
	}else if(jpm->ret==1){
		
		addr+=jpm->code_len;
		addr+=count-no->code_index+1;
	    int codex =no->len_code-4;
	//	printf("setcall   ===1  === %d\n",addr);
    	memcpy(&no->code[codex],&addr,4);
		
		
	}
	

	
	
	
}




void MOVadder(struct Arraylist *  list){
			//printf("MOVadder   ------\n");
	int i=1,j,res=0;
	
	for(;i<list->length;i++){
	
	    methods mode =getarray(list,i); 
		 int conut=computersAdder(i+1,list);
		 
		 for(j=0;j<mode->line->length;j++){
		 nodes no   =getarray(mode->line,j);
	        if(AdderaADD(conut,mode->code_len,no)!=0){//下面处理call jmp等计算
				
				
				res =areJPM(no);
				if(res==1){ //JPM
					
					
					setJPM(mode->line,j);
					
					
				}else if(res==2){ //CALL
					
					setcall(list,no,i,mode->code_len);
					
				}
				
				
				//printf("MOVadder   1\n");
				
			}
	    //for()
	
		 }
	 
	
	
	}
	
	
}





void setcodes( struct Arraylist * list){
    	int i=0,j=0;
		//jpm=0
	  for(;i<list->length;i++){
	   methods mode =getarray(list,i); 
	    if(strcmp(mode->name,"start")==0&&i==0){
		//	printf("start\n");
			ret jpm= formethods(list,i,"main");
			
		
		  //  printf("start %d \n",jpm->code_len);
			emit(mode->code_len,mode->start);
		    int addr=jpm->code_len+16;
			memcpy(&arcs->code[1],&addr,4);
			continue;
		}
		//printf("%s \n",mode->name);
		for(j=0;j<mode->line->length;j++){
			
			 nodes no   =getarray(mode->line,j);
			if(no->len_code!=0){
				//printf("%s \n",no->asmscode);
				if(atoi(no->asmscode)!=END)
				 emit(no->len_code,no->code);
			}
			
		}
		
	   
	  
	  }
	
}









void ir_asm(char * file)
{
	arcs=malloc(sizeof(arcs));
	arcs->code_len=arcs->rdate_len=0;
	
	mey=malloc(sizeof(memoryco));
	mey->code_len=0;
	mey->memoryline=inif();
	mey->len=2024;
	FILE *fp;
	
    fp = fopen(file, "rb");


   if (fp == NULL) {
      printf( "Failed to open file: \n");
      return 1;
    }

  char * buf=malloc(20460);
  readfile(fp,buf,20460);
  struct Arraylist * methodlist= readMode(buf);

enterSet(methodlist);

 methodlist=sequence(methodlist);
MOVadder(methodlist);

printfms(methodlist);
printfx86(mey->code_len,mey->code,0);
setcodes(methodlist);

//printf("%s \n",buf);


free(buf);

fclose(fp);



}