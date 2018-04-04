#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "machineStruct.h"

#ifndef _TOOLS_H_
#define _TOOLS_H_

/*Read the next non-empty char in file */
char ReadChar(FILE* f);

void printCode(Brain* b);
void printLabels(Brain* b);
void printData(Brain* b);
void printMem(Brain *b);

void sleep_ms(int milliseconds);

#endif