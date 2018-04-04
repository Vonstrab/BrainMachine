#include "tools.h"

/*Read the next non-empty char in file */
char ReadChar(FILE* f) {
  char c;
  do
    c = getc(f);
  while (isspace(c));
  return c;
}



void printCode(Brain* b) {
  int i = 0;
  int j = 0;
  for (i = 0; i < b->tailleCode; i++) {
    printf("%c", b->code[i]);
    if (j == 70) {
      printf("\n");
      j = 0;
    }
    j++;
  }
  printf("\n");
}

void printLabels(Brain* b) {
  printf("Le tableau des labels :\n");
  int i;
  for (i = 0; i < b->tailleLabels; i++) {
    printf("Label %d : %d %d \n", i, b->tabLabelL[i], b->tabLabelR[i]);
  }
  printf("\n");
}

void printData(Brain* b) {
  printf("Number of instructions : %d\n", b->tailleCode);
  printf("Number of nested braces : %d\n", b->tailleLabels);
}

void printMem(Brain* b) {
  printf("\nMemoire : :\n");
    printf("| ");
  
  int i = 0;
  int j = 0;
  for (i = 0; b->tab[i]!=0; i++) {
    printf("%d | ", b->tab[i]);
    if (j == 70) {
      printf("\n");
      j = 0;
    }
    j++;
  }
  printf("\n");
}

void sleep_ms(int milliseconds) 
{
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}