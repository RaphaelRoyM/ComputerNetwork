#include<stdio.h>
int main(){
  char str[100];
  printf("enter the string for change case:\t");
  scanf("%s",str);
  
  for(int i=0;str[i]!='\0';i++){
    if(str[i]>='a'&& str[i]<='z'){
      str[i]=str[i]-32;
    }
    else if(str[i]>='A'&&str[i]<='Z'){
      str[i]=str[i]+32;
    }
  }
  printf("converted string is %s\n",str);
  return 0;
}


