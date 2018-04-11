#include <stdio.h>
#include <stdlib.h>
#include "machineStruct.h"
#include "tools.h"


#ifndef _PARSER_H_
#define _PARSER_H_

int isValid(char c);
void parse(const char* in, BrainVM* b);


#endif