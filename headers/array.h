#ifndef ARRAY_H
#define ARRAY_H

#include "tree.h"

typedef struct Array Array;

Array* createArray(long long* array,int size);

int resize(Array** arrayPtr,int newSize,long long value);

int addElement(Array* array,long long  value);

long long getElement(Array* array,unsigned int idx);

int getSize(Array* array);

int getCapacity(Array* array);

int destroyArray(Array* array);

#endif
