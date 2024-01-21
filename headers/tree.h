#ifndef DEFINES_H
#define DEFINES_H

#include "types.h"
#include "data.h"

typedef struct CmonNode CmonNode;

typedef struct Cmon Cmon;

Cmon* createCmon();

int addCmon(Cmon* tree,CmonData* data);

void printTree(Cmon* tree);

#endif
