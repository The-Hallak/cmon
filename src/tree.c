#include "../headers/tree.h"
#include "../headers/data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define NODE_EXIST_ERROR -2
#define NODE_GEN_ERROR -1
#define NODE_NOT_EXIST_ERROR -3

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
  newNode->leftDepth=1;
  newNode->rightDepth=1;
  return newNode;
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

void balance(CmonNode** currentNode){
  int difDepth=(*currentNode)->leftDepth-(*currentNode)->rightDepth;
  if(abs(difDepth)<2)return;
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
}

int calculateDepth(CmonNode*currentNode){
  if(currentNode==NULL)return 0;
  return max(currentNode->leftDepth,currentNode->rightDepth);
}

int addCmonNode(CmonNode** currentNode,CmonNode*parent,CmonData*data){
  if(currentNode==NULL)return NODE_GEN_ERROR;
  if(*currentNode==NULL){
    *currentNode=createNode(data,parent);
    return currentNode==NULL?NODE_GEN_ERROR:1;
  }
  int cmp=strcmp(getKey((*currentNode)->data),getKey(data));
  if(cmp==0){
    return NODE_EXIST_ERROR;
  }else if(cmp<0){
    int ret=addCmonNode(&(*currentNode)->rightChild,*currentNode,data);
    if(ret<0)return ret;
    (*currentNode)->rightDepth=1+ret;
  }else{
    int ret=addCmonNode(&(*currentNode)->leftChild,*currentNode,data);
    if(ret<0)return ret;
    (*currentNode)->leftDepth=1+ret;
  }
  int difDepth=(*currentNode)->leftDepth-(*currentNode)->rightDepth;
  if(abs(difDepth)<2){
    return calculateDepth(*currentNode);
  }
  balance(currentNode);
  return calculateDepth(*currentNode);
}

int addCmon(Cmon* tree,CmonData* data){
  if(tree==NULL)return NODE_GEN_ERROR; 
  if(tree->head==NULL){
    tree->head=createNode(data,NULL);
    return tree->head==NULL?NODE_GEN_ERROR:0;
  }
  return addCmonNode(&tree->head,NULL,data);
}

int deleteCmonNode(CmonNode**currentNode,char* key){
  if(currentNode==NULL)return NODE_GEN_ERROR;
  if(*currentNode==NULL)return NODE_NOT_EXIST_ERROR;
  int cmp=strcmp(getKey((*currentNode)->data),key);
  if(cmp<0){
    int ret=deleteCmonNode(&(*currentNode)->rightChild,key);
    if(ret<0)return ret;
    (*currentNode)->rightDepth=ret+1;
  }else if(cmp>0){
    int ret=deleteCmonNode(&(*currentNode)->leftChild,key);
    if(ret<0)return ret;
    (*currentNode)->leftDepth=ret+1;
  }
  if(cmp!=0){
    balance(currentNode);
    return calculateDepth(*currentNode);
  }
  //in case the node has one child or no child
  if((*currentNode)->leftChild==NULL){
    CmonNode* temp=*currentNode;
    if(temp->rightChild!=NULL) temp->rightChild->parent=temp->parent;
    if(temp->parent->leftChild==temp){
      temp->parent->leftChild=temp->rightChild;
      temp->parent->leftDepth=temp->rightDepth;
    }else{
      temp->parent->rightChild=temp->rightChild;
      temp->parent->rightDepth=temp->rightDepth;
    }
    *currentNode=temp->rightChild;
    free(temp);
    return calculateDepth(*currentNode);

  }else if((*currentNode)->rightChild==NULL){
    CmonNode* temp=*currentNode;
    if(temp->leftChild!=NULL) temp->leftChild->parent=temp->parent;
    if(temp->parent->leftChild==temp){
      temp->parent->leftChild=temp->leftChild;
    }else{
      temp->parent->rightChild=temp->leftChild;
    }
    *currentNode=temp->leftChild;
    free(temp);
    return calculateDepth(*currentNode);
  }
  
  CmonNode* candidate=(*currentNode)->leftChild;
  while(candidate->rightChild!=NULL)candidate=candidate->rightChild;

  (*currentNode)->data=candidate->data;
  if(candidate->parent->leftChild==candidate){
    candidate->parent->leftChild=candidate->leftChild;
    candidate->parent->leftDepth=candidate->leftDepth;
  }else{
    candidate->parent->rightChild=candidate->leftChild;
    candidate->parent->rightDepth=candidate->leftDepth;
  }
  if(candidate->leftChild!=NULL)candidate->leftChild->parent=candidate->parent;
  CmonNode*temp=candidate->parent;
  free(candidate);
  while(temp!=(*currentNode)->parent){
    temp->leftDepth=calculateDepth(temp->leftChild);  
    temp->rightDepth=calculateDepth(temp->rightChild);  
    balance(&temp);
    temp=temp->parent;
  }
  return calculateDepth(*currentNode);
}

int deleteCmon(Cmon*tree,char*key){
  if(tree==NULL)return NODE_GEN_ERROR;
  return deleteCmonNode(&(tree->head),key);
}

void printNode(CmonNode* currentNode){
  if(currentNode==NULL)return;
  printData(currentNode->data);
  printNode(currentNode->leftChild);
  printNode(currentNode->rightChild);
}

void printTree(Cmon* tree){
  if(tree==NULL)return;
  printf("{");
  printNode(tree->head);
  printf("}");
}
