#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "treeStructure.h"
#include "buildTree.h"
#include "writeTree.h"
#include "destroyTree.h"
#include "tests.h"
#include "valueTree.h"

void taskOne(const int test){
  Node *head;
  head = makeNode( 0.0,0.0, 0 );
  if(test==1){
    makeChildren( head );
    makeChildren( head->child[0] );
    makeChildren( head->child[1] );
    makeChildren( head->child[2] );
    makeChildren( head->child[3] );
    destroyTree( head );
    return;
  }
  else{
    makeChildren( head );
    makeChildren( head->child[0] );
    makeChildren( head->child[3] );
    makeChildren( head->child[0]->child[1] );
    makeChildren( head->child[0]->child[2] );
    makeChildren( head->child[0]->child[3] );
    makeChildren( head->child[3]->child[0] );
    destroyTree( head );
    return;
  }
}

void tasktwo(const int test){
  Node *head;
  head = makeNode( 0.0,0.0, 0 );
  if(test==1){
    makeChildren( head );
    makeChildren( head->child[0] );
    makeChildren( head->child[1] );
    makeChildren( head->child[2] );
    makeChildren( head->child[3] );
    growTree( head,-1 );
    writeTree( head );
    destroyTree( head );
    return;
  }
  else {
    makeChildren( head );
    makeChildren( head->child[0] );
    makeChildren( head->child[1] );
    makeChildren( head->child[3] );
    makeChildren( head->child[0]->child[0] );
    makeChildren( head->child[0]->child[3] );
    makeChildren( head->child[1]->child[0] );
    makeChildren( head->child[1]->child[1] );
    makeChildren( head->child[1]->child[3] );
    makeChildren( head->child[3]->child[1] );
    makeChildren( head->child[3]->child[2] );
    growTree( head,-1 );
    writeTree( head );
    destroyTree( head );
    return;
  }
}

void taskThree(const int test, const int maxLevel){
  Node *head;
  head = makeNode( 0.0,0.0, 0 ); // level 0
  if(test==1){
    growTree( head,maxLevel ); // level 1
    growTree( head,maxLevel ); // level 2
    growTree( head,maxLevel ); // level 3
    growTree( head,maxLevel ); // level 4
    growTree( head,maxLevel ); // level 5
    destroyTree( head );
    return;
  }
  else if(test==2){
    growTree( head,maxLevel ); // level 1
    growTree( head,maxLevel ); // level 2
    growTree( head,maxLevel ); // level 3
    growTree( head,maxLevel ); // level 4
    growTree( head,maxLevel ); // level 5
    growTree( head,maxLevel ); // level 6
    destroyTree( head );
    return;
  }
  else if(test==3){
    growTree( head,maxLevel ); // level 1
    growTree( head,maxLevel ); // level 2
    growTree( head,maxLevel ); // level 3
    growTree( head,maxLevel ); // level 4
    growTree( head,maxLevel ); // level 5
    growTree( head,maxLevel ); // level 6
    growTree( head,maxLevel ); // level 7
    destroyTree( head );
    return;
  }
  else if(test==4){
    growTree( head,maxLevel ); // level 1
    growTree( head,maxLevel ); // level 2
    growTree( head,maxLevel ); // level 3
    growTree( head,maxLevel ); // level 4
    growTree( head,maxLevel ); // level 5
    growTree( head,maxLevel ); // level 6
    growTree( head,maxLevel ); // level 7
    growTree( head,maxLevel ); // level 8
    destroyTree( head );
    return;
  }
  else if(test==5){
    makeChildren( head );
    makeChildren( head->child[0] );
    makeChildren( head->child[1] );
    makeChildren( head->child[3] );
    makeChildren( head->child[0]->child[0] );
    makeChildren( head->child[0]->child[2] );
    makeChildren( head->child[3]->child[3] );
    growTree( head,maxLevel );
    writeTree( head );
    destroyTree( head );
  }
  else if(test==6){
    makeChildren( head );
    makeChildren( head->child[0] );
    makeChildren( head->child[1] );
    makeChildren( head->child[3] );
    makeChildren( head->child[0]->child[0] );
    makeChildren( head->child[0]->child[2] );
    makeChildren( head->child[3]->child[3] );
    growTree( head,maxLevel );
    writeTree( head );
    destroyTree( head );
  }
}

void taskFour(const int test, double tolerance, int choice){
  if(test==1){
    Node *head;
    head = makeNode( 0.0,0.0, 0 );
    growTree( head,-1 );
    growTree( head,-1 );
    taskFourAlgorithm( head,tolerance,choice );
    writeTree( head );
    destroyTree( head );
    return;
  }
  if(test==2){
    Node *head;
    head = makeNode( 0.0,0.0, 0 );
    growTree( head,-1 );
    growTree( head,-1 );
    taskFourAlgorithm( head,tolerance,choice );
    writeTree( head );
    destroyTree( head );
    return;
  }
}
