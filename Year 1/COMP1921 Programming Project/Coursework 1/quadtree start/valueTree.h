#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"

double dataFunction( double x, double y, int choice );

bool indicator( Node *node, double tolerance, int choice );

void addChildIfNotIndicator(Node *node, double tolerance, int choice, int *countFalse);

void taskFourAlgorithm(Node *node, double tolerance, int choice);
