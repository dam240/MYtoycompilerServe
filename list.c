#include "list.h"
#include <stdio.h>
#include <stdlib.h>





void * init(int size){
void * str= malloc(sizeof(size));
 if(!str){
   exit(0);
  }
return  str;
} 


struct Arraylist * inif(){
struct Arraylist * list=(struct Arraylist *)init(sizeof(struct Arraylist));
list->length=0;
list->size=0;
return  list;
}


void add(struct Arraylist * list,void * obj){
   if(list->size==0){
      list->list=1;
     list->obj= malloc(sizeof(struct list)*20);
     if(!list->obj){
       printf("nc");
      exit(0);
     }
    }

   if(list->size==list->length){
     list->obj=realloc(list->obj,sizeof(struct list)*(list->size+20));
     if(!list->obj){
       printf("nc");
      exit(0);
      }
     list->size+=20;
    }
 
  struct list * ma =( struct list *)list->obj;
  ma[list->length].value=obj;
  list->length++;
}



void addALL(struct Arraylist * list,void * obj,int size,int len){
   if(list->size!=0||list->length!=0)
      return;
     list->obj=obj;
     list->size=size;
     list->length=len;
printf("len =%d \n",len);
}


void * getarray(struct Arraylist * list,int index){
  if(list->length<0||index>list->length||list->list!=1){
     
	 printf("getarray---------\n");
	 exit(0);
  }
  struct list * obj= ( struct list *)list->obj;
   return obj[index].value;
}


void * getObj(struct Arraylist * list){
  if(list->list!=0)
        exit(0);
  return list->obj;
}






