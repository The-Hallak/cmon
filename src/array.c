#include "../headers/array.h"
#include "../headers/tree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MALLOC_ERROR -69

struct Array{
  int size,capacity;
  int type;
  union {
    long long * integer;
    char* string;
    Cmon* cmon;
    struct Array* array;
  };
};


int min(int a,int b){
  if(a<b)return a;
  return b;
}

Array* createArray(long long* array,int size){
  Array* newArray=malloc(sizeof(Array));
  if(newArray==NULL)return newArray;
  newArray->size=size;
  newArray->capacity=size+(size==0);
  newArray->type=INT_TYPE;
  newArray->integer=(long long*)malloc(newArray->capacity*sizeof(long long ));
  if(newArray==NULL){
    free(newArray);
    return NULL;
  }
  for(int i=0;i<size;i++){
    newArray->integer[i]=array[i];
  }
  return newArray;
}

int resize(Array** arrayPtr,int newSize,long long newValue){
  Array* array=*arrayPtr;
  bool canExtend= newSize>=array->size&&newSize<=array->capacity;
  if(canExtend){
    for(int i=array->size;i<newSize;i++)
      array->integer[i]=newValue;
    array->size=newSize;
    return 0;
  }
  bool shrinking=newSize<array->size;
  if(shrinking){
    array->size=newSize;
    return 0;
  }
  long long* newArray=(long long*)malloc(newSize*sizeof(long long ));
  if(newArray==NULL){
    free(newArray);
    return MALLOC_ERROR;
  }
  long long* temp=array->integer;
  for(int i=0;i<array->size;i++){
    newArray[i]=temp[i];
  }
  for(int i=array->size;i<newSize;i++){
    newArray[i]=newValue;
  }
  array->integer=newArray;
  array->size=newSize;
  array->capacity=newSize;
  //the error occure here
  free(temp);
  return 0;
}

int changeSize(Array** arrayPtr,int newCapacity){
  Array* array=*arrayPtr;
  long long* newArray=(long long*)malloc(newCapacity*sizeof(long long ));
  if(newArray==NULL){
    free(newArray);
    return MALLOC_ERROR;
  }
  long long* temp=array->integer;
  for(int i=0;i<min(array->size,newCapacity);i++){
    newArray[i]=temp[i];
  }
  array->integer=newArray;
  array->capacity=newCapacity;
  free(temp);
  return 0;
}

int addElement(Array* array,long long value){
  if(array->capacity==array->size){
    int ret=changeSize(&array,array->size*2);
    if(ret<0)return ret;
  }
  array->integer[array->size]=value;
  array->size++;
  return 0;
}

long long getElement(Array*array,unsigned int idx){
  if(idx>=array->size)return 0;
  return array->integer[idx]; 
}

int getSize(Array*array){
  if(array==NULL)return 0;
  return array->size;
}
int getCapacity(Array*array){
  if(array==NULL)return 0;
  return array->capacity;
}
int destroyArray(Array* array){
  if(array==NULL)return -1;
  if(array->integer!=NULL)
    free(array->integer);
  free(array);
  return 0;
}
