#include "../headers/array.h"
#include "../headers/tree.h"
#include "../headers/types.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MALLOC_ERROR -69
#define INVALID_TYPE -420

struct Cmon{
  CmonNode* head;
};


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

Array* createArray(void* data,int size,int type,bool defaultValue){
  Array* newArray=malloc(sizeof(Array));
  if(newArray==NULL){
    free(newArray);
    return newArray;
  }
  newArray->size=size;
  newArray->capacity=size+(size==0);
  newArray->type=type;
  switch(type){
    case INT_TYPE:
      newArray->integer=(long long*)malloc(newArray->capacity*sizeof(long long ));
      if(newArray->integer==NULL){
        free(newArray->integer);
        free(newArray);
        return NULL;
      }
      if(!defaultValue){
        long long *longArray=(long long*)data;
        for(int i=0;i<size;i++){
          newArray->integer[i]=longArray[i];
        }
      }else{
        for(int i=0;i<size;i++){
          newArray->integer[i]=*(long long*)data;
        }
      }
      break;
    case STRING_TYPE:
      newArray->string=(char*)malloc(newArray->capacity*sizeof(char));
      if(newArray->string==NULL){
        free(newArray->string);
        free(newArray);
        return NULL;
      }
      if(!defaultValue){
        char*stringArray=(char*)data;
        for(int i=0;i<size;i++){
          newArray->string[i]=stringArray[i];
        }
      }else{
        for(int i=0;i<size;i++){
          newArray->string[i]=*(char*)data;
        }
      }
      break;
    case CMON_TYPE:
      newArray->cmon=(Cmon*)malloc(newArray->capacity*sizeof(Cmon));
      if(newArray->cmon==NULL){
        free(newArray->cmon);
        free(newArray);
        return NULL;
      }
      if(!defaultValue){
        Cmon* cmonArray=(Cmon*)data;
        for(int i=0;i<size;i++){
          newArray->cmon[i]=cmonArray[i];
        }
      }else{
        for(int i=0;i<size;i++){
          newArray->cmon[i]=*(Cmon*)data;
        }
      }
      break;
    case ARRAY_TYPE:
      newArray->array=(Array*)malloc(newArray->capacity*sizeof(Array));
      if(newArray->array==NULL){
        free(newArray->array);
        free(newArray);
        return NULL;
      }
      if(!defaultValue){
        Array* arrayArray=(Array*)data;
        for(int i=0;i<size;i++){
          newArray->array[i]=arrayArray[i];
        }
      }else{
        for(int i=0;i<size;i++){
          newArray->array[i]=*(Array*)data;
        }
      }
      break;
  }
  return newArray;
}

Array* createLongArray(int size, long long defValue){
  return createArray(&defValue,size,INT_TYPE,true);
}
Array* createLongArrayFromArray(long long* array,int size){
  return createArray(array,size,INT_TYPE,false);
}

Array* createCharArray(int size,char defValue){
  return createArray(&defValue,size,STRING_TYPE,true);
}
Array* createCharArrayFromArray(char* array,int size){
  return createArray(array,size,STRING_TYPE,false);
}

Array* createArrayArray(int size,Array* defValue){
  return createArray(defValue,size,ARRAY_TYPE,true);
}
Array* createArrayArrayFromArray(Array* array,int size){
  return createArray(array,size,ARRAY_TYPE,false);
}

Array* createCmonArray(int size,Cmon* defValue){
  return createArray(defValue,size,CMON_TYPE,true);
}
Array* createCmonArrayFromArray(Cmon* array,int size){
  return createArray(array,size,CMON_TYPE,false);
}
//TODO:types
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

int addElement(Array* array,void* value){
  if(array->capacity==array->size){
    int ret=changeSize(&array,array->size*2);
    if(ret<0)return ret;
  }
  switch(array->type){
    case INT_TYPE:
      array->integer[array->size++]=*(long long*)value;
      break;
    case STRING_TYPE:
      array->string[array->size++]=*(char*)value;
      break;
    case CMON_TYPE:
      array->cmon[array->size++]=*(Cmon*)value;
      break;
    case ARRAY_TYPE:
      array->array[array->size++]=*(Array*)value;
      break;
  }
  return 0;
}

int arrayAddLong(Array*array,long long value){
  if(array->type!=INT_TYPE)return INVALID_TYPE;
  return addElement(array,(void*)&value);
}

int arrayAddChar(Array*array,char value){
  if(array->type!=STRING_TYPE)return INVALID_TYPE;
  return addElement(array,(void*)&value);
}

int arrayAddArray(Array*array,Array value){
  if(array->type!=ARRAY_TYPE)return INVALID_TYPE;
  return addElement(array,(void*)&value);
}

int arrayAddCmon(Array* array,Cmon value){
  if(array->type!=CMON_TYPE)return INVALID_TYPE;
  return addElement(array,(void*)&value);
}


void* getElement(Array*array,unsigned int idx){
  if(idx>=array->size)return 0;
  switch(array->type){
    case INT_TYPE:
      return (void*)(array->integer+idx);
    case STRING_TYPE:
      return (void*)(array->string+idx);
    case CMON_TYPE:
      return (void*)(array->cmon+idx);
    case ARRAY_TYPE:
      return (void*)(array->array+idx);
    default:
      return NULL;
  }
}

long long getLong(Array*array,unsigned int idx){
  if(array->type!=INT_TYPE)return 0;
  long long* ret=(long long*)getElement(array,idx);
  if(ret==NULL)return 0;
  return *ret;
}

char getChar(Array*array,unsigned int idx){
  if(array->type!=STRING_TYPE)return 0;
  char* ret=(char*)getElement(array,idx);
  if(ret==NULL)return 0;
  return *ret;
}

Array* getArray(Array*array,unsigned int idx){
  if(array->type!=ARRAY_TYPE)return NULL;
  Array* ret=(Array*)getElement(array,idx);
  return ret;
}

Cmon* getCmon(Array*array,unsigned int idx){
  if(array->type!=CMON_TYPE)return NULL;
  Cmon* ret=(Cmon*)getElement(array,idx);
  return ret;
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
  if(array->type==INT_TYPE&&array->integer!=NULL)
    free(array->integer);
  if(array->type==STRING_TYPE&&array->string!=NULL)
    free(array->string);
  if(array->type==CMON_TYPE&&array->cmon!=NULL)
    free(array->cmon);
  if(array->type==ARRAY_TYPE&&array->array!=NULL)
    free(array->array);
  free(array);
  return 0;
}
