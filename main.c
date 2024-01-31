#include<stdio.h>
#include"headers/tree.h"
#include<stdlib.h>
#include<unistd.h>
#include"headers/array.h"

int main(){
  Array* arr=createLongArray(5,10);
  for(int i=0;i<getSize(arr);i++){
    printf("arr[%d]=%lld\n",i,getLong(arr,i));
  }
  destroyArray(arr);
  
  arr=createArrayArray(5,createCharArrayFromArray("mohamad",sizeof("mohamad")));
  for(int i=0;i<getSize(arr);i++){
    for(int j=0;j<getSize(getArray(arr,i));j++){
      printf("%c",getChar(getArray(arr,i),j));
    }
    printf("\n");
  }
  destroyArray(arr);
  return 0;
}
