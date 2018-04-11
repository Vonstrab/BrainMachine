#include "parser.h"

int isValid(char c) {
  int ret = (c == '+' || c == '-' || c == '<' || c == '>' || c == '.' ||
             c == ',' || c == '[' || c == ']');
  return ret;
}

void parse(const char* in, BrainVM* b) {
  FILE* f_in = fopen(in, "r");
  int calc = 0;
  int label = 0;
  int ERROR = 0;
  char c;
  int i;
  int k = 0;

  while ((c = ReadChar(f_in)) != EOF) {
    if (isValid(c)) {
      b->code->code[calc] = c;
      calc++;
    }

    if (c == '[') {
      b->labels->tabLabelL[label] = calc;
      label++;
    }

    if (c == ']') {
      for (i = label - 1; i >= 0; i--) {
        if (b->labels->tabLabelR[i] == 0) {
          b->labels->tabLabelR[i] = calc;
          k = 1;
          break;
        }
      }

      if (k == 0) {
        printf("\nERROR : Right Brace Unmatched\n");
        ERROR = 1;
      }
      k = 0;
    }
  }
  fclose(f_in);
  b->code->code[calc] = '\0';
  b->labels->tabLabelL[label] = '\0';
  b->labels->tabLabelR[label] = '\0';
  b->code->sizeCode = calc;
  b->labels->sizeLabels = label;

  for (i = 0; i < label; i++) {
    if (b->labels->tabLabelR[i] == '\0') {
      printf("\nERROR : Left Brace Unmatched '[' \n");
      ERROR = 1;
    }
    if (b->labels->tabLabelL[i] == '\0') {
      printf("\nERROR Right Brace Unmatched ']' \n");
      ERROR = 1;
    }
  }

  if (ERROR == 1) {
    printf("\nError found , now quiting \n");
    exit(0);
  }
}
