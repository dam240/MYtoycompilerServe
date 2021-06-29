#include "elfFile.h"

int main(int argc,char *argv[]){


  char * filenasd=NULL;
  
if(argc>=4){

 if(compareNames("asm",argv[1])==1){
   if(compareNames("-o",argv[2])==1){

        filenasd=argv[3];
        int fsize=strlen(filenasd);
    if(filenasd[fsize-1]=='d'){
         if(filenasd[fsize-2]=='o'){
           if(filenasd[fsize-3]=='.'){
 printf("%s\n",filenasd);
}else{
 printf("文件不对 %s\n",filenasd);
 exit(-1);
        }

}else{
 printf("文件不对 %s\n",argv[3]);
 exit(-1);
        }

       }else{
 printf("文件不对%s\n",argv[2]);
 exit(-1);
        }
          

//compareNames(,"-d")





}else{
 printf("无法识别该命令  %s\n",argv[1]);
 exit(-1);

}

 
}else{
 printf("无法识别该命令len=%d   %s\n",strlen(argv[1]),argv[1]);
 exit(-1);

}
}else if(argc==2){

 if(strcmp(argv[1],"help")==0){

 printf("暂时不支持\n");
 exit(-1);
 
 }


}
outfile(filenasd);


// free(arcs);
//free(mey);


return 0;
}