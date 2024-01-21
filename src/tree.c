#include "../headers/tree.h"
#include "../headers/data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

struct CmonNode{
  struct CmonNode* parent;
  struct CmonNode* leftChild;
  struct CmonNode* rightChild;
  int leftDepth,rightDepth;
  CmonData* data;
};

struct Cmon{
  CmonNode* head;
};

Cmon* createCmon(){
  Cmon* newCmon=(Cmon*)malloc(sizeof(Cmon));
  if(newCmon==NULL)return NULL;
  newCmon->head=NULL;
  return newCmon;
}

CmonNode* createNode(CmonData* data, CmonNode*parent){
  CmonNode* newNode=(CmonNode*)malloc(sizeof(CmonNode));
  if(newNode==NULL)return NULL;
  newNode->parent=parent;
  newNode->leftChild=NULL;
  newNode->rightChild=NULL;
  newNode->data=data;
  newNode->leftDepth=0;
  newNode->rightDepth=0;
  return newNode;
}

CmonNode* getLargestNode(CmonNode* currentNode){
  if(currentNode==NULL)return NULL;
  while(currentNode->rightChild!=NULL)currentNode=currentNode->rightChild;
  return currentNode;
}
CmonNode* getSmallestNode(CmonNode* currentNode){
  if(currentNode==NULL)return NULL;
  while(currentNode->leftChild!=NULL)currentNode=currentNode->leftChild;
  return currentNode;
}

int max(int a,int b){
  if(a>b)return a;
  return b;
}
void leftRotation(CmonNode** currentNode){
  CmonNode* rChild=(*currentNode)->rightChild;
  CmonNode* parent=(*currentNode)->parent;
  (*currentNode)->rightChild=rChild->leftChild;
  if(rChild->leftChild!=NULL)
    rChild->leftChild->parent=(*currentNode);
  (*currentNode)->rightDepth=rChild->leftDepth;
  (*currentNode)->parent=rChild;
  rChild->leftChild=*currentNode;
  rChild->leftDepth=max((*currentNode)->leftDepth,(*currentNode)->rightDepth)+1;
  if(parent!=NULL){
    if(parent->leftChild==*currentNode){
      parent->leftChild=rChild;
      parent->leftDepth=max(rChild->leftDepth,rChild->rightDepth)+1;
    }else{
      parent->rightChild=rChild;
      parent->rightDepth=max(rChild->leftDepth,rChild->rightDepth)+1;
    }
  }
  rChild->parent=parent;
  *currentNode=rChild;
}

void rightRotation(CmonNode** currentNode){
  CmonNode* lChild=(*currentNode)->leftChild;
  CmonNode* parent=(*currentNode)->parent;
  (*currentNode)->leftChild=lChild->rightChild;
  (*currentNode)->leftDepth=lChild->rightDepth;
  if(lChild->rightChild!=NULL)
    lChild->rightChild->parent=(*currentNode);
  (*currentNode)->parent=lChild;
  lChild->rightChild=*currentNode;
  lChild->rightDepth=max((*currentNode)->leftDepth,(*currentNode)->rightDepth)+1;
  if(parent!=NULL){
    if(parent->leftChild==*currentNode){
      parent->leftChild=lChild;
      parent->leftDepth=max(lChild->leftDepth,lChild->rightDepth)+1;
    }else{
      parent->rightChild=lChild;
      parent->rightDepth=max(lChild->leftDepth,lChild->rightDepth)+1;
    }
  }
  lChild->parent=parent;
  *currentNode=lChild;
}

int addCmonNode(CmonNode** currentNode,CmonNode*parent,CmonData*data){
  if(currentNode==NULL)return -1;
  if(*currentNode==NULL){
    *currentNode=createNode(data,parent);
    return currentNode==NULL?-1:0;
  }
  int cmp=strcmp(getKey((*currentNode)->data),getKey(data));
  if(cmp==0){
    return -2;
  }else if(cmp<0){
    (*currentNode)->rightDepth=1+addCmonNode(&(*currentNode)->rightChild,*currentNode,data);
    if((*currentNode)->rightDepth<=0)return (*currentNode)->rightDepth-1;
  }else{
    (*currentNode)->leftDepth=1+addCmonNode(&(*currentNode)->leftChild,*currentNode,data);
    if((*currentNode)->leftDepth<=0)return (*currentNode)->leftDepth-1;
  }
  int difDepth=(*currentNode)->leftDepth-(*currentNode)->rightDepth;
  if(abs(difDepth)<2){
    return max((*currentNode)->leftDepth,(*currentNode)->rightDepth);
  }
  if(difDepth<0){
    if((*currentNode)->rightChild->leftDepth >(*currentNode)->rightChild->rightDepth){
      rightRotation(&(*currentNode)->rightChild);
    }
    leftRotation(currentNode);
  }else{
    if((*currentNode)->leftChild->rightDepth >(*currentNode)->leftChild->leftDepth){
      leftRotation(&(*currentNode)->leftChild);
    }
    rightRotation(currentNode);
  }

  return max((*currentNode)->leftDepth,(*currentNode)->rightDepth);
}

int addCmon(Cmon* tree,CmonData* data){
  if(tree==NULL)return -1; 
  if(tree->head==NULL){
    tree->head=createNode(data,NULL);
    return tree->head==NULL?-1:0;
  }
  return addCmonNode(&tree->head,NULL,data);
}

void printNode(CmonNode* currentNode){
  if(currentNode==NULL)return;
  printf("dif:%d\t",abs(currentNode->leftDepth-currentNode->rightDepth));
  printData(currentNode->data);
  printNode(currentNode->leftChild);
  printNode(currentNode->rightChild);
}

void printTree(Cmon* tree){
  if(tree==NULL)return;
  printNode(tree->head);
}
