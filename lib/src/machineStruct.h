/*librairie principale pour interpreter du brainfuck*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef _MACHINESTRUCT_H_
#define _MACHINESTRUCT_H_

#define DATASIZE 30000;

typedef struct {
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

typedef struct {
  char* code;
  int PC;
  int sizeCode;
  int nbPage;
} codeSeg;

typedef struct {
  char* array;
  int dataPointer;
  int size;
} dataSeg;

typedef struct {
  int sizeLabels;
  int labelCount;
  int* tabLabelL;
  int* tabLabelR;
  int nbPage;
} labelData;

typedef struct {
  codeSeg* code;
  dataSeg* array;
  labelData* labels;
} BrainVM;

labelData* initLabel();
dataSeg* initData();
codeSeg* initCode();
BrainVM* initVM();

void changePC(BrainVM* b, int newPC);
void nextPC(BrainVM* b);
int getPC(BrainVM* b);
char getInst(BrainVM* b);
void increment(BrainVM* b);
void decrement(BrainVM* b);
void changeValue(BrainVM* b, int newValue);
int getValue(BrainVM* b);
void movePointer(BrainVM* b, int newPointer);
void PointerLeft(BrainVM* b);
void PointerRight(BrainVM* b);
int getPointer(BrainVM* b);
int getSizeLabel(BrainVM* b);

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