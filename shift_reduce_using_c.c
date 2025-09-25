/*
e-.e+e
e->e*e
e->(e)
e->i
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char input[20];
int top=0;
char stack[50];
int j=0;
int slno=0;

void reduce(){
	int z=0;
	for(z=0;z<top;z++){
		if(stack[z]=='i'){
			stack[z]='E';
			stack[z+1]='\0';
			printf("%d\t$%s\t%s$\tReduce E->i\n",slno,stack,input);
			slno++;
		}
		
	}
	for(z=0;z<top;z++){
		if(stack[z]=='(' && stack[z+1]=='E' && stack[z+2]==')'){
			stack[z]='E';
			stack[z+1]='\0';
			printf("%d\t$%s\t%s$\tReduce E->(E)\n",slno,stack,input);
			top-=2;
			slno++;
		}
		
	}
	for(z=0;z<top;z++){
		if(stack[z]=='E' && stack[z+1]=='+' && stack[z+2]=='E'){
			stack[z]='E';
			stack[z+1]='\0';
			printf("%d\t$%s\t%s$\tReduce (E-> E+E)\n",slno,stack,input);
			top-=2;
			slno++;
		}
		
	}
	for(z=0;z<top;z++){
		if(stack[z]=='E' && stack[z+1]=='*' && stack[z+2]=='E'){
			stack[z]='E';
			stack[z+1]='\0';
			printf("%d\t$%s\t%s$\tReduce (E-> E*E)\n",slno,stack,input);
			top-=2;
			slno++;
		}
		
	}
}

int main(){
	printf("enter the input string\n");
	scanf("%s",input);
	
	printf("\nslno\tstack\tinput\taction\n");
	while(input[j]!='\0'){
		char ch=input[j];
		stack[top++]=input[j++];
		stack[top]='\0';
		input[j-1]='_';
		printf("%d\t$%s\t%s$\tSHIFT %c\n",slno,stack,input,ch);
		slno++;
		reduce();
	}
	if(stack[0]=='E' && stack[1]=='\0'){
		printf("\nAccepted\n");
	}
	else{
		printf("\nRejected\n");
	}
}
