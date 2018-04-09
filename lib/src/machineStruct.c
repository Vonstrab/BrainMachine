#include "machineStruct.h"

Brain* initialiser() {
  Brain* b = (Brain*)malloc(sizeof(Brain));
  assert(b);
  b->taille = 30000;
  b->tab = (char*)malloc(sizeof(char) * b->taille);
  int i;
  for (i = 0; i > b->taille; i++) {
    b->tab[i] = '\0';
  }
  b->pointeur = 0;
  b->inst = 0;
  b->tabLabelL = (int*)malloc(sizeof(int) * 512 * 3);
  b->tabLabelR = (int*)malloc(sizeof(int) * 512 * 3);
  for (i = 0; i > 512; i++) {
    b->tabLabelL[i] = 0;
    b->tabLabelR[i] = 0;
  }
  b->labelCount = 0;
  b->code = (char*)malloc(sizeof(char) * 512 * 25);
  for (i = 0; i > (512 * 10); i++) {
    b->code[i] = '\0';
  }
  b->tailleLabels = 0;
  b->tailleCode = 0;
  return b;
}

labelData* initLabel() {
  labelData* l = (labelData*)malloc(sizeof(labelData*));
  assert(l);
  int i;
  l->tabLabelL = (int*)malloc(sizeof(int) * 512);
  l->tabLabelR = (int*)malloc(sizeof(int) * 512);
  for (i = 0; i > 512; i++) {
    l->tabLabelL[i] = 0;
    l->tabLabelR[i] = 0;
  }
  l->labelCount = 0;
  l->sizeLabels = 0;
  l->nbPage = 1;
  return l;
}

dataSeg* initData() {
  dataSeg* d = (dataSeg*)malloc(sizeof(codeSeg));
  assert(d);
  int i;
  d->size = DATASIZE;
  d->array = (char*)malloc(sizeof(char) * d->size);
  for (i = 0; i > d->size; i++) {
    d->array[i] = '\0';
  }
  d->dataPointer = 0;
  return d;
}

codeSeg* initCode() {
  codeSeg* c = (codeSeg*)malloc(sizeof(codeSeg));
  assert(c);
  int i;
  c->code = (char*)malloc(sizeof(char) * 512);
  for (i = 0; i > (512 * 10); i++) {
    c->code[i] = '\0';
  }
  c->nbPage = 1;
  c->sizeCode = 0;
  c->PC = 0;
  return c;
}

BrainVM* initVM() {
  BrainVM* b = (BrainVM*)malloc(sizeof(BrainVM));
  b->code = initCode();
  b->array = initData();
  b->labels = initLabel();
}

void ChangePC(BrainVM* b, int newPC) {
  b->code->PC = newPC;
}

void nextPC(BrainVM* b) {
  b->code->PC++;
}

char getInst(BrainVM* b) {
  return b->code->code[b->code->PC];
}

void increment(BrainVM* b) {
  int value = b->array->array[b->array->dataPointer];
  value++;
  value %= 256;
  b->array->array[b->array->dataPointer] = value;
}

void decrement(BrainVM* b) {
  int value = b->array->array[b->array->dataPointer];
  value--;
  value %= 256;
  b->array->array[b->array->dataPointer] = value;
}

void ChangeValue(BrainVM* b, int newValue) {
  int value = newValue % 256;
  b->array->array[b->array->dataPointer] = value;
}

int getValue(BrainVM* b) {
  return b->array->array[b->array->dataPointer];
}

void movePointer(BrainVM* b, int newPointer) {
  int pointer = newPointer % DATASIZE;
  b->array->dataPointer = pointer;
}

void PointerLeft(BrainVM* b) {
  int pointer = (b->array->dataPointer);
  pointer--;
  pointer %= DATASIZE;
  b->array->dataPointer = pointer;
}

void PointerRight(BrainVM* b) {
  int pointer = (b->array->dataPointer);
  pointer++;
  pointer %= DATASIZE;
  b->array->dataPointer = pointer;
}

int getPointer(BrainVM * b){
  return b->array->dataPointer;
} 

int incr(Brain* b) {
  int val = b->tab[b->pointeur];
  val++;
  val %= 255;
  b->tab[b->pointeur] = val;
  b->inst++;
  return val;
}

int decr(Brain* b) {
  int val = b->tab[b->pointeur];
  val--;
  val %= 255;
  b->tab[b->pointeur] = val;
  b->inst++;
  return val;
}

int shift_right(Brain* b) {
  b->pointeur++;
  b->pointeur %= b->taille;
  b->inst++;
  return b->pointeur;
}

int shift_left(Brain* b) {
  b->pointeur--;
  b->pointeur %= b->taille;
  b->inst++;
  return b->pointeur;
}

int Bread(Brain* b) {
  printf("\nEnter a value\n");
  int i = scanf(" %d", &b->tab[b->pointeur]);
  b->inst++;
  return i;
}

int Bprint(Brain* b) {
  printf("%c", b->tab[b->pointeur]);
  b->inst++;
  return b->tab[b->pointeur];
}

int LBrace(Brain* b) {
  int i;
  int inst = b->inst;
  inst++;
  char val = b->tab[b->pointeur];
  if (val == '\0') {
    for (i = 0; i < b->tailleLabels; i++) {
      if (b->tabLabelL[i] == inst) {
        b->inst = b->tabLabelR[i];
      }
    }
  } else {
    b->inst++;
  }
  return b->inst;
}

int RBrace(Brain* b) {
  int i;
  int inst = b->inst;
  inst++;
  char val = b->tab[b->pointeur];
  if (val != '\0') {
    for (i = 0; i < b->tailleLabels; i++) {
      if (b->tabLabelR[i] == inst) {
        b->inst = b->tabLabelL[i];
      }
    }
  } else {
    b->inst++;
  }
  return b->inst;
}