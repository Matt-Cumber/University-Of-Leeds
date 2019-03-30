#include "stdio.h"
#include "stdlib.h"
#include "math.h"

Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void growTree( Node *node, const int maxLevel);
