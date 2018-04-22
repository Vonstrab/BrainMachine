#include <stdio.h>
#include <stdlib.h>
#include "machineStruct.h"
#include "parser.h"
#include "tools.h"

#ifndef _MACHINE_H_
#define _MACHINE_H_

int executeCode(BrainVM* b, int verbose, int freq);
void executeInstruction(char c, BrainVM* b);

#endif