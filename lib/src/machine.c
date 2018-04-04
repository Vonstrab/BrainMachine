#include "machine.h"

char readInstruction(Brain* b) {
  return b->code[b->inst];
}

void executeInstruction(char c, Brain* b, int verbose) {
  int ret;

  switch (c) {
    case '>':
      ret = shift_right(b);

      break;
    case '<':
      ret = shift_left(b);
      break;
    case '+':
      ret = incr(b);
      break;
    case '-':
      ret = decr(b);
      break;
    case ',':
      ret = Bread(b);
      break;
    case '.':
      ret = Bprint(b);
      break;
    case '[':
      ret = LBrace(b);
      break;
    case ']':
      ret = RBrace(b);
      break;
    default:
      break;
  }
}

void executeCode(Brain* b, int verbose, int freq) {
  char inst = readInstruction(b);
  while (inst != '\0') {
    if (verbose) {
      printf("\n");
      printf("Execution of the %c instruction.\nInstruction number : %d\n", inst, b->inst);
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