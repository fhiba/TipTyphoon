#ifndef LINKCHECKER_H
#define LINKCHECKER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"


bool checkProgram(MasterBlock * masterBlock);


#define BLOCK_SIZE 100

#endif