/*librairie principale pour interpreter du brainfuck*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#ifndef _MACHINESTRUCT_H_
#define _MACHINESTRUCT_H_

typedef struct machine {
  char* tab;
  char* code;
  int* tabLabelL;
  int* tabLabelR;
  int taille;
  int pointeur;
  int inst;
  int labelCount;
  int tailleCode;
  int tailleLabels;
} Brain;

Brain* initialiser();
int incr(Brain* b);
int decr(Brain* b);
int shift_right(Brain* b);
int shift_left(Brain* b);
int Bread(Brain* b);
int Bprint(Brain* b);
int LBrace(Brain* b);
int RBrace(Brain* b);

#endif