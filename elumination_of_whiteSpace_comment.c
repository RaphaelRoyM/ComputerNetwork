#include<stdio.h>
#include<ctype.h>
int main(int argc, char *argv[]){
  char ch1,ch2;
  FILE *fp1=fopen(argv[1],"r");
  FILE *fp2=fopen("comment_white_space_removed","w");
  while((ch1=fgetc(fp1))!=EOF){
    if(ch1=='\n'){
      continue;
    }
    if(isspace(ch1)){
      continue;
    }
    if(ch1=='/'){
      ch2 = fgetc(fp1);
      if(ch2=='/'){
        while((ch1=fgetc(fp1))!='\n');
      }
      else if(ch2=='*'){
        while((ch1=fgetc(fp1))!='*'&&(ch2=fgetc(fp1))!='/'){
          ungetc(ch2,fp1);
        }
      }
    }
    else{
      fprintf(fp2,"%c",ch1);
    }
  }
}
