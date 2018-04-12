#include "machine.h"

void Bread(BrainVM* b) {
  printf("\nEnter a value\n");
  int a;
  int i;
  a = scanf(" %d", &i);
  changeValue(b, i);
}

void Bprint(BrainVM* b) {
  printf("%c",(char) getValue(b));
}

void LBrace(BrainVM* b) {
  int i;
  int inst = getPC(b);
  inst++;
  char val = getValue(b);
  if (val == '\0') {
    for (i = 0; i < getSizeLabel(b); i++) {
      if (b->labels->tabLabelL[i] == inst) {
        changePC(b, b->labels->tabLabelR[i]);
      }
    }
  } else {
    nextPC(b);
  }
}

void RBrace(BrainVM* b) {
  int i;
  int inst = getPC(b);
  inst++;
  char val = getValue(b);
  if (val != '\0') {
    for (i = 0; i < getSizeLabel(b); i++) {
      if (b->labels->tabLabelR[i] == inst) {
        changePC(b, b->labels->tabLabelL[i]);
      }
    }
  } else {
    nextPC(b);
  }
}

void executeInstruction(char c, BrainVM* b) {
  switch (c) {
    case '>':
      PointerRight(b);
      nextPC(b);
      break;

    case '<':
      PointerLeft(b);
      nextPC(b);
      break;

    case '+':
      increment(b);
      nextPC(b);
      break;

    case '-':
      decrement(b);
      nextPC(b);
      break;

    case ',':
      Bread(b);
      nextPC(b);
      break;

    case '.':
      Bprint(b);
      nextPC(b);
      break;

    case '[':
      LBrace(b);
      break;

    case ']':
      RBrace(b);
      break;

    default:
      break;
  }
}

void executeCode(BrainVM* b, int verbose, int freq) {
  char inst = getInst(b);
  while (inst != '\0') {
    if (verbose) {
      printf("\n");
      printf("Execution of the %c instruction.\nInstruction number : %d\n",
             inst, getPC(b));
    }
    executeInstruction(inst, b);
    if (freq > 0) {
      sleep_ms(freq);
    }
    if (verbose) {
      printf("Value Pointed: %d Case :%d\n",
             b->array->array[b->array->dataPointer], b->array->dataPointer);
    }
    if (freq == -1) {
      printf("Press ENTER Key to Continue\n");
      getchar();
    }
    inst = getInst(b);
  }
}