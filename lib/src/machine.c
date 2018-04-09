#include "machine.h"

void Bread(BrainVM* b) {
  printf("\nEnter a value\n");
  int i;
  scanf(" %d", &i);
  ChangeValue(b, i);
}

void Bprint(BrainVM* b) {
  printf("%c", getValue(b));
}

int LBrace(Brainvm* b) {
  int i;
  int inst = getPC(b);
  inst++;
  char val = getValue(b);
  if (val == '\0') {
    for (i = 0; i < getSizeLabel(b); i++) {
      if (b->labelData->tabLabelL[i] == inst) {
        changePC(b, b->labelData->tabLabelR[i]);
      }
    }
  } else {
    nextPC(b);
  }
  return b->inst;
}

int RBrace(Brain* b) {
  int i;
  int inst = getPC(b);
  inst++;
  char val = getValue(b);
  if (val == '\0') {
    for (i = 0; i < getSizeLabel(b); i++) {
      if (b->labelData->tabLabelR[i] == inst) {
        changePC(b, b->labelData->tabLabelL[i]);
      }
    }
  } else {
    nextPC(b);
  }
  return b->inst;
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
             inst, getPointer(b));
    }
    executeInstruction(inst, b, verbose);
    if (freq > 0) {
      sleep_ms(freq);
    }
    if (verbose) {
      printf("Value Pointed: %d Case :%d\n", b->tab[b->pointeur], b->pointeur);
    }
    if (freq == -1) {
      printf("Press ENTER Key to Continue\n");
      getchar();
    }
    inst = readInstruction(b);
  }
}