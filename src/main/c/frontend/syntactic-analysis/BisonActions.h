#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

Block * WordBlockSemanticAction(Word * word, Block * nextBlock);
Block * HeadingBlockSemanticAction(Block * block, BlockType type);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Block * block);
Word * StringSemanticAction(char * word);

#endif
