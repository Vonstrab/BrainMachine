#include <stdio.h>
#include <stdlib.h>
#include "machineStruct.h"
#include "parser.h"
#include "tools.h"

#ifndef _MACHINE_H_
#define _MACHINE_H_

    char readInstruction(Brain* b);
void executeCode(Brain* b, int verbose, int freq);
void executeInstruction(char c, Brain* b, int option);

#endif