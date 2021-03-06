#include "machine.h"

void Bread(BrainVM* b) {
  printf("\nEnter a value\n");
  int a;
  int i;
  a = scanf(" %d", &i);
  changeValue(b, i);
}

void Bprint(BrainVM* b) {
  printf("%c", (char)getValue(b));
}

void LBrace(BrainVM* b) {
  int i;
  char val = getValue(b);
  int pc = getPC(b);
  if (val == '\0') {
    changePC(b, b->labels->tabLabelR[pc]);
  }
  nextPC(b);
}

void RBrace(BrainVM* b) {
  int i;
  char val = getValue(b);
  int pc = getPC(b);
  if (val != '\0') {
    changePC(b, b->labels->tabLabelL[pc]);
  }
  nextPC(b);
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

int executeCode(BrainVM* b) {
  char inst = getInst(b);
  int nb_instr = 1;
  while (inst != '\0') {
    if (b->verbose) {
      printf("\n");
      printf("Execution of the %c instruction.\nInstruction number : %d\n",
             inst, getPC(b));
    }
    executeInstruction(inst, b);
    if (b->vm_freq > 0) {
      sleep_ms(b->vm_freq);
    }
    if (b->verbose) {
      printf("Value Pointed: %d Case :%d\n",
             b->array->array[b->array->dataPointer], b->array->dataPointer);
    }
    if (b->step) {
      printf("Press ENTER Key to Continue\n");
      getchar();
    }
    inst = getInst(b);
    nb_instr++;
  }
  return nb_instr;
}