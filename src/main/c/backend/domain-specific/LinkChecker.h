#ifndef LINKCHECKER_H
#define LINKCHECKER_H

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Type.h"

void initializeCheckerModule();
void shutdownCheckerModule();
boolean checkProgram(MasterBlock * masterBlock);


#define BLOCK_SIZE 100

#endif