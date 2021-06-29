#include "readfile.h"  // malloc



void readfile(FILE *fp,char * buf,int MAX_LINE){

int len=0;
 /*while(fgets(buf,MAX_LINE,fp) != NULL)
 {
 len = strlen(buf);
 buf[len-1] = '\0'; 
 printf("%s %d \n",buf,len - 1);
 }*/
 
    fread(buf, MAX_LINE, 1, fp);

 

} 

char * returnsCH(char * code,int b,int e){
	//printf("returnsCH======== %d===%d======\n",b,e);
	char * t=(char *)malloc(20);
	 if(!t){
		 exit(-1);
	 }
	  int j=0,i;
         
	 for(i=b;i<e;i++,j++){
		 t[j]=code[i];
	 }

	 t[j]='\0';
	 return t;
}

void printflin(struct Arraylist * list){
	//printf("printflin=========%d====\n",list->length);
	char * txt=NULL;
	int i;
//	for( i=0;i<list->length;i++){
	//txt=getarray(list,i);
		//printf("%s \n",txt);
	//}
	//txt=NULL;
}





void printfmethods( methods  mode){
	//printf("methods=========%s====\n",mode->name);
	struct Arraylist * list=mode->line;
	int i;
	//for( i=0;i<list->length;i++){
//	nodes no=getarray(list,i);
  //   printf("%s     %d \n",no->asmscode,no->arenode);
	//}
	
}



int areStart(char * txt){
	
	int len=strlen(txt);
	//printf("areStart====%s  %d\n",txt,len);
	int i;
	for( i=0;i<len;i++){
		if(txt[i]==':'){
			if(txt[i-1]=='#')
		     return 2;
		    else
			return 1;
		}
	}
	
	
	return 0;
	
}



struct Arraylist *  modelsplit(struct Arraylist * list){
//	printf("========modelsplit=====\n");
	
 struct Arraylist * methodlist;
		 methodlist=inif();
char * txt=NULL;
methods mode=NULL;
	int i,rets;
	//printf("========modelsplit===1==\n");
	for( i=0;i<list->length;i++){
	txt=getarray(list,i);
//	printf("========modelsplit===2==\n");
	rets=areStart(txt);
	 if(rets==1){
		// printf("========modelsplit===4==\n");
		if(mode==NULL){
			mode=malloc(sizeof (method));
			if(!mode)
				exit(-1);
		}else{
			 mode=malloc(sizeof (method));
			  if(!mode)
				exit(-1);  
		}
		
		//strcpy(,txt);
		
		 int ii=0,con=strlen(txt);
		  char * name=NULL;
		   int ij=0;
	       for(;ii<con;ii++){
	     //  printf("%x %c\n",mode1->name[ii],mode1->name[ii]);
	            if(txt[ii]!='\n'&&txt[ii]!=':'&&txt[ii]!=' '){
					// printf("----------\n");
	              name=malloc(con-ii);
	               
				 for(;ij<con-ii+1;ii++,ij++){
				  name[ij]=txt[ii];
				  printf("%c ", name[ij]);
				//  printf("%c - %d  %d-\n",name[ij],ii,con);
				 }
				 
				 
				 
				 
				 
				// char * p=mode1->name;
				 // mode1->name=name;
				  // printf("%s %d\n", mode1->name,strlen( mode1->name));
	             //free(p);
			//	 printf("------2---%d----%s-------\n",strlen(name),name);
				
				}
		   }
		    name[ij]='\0';
		//printf("------111111111-------%s-------\n",name);
		 mode->name=name;
    	 mode->code_len=0;
		 mode->line=inif();
		 add(methodlist,mode);  
	 }else{

		 nodes nodeire=malloc(sizeof (node)); 
		 if(!nodeire)
		 exit(-1);
	    //strcpy( ,txt);
		nodeire->asmscode=txt;
		 		 //printf("========modelsplit===3==\n");
		 add(mode->line,nodeire); 
		  if(rets==2){
			   nodeire->arenode=1;
		  }
	 }
	
	
	
	
	
		//printf("%s \n",txt);
	}
	txt=NULL;
	 mode=NULL;
return methodlist;
}	



struct Arraylist *  readMode(char * buf)
{
	     struct Arraylist * list;
		 list=inif();
	     int len=strlen(buf);
		 int start=0;
		 int i;
	    for( i=0;i<len;i++){
			if(buf[i]=='\r'&&buf[i+1]=='\n'){	
			  char * txt=returnsCH(buf,start,i);
			  add(list,txt);  
			  start=i+2;
			}
		}
	   
	
	   
	   
	//   printflin(list);
	  
   struct Arraylist * methodlist=modelsplit(list);
   free(list->obj);
   free(list);
//	printf("===%d \n",methodlist->length);
	methods mode=getarray(methodlist,1); //下面是转成机器码
	
	//printfmethods(mode);
	return methodlist;
}





char * getschar(int b,int e,char * p){
	
	char * ps=malloc((e-b)+1);
	int i,size=strlen(p),j=0;
	
	for(i=b;i<e;i++){
	  ps[j]=p[i];
            //  printf("%c",ps[j]);
j++;
	}
	ps[j]='\0';
	//printf("getschar====%s\n",ps);
	
	return  ps;
	
}




int cCount(char c,char * p){
	
	int size=strlen(p);
   int i,count=0;
     
	for(i=0;i<size;i++){
		if(p[i]==c)
		count++;

	}
	return count;


}


struct Arraylist *  splitchar(char  * p,char c){
		//printf("replace===============\n");
	struct Arraylist * list;
	 list=inif();
	int s=strlen(p);
	int i,j=0;
	int size=cCount(c,p);
	int * INTS=(int *)malloc(size*sizeof(int));
	for(i=0;i<s;i++){
		if(p[i]==c){
			INTS[j]=i;
		   j++;
		}
		
	}
	//printf("replace========%s=======%d\n",p,size);
	int b=0;
	
	for(i=0;i<size;i++){
//printf("replace=========%d==%d===\n",b,INTS[i]);	
          char * ps=getschar(b,INTS[i],p);
        	//printf("%s \n",ps);
          b=INTS[i]+1;
//printf("replace=====%s=====%d==%d===\n",ps,b,INTS[i]);	
		
		 add(list,ps);
	}
	char * ps=getschar(b,s,p);
	//printf("%s \n",ps);
    add(list,ps);
		//printf("replace=====%s==========\n",ps);	
	free(INTS);
	
		//printf("replace=====end==========\n");	
	return list;
}




