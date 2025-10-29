/*
  oblc - open bracket line count
  OpenBracket - array that stores all open bracket read. it is poped when close bracket is read
  lc - line count
  error - if 0 brackets are balance
*/
#include<stdio.h>
char OpenBracket[30]={0};
int lc=1, oblc[30], top=-1,error=0;

int isMatching(char openB,char closeB){
  return ((openB=='('&&closeB==')')||(openB=='{'&&closeB=='}')||(openB=='['&&closeB==']'));
}
int main(){
  char ch;
  FILE *fp=fopen("Input_paranthesis.txt","r");
  while((ch=fgetc(fp))!=EOF){
    switch(ch){
    
      case '\n':
        lc++;
        break;
      
      case '(':
      case '[':
      case '{':
        OpenBracket[++top]=ch;
        oblc[top]=lc;
        break;
      
      case ')':
      case ']':
      case '}': 
        if(top!=-1){
          char openB=OpenBracket[top];
          char closeB=ch;
          if(isMatching(openB,closeB)){
            top--;
          }
          else{
            printf("At line number %d 'open bracket mismatch %c' for %c \n",lc,OpenBracket[top],ch);
            top--;
            error=1;
          }
        }
        else{
          printf("At line number %d 'open bracket missing' for %c \n",lc,ch);
          error=1;
        }
        break;
    }
  }
  while(top!=-1){
    ch=OpenBracket[top--];
    printf("At line number %d 'close bracket missing' for %c \n",oblc[top+1],ch);
    error=1;
  }
  if(error==0){
    printf("All brackets are balanced\n");
  }
}
