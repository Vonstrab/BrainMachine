#include "machineStruct.h"

labelData* initLabel() {
  labelData* l = (labelData*)malloc(sizeof(labelData*));
  assert(l);
  int i;
  l->tabLabelL = (int*)calloc(30005, sizeof(int));
  l->tabLabelR = (int*)calloc(30005, sizeof(int));
  l->sizeLabels = 0;
  return l;
}

dataSeg* initData() {
  dataSeg* d = (dataSeg*)malloc(sizeof(codeSeg));
  assert(d);
  int i;
  d->size = DATASIZE;
  d->array = (char*)calloc(d->size, sizeof(char));
  d->dataPointer = 0;
  return d;
}

codeSeg* initCode() {
  codeSeg* c = (codeSeg*)malloc(sizeof(codeSeg));
  assert(c);
  int i;
  c->code = (char*)calloc(30000, sizeof(char));
  c->sizeCode = 0;
  c->PC = 0;
  return c;
}

BrainVM* initVM() {
  BrainVM* b = (BrainVM*)malloc(sizeof(BrainVM));
  b->code = initCode();
  b->array = initData();
  b->labels = initLabel();
  return b;
}

void changePC(BrainVM* b, int newPC) {
  b->code->PC = newPC;
}

void nextPC(BrainVM* b) {
  b->code->PC++;
}

int getPC(BrainVM* b) {
  return b->code->PC;
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

void changeValue(BrainVM* b, int newValue) {
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

int getPointer(BrainVM* b) {
  return b->array->dataPointer;
}

int getSizeLabel(BrainVM* b) {
  return b->labels->sizeLabels;
}