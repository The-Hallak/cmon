#ifndef DATA_H
#define DATA_H

typedef struct CmonData CmonData;

CmonData* createData(char* key,void* value,int type);

char* getKey(CmonData*);

void* getValue(CmonData*);

void printData(CmonData*);

int isString(CmonData*);

int isCmon(CmonData*);

int isInt(CmonData*);

int isStringArray(CmonData*);

int isCmonArray(CmonData*);

int isIntArray(CmonData*);

#ifdef INTERNAL_DEFS

#endif

#endif
