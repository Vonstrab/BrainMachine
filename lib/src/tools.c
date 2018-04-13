#include "tools.h"

/*Read the next non-empty char in file */
char ReadChar(FILE* f) {
  char c;
  do
    c = getc(f);
  while (isspace(c));
  return c;
}

void printCode(BrainVM* b) {
  int i = 0;
  int j = 0;
  for (i = 0; i < b->code->sizeCode; i++) {
    printf("%c", b->code->code[i]);
    if (j == 70) {
      printf("\n");
      j = 0;
    }
    j++;
  }
  printf("\n");
}

void printData(BrainVM* b) {
  printf("Number of instructions : %d\n", b->code->sizeCode+1);
  printf("Number of nested braces : %d\n", b->labels->sizeLabels);
}

void printMem(BrainVM* b) {
  printf("\nMemoire : :\n");
  printf("| ");

  int i = 0;
  int j = 0;
  for (i = 0; b->array->array[i] != 0; i++) {
    printf("%d | ", b->array->array[i]);
    if (j == 70) {
      printf("\n");
      j = 0;
    }
    j++;
  }
  printf("\n");
}

void sleep_ms(int milliseconds) {
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000;
  ts.tv_nsec = (milliseconds % 1000) * 1000000;
  nanosleep(&ts, NULL);
}