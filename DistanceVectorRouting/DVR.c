#include<stdio.h>
struct routers{
  int D[20];
  int AN[20];
}
node[20];

int main(){
  int CM[20][20],n;
  printf("enter the no of routers\n");
  scanf("%d",&n);
  
  printf("enter the cost matrix\n");
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      scanf("%d",&CM[i][j]);
      CM[i][i]=0;
      node[i].D[j]=CM[i][j];
      node[i].AN[j]=j;
    }  +++++++++++++++++++++++++++++++++++++++++++++
  }
  
  
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      for(int k=0;k<n;k++){
        if(node[i].D[j]>CM[i][k]+node[k].D[j]){
          node[i].D[j]=CM[i][k]+node[k].D[j];
          node[i].AN[j]=k;
        }
      }
    }
  }
  
  for(int i=0;i<n;i++){
    printf("\nRouter%d\n",i+1);
    for(int j=0;j<n;j++){
      printf("\nRouter%d via %d        distance : %d",j+1,node[i].AN[j]+1,node[i].D[j]);
    }
  }
  printf("\n");
  return 0;
}