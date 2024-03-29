#include "../headers/data.h"
#include "../headers/types.h"
#include "../headers/tree.h"
#include <stdlib.h>
#include <stdio.h>

struct CmonData{
  char* key;
  void* value;
  int type;
};

CmonData* createData(char* key,void* value,int type){
  CmonData* newData=(CmonData*)malloc(sizeof(CmonData));
  if(newData==NULL)return NULL;
  newData->key=key;
  newData->value=value;
  newData->type=type;
  return newData;
}

char* getKey(CmonData* data){
  if(data==NULL)return NULL;
  return data->key;
}

void* getValue(CmonData*data){
  if(data==NULL)return NULL;
  return data->value;
}

int isString(CmonData*data){
  if(data==NULL)return -1;
  return data->type==STRING_TYPE;
}
int isInt(CmonData*data){
  if(data==NULL)return -1;
  return data->type==INT_TYPE;
}
int isSTringArray(CmonData*data){
  if(data==NULL)return -1;
  return data->type==STRING_ARRAY_TYPE;
}
int isIntArray(CmonData*data){
  if(data==NULL)return -1;
  return data->type==INT_ARRAY_TYPE;
}
int isCmonArray(CmonData*data){
  if(data==NULL)return -1;
  return data->type==CMON_ARRAY_TYPE;
}
int isCmon(CmonData*data){
  if(data==NULL)return -1;
  return data->type==CMON_TYPE;
}

void printData(CmonData*data){
  printf("\"%s\":",data->key);
  switch(data->type){
    case STRING_TYPE:
      printf("\"%s\"",(char*)data->value);
      break;
    case INT_TYPE:
      printf("%d",*(int*)data->value);
      break;
    case CMON_TYPE:
      printTree((Cmon*)data->value);
      break;
  }
  printf(",");
}
