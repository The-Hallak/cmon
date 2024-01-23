#include<stdio.h>
#include"headers/tree.h"
#include<stdlib.h>
#include<unistd.h>
#include"headers/array.h"

int main(){
  
  //Cmon* myTree=createCmon();
  //CmonData* data1=createData("a",(void*)"hello",STRING_TYPE);
  //CmonData* data2=createData("b",(void*)"hello",STRING_TYPE);
  //CmonData* data3=createData("c",(void*)"hello",STRING_TYPE);
  //CmonData* data4=createData("d",(void*)"hello",STRING_TYPE);
  //int tempNumber=1;
  //Cmon*myTree1=createCmon();
  //addCmon(myTree1,data2);
  //CmonData* data5=createData("e",(void*)&tempNumber,INT_TYPE);
  //CmonData* data6=createData("Cmon",(void*)myTree1,CMON_TYPE);
  //addCmon(myTree,data2);
  //addCmon(myTree,data1);
  //addCmon(myTree,data4);
  //addCmon(myTree,data3);
  //addCmon(myTree,data5);
  //addCmon(myTree,data6);
  //addCmon(myTree1,data1);
  //printTree(myTree);
  //printf("\n");
  Array* myArray=createArray(NULL,0); 
  if(myArray==NULL){
    printf("error");
    return 0;
  }
  addElement(myArray,2);
  addElement(myArray,3);
  resize(&myArray,5,10);
  //printf("hello malloc\n"); fflush(stdout);
  //printf("size:%d,capacity:%d\n",getSize(myArray),getCapacity(myArray));
  //fflush(stdout);
  //for(int i=0;i<getSize(myArray);i++){
  //  printf("arr[%d]:%lld\n",i,getElement(myArray,i));
  //}

  destroyArray(myArray);
  return 0;
}
