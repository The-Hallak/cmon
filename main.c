#include<stdio.h>
#include"headers/tree.h"
#include<stdlib.h>
#include<unistd.h>

int main(){
  
  Cmon* myTree=createCmon();
  CmonData* data1=createData("a",(void*)"hello",STRING_TYPE);
  CmonData* data2=createData("b",(void*)"hello",STRING_TYPE);
  int temp=5;
  CmonData* data3=createData("c",(void*)&temp,INT_TYPE);
  CmonData* data4=createData("d",(void*)"hello",STRING_TYPE);
  CmonData* data5=createData("e",(void*)"hello",STRING_TYPE);
  addCmon(myTree,data2);
  addCmon(myTree,data4);
  addCmon(myTree,data1);
  addCmon(myTree,data3);
  addCmon(myTree,data5);
  printTree(myTree);
  
  return 0;
}
