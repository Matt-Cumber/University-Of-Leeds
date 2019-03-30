#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "treeStructure.h"
#include "tests.h"
#include "buildTree.h"
#include "writeTree.h"
#include "destroyTree.h"
#include "valueTree.h"

void runGNUPLOT() {
  FILE *gnuplot;
  gnuplot = popen("gnuplot -persist", "w");
  if (gnuplot == NULL){
    printf("error opening gnuplot to produce tree");
    exit(0);
  }
  fprintf(gnuplot,"load 'quad.gnu'\n");
  fprintf(gnuplot,"q\n");
  fclose(gnuplot);
  return;
}

void runGNUPLOTPNG() {
  FILE *gnuplot;
  gnuplot = popen("gnuplot -persist", "w");
  if (gnuplot == NULL){
    printf("error opening gnuplot to produce tree");
    exit(0);
  }
  fprintf(gnuplot,"set term png\n");
  fprintf(gnuplot,"set output 'quad.png'\n");
  fprintf(gnuplot,"load 'quad.gnu'\n");
  fprintf(gnuplot,"q\n");
  fclose(gnuplot);
  return;
}

int main( int argc, char **argv ) {
  int task,testnumber,gnupng=0,autodisplay=0;
  while(true){
    printf("--------Select Task--------\n1. Task 1\n2. Task 2\n3. Task 3\n4. Task 4\n5. Exit\n>>>>");
    scanf(" %d", &task);

    // task 1
    if(task==1){
      while(true){
        printf("--------Select test--------\n1. Full level 2 tree\n2. Non-uniform level 3 tree\n3. Cancel\n>>>>");
        scanf(" %d", &testnumber);
        if(testnumber==1){
          taskOne(1);
          return 0;
        }
        else if(testnumber==2) {
          taskOne(2);
          return 0;
        }
        else if(testnumber==3) break;
        else{
          printf("Error choosing test\n");
        }
      }
    }

    //task 2
    else if(task==2){
      while(true){
        printf("--------Select test--------\n1. Grow full level 2 tree\n2. Grow non-uniform level 3 tree\n3. Change gnuplot output to .png\n4. Set to auto display\n5. Cancel\n>>>>");
        scanf(" %d", &testnumber);
        if(testnumber==1){
          tasktwo(1);
          if(autodisplay==0){
            if(gnupng==0) return 0;
              else{
                runGNUPLOTPNG();
                return 0;
              }
            }
            else{
              if(gnupng==0) runGNUPLOT();
              else{
                runGNUPLOTPNG();
                system("display quad.png");
              }
              return 0;
          }
        }
        else if(testnumber==2){
          tasktwo(2);
          if(autodisplay==0){
            if(gnupng==0) return 0;
              else{
                runGNUPLOTPNG();
                return 0;
              }
            }
            else{
              if(gnupng==0) runGNUPLOT();
              else{
                runGNUPLOTPNG();
                system("display quad.png");
              }
              return 0;
          }
        }
        else if(testnumber==3) gnupng=1;
        else if(testnumber==4) autodisplay=1;
        else if(testnumber==5) break;
        else{
          printf("Error choosing test\n");
        }
      }
    }

    //task 3
    else if(task==3){
      while(true){
        printf("--------Select test--------\n1. Full level 5 tree\n2. Full level 6 tree\n3. Full level 7 tree\n4. Full level 8 tree\n5. Non-uniform level 3 tree max level 3\n6. Non-uniform level 3 tree max level 4\n7. Set to auto display\n8. Cancel\n>>>>");
        scanf(" %d", &testnumber);
        if(testnumber==1){
          if(autodisplay==1){
            taskThree(1,-1);
            runGNUPLOT();
            return 0;
          }
          taskThree(1,-1);
          return 0;
        }
        else if(testnumber==2){
          if(autodisplay==1){
            taskThree(2,-1);
            runGNUPLOT();
            return 0;
          }
          taskThree(2,-1);
          return 0;
        }
        else if(testnumber==3){
          if(autodisplay==1){
            taskThree(3,-1);
            runGNUPLOT();
            return 0;
          }
          taskThree(3,-1);
          return 0;
        }
        else if(testnumber==4){
          if(autodisplay==1){
            taskThree(4,-1);
            runGNUPLOT();
            return 0;
          }
          taskThree(4,-1);
          return 0;
        }
        else if(testnumber==5){
          if(autodisplay==1){
            taskThree(5,3);
            runGNUPLOT();
            return 0;
          }
          taskThree(5,3);
          return 0;
        }
        else if(testnumber==6){
          if(autodisplay==1){
            taskThree(6,4);
            runGNUPLOT();
            return 0;
          }
          taskThree(6,4);
          return 0;
        }
        else if(testnumber==7) autodisplay=1;
        else if(testnumber==8) break;
        else{
          printf("Error choosing test\n");
        }
      }
    }
    else if(task==4){
      while(true){
        printf("--------Select test--------\n1. choice=0, tolerance=0.5\n2. choice=1, tolerance=0.2\n3. Set auto display\n4. Cancel\n>>>>");
        scanf(" %d", &testnumber);
        if(testnumber==1){
          if(autodisplay==1){
            taskFour(1,0.5,0);
            runGNUPLOT();
            return 0;
          }
          taskFour(1,0.5,0);
          return 0;
        }
        else if(testnumber==2){
          if(autodisplay==1){
            taskFour(1,0.2,1);
            runGNUPLOT();
            return 0;
          }
          taskFour(1,0.2,1);
          return 0;
        }
        else if(testnumber==3) autodisplay=1;
        else if(testnumber==4) break;
        else{
          printf("Error choosing test\n");
        }
      }
    }
    else if(task==5) break;
    else{
      printf("Error choosing task\n");
    }
  }
  return 0;
}
