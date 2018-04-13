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
  int* stackBRACE;
  int sptr = 0;

  stackBRACE = (int*)calloc(1000, sizeof(int));

  while ((c = ReadChar(f_in)) != EOF) {
    if (isValid(c)) {
      b->code->code[calc] = c;
      calc++;
    }

    if (c == '[') {
      stackBRACE[sptr] = calc;
      sptr++;
    }

    if (c == ']') {
      if (sptr == 0) {
        printf("\nERROR : Right Brace Unmatched\n");
        ERROR = 1;
      }

      k = stackBRACE[sptr - 1];
      sptr--;

      b->labels->tabLabelL[calc - 1] = k - 1;
      b->labels->tabLabelR[k - 1] = calc - 1;
      label++;
    }
  }

  fclose(f_in);
  b->code->code[calc] = '\0';
  b->labels->tabLabelL[label] = '\0';
  b->labels->tabLabelR[label] = '\0';
  b->code->sizeCode = calc;
  b->labels->sizeLabels = label;

  if (sptr != 0) {
    printf("\nERROR : Left Brace Unmatched '[' \n");
    ERROR = 1;
  }

  free (stackBRACE);

  if (ERROR == 1) {
    printf("\nError found , now quiting \n");
    exit(0);
  }
}
