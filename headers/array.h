#ifndef ARRAY_H
#define ARRAY_H

#include "tree.h"

typedef struct Array Array;

Array* createLongArrayFromArray(long long*array,int size);

Array* createLongArray(int size,long long defValue);

int arrayAddLong(Array* array,long long value);

long long getLong(Array* array,unsigned int idx);


Array* createCharArrayFromArray(char* array,int size);

Array* createCharArray(int size,char defValue);

int arryAddChar(Array* array,char value);

char getChar(Array* array,unsigned int idx);


Array* createArrayArrayFromArray(Array* array,int size);

Array* createArrayArray(int size,Array* defValue);

int arrayAddArray(Array* array,Array value);

Array* getArray(Array* array,unsigned int idx);


Array* createCmonArrayFromArray(Cmon* array,int size);

Array* createCmonArray(int size,Cmon* defValue);

int arrayAddCmon(Array* array,Cmon value);

Cmon* getCmon(Array* array,unsigned int idx);


int resize(Array** arrayPtr,int newSize,long long value);

int getSize(Array* array);

int getCapacity(Array* array);

int destroyArray(Array* array);

#endif
