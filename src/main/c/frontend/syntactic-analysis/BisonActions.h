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




Program * MasterBlockProgramSemanticAction(CompilerState * compilerState, MasterBlock * block);
MasterBlock * MasterBlockSemanticAction(Block * block);
MasterBlock * UnionMasterBlockSemanticAction(MasterBlock * first, Block * second);
Block * HeaderBlockSemanticAction(Inner * inner, int number);
Block * StylingBlockSemanticAction(Styling * block);
Block * TextBlockSemanticAction(Inner * inner);
Block * ListBlockSemanticAction(List * list);
Block * BlockquoteBlockSemanticAction(Inner * inner);
Styling * UnionStylingSemanticAction(Styling * first, Styling * second);
Styling * StylingSemanticAction(char * string, StylingType type);
Text * TextSemanticAction(char * string);
Text * UnionTextSemanticAction(Text* left, char * string, Text * right);
Inner * TextInnerSemanticAction(Text * text);
Text * FormatTextSemanticAction(Text * text, TextType type);
List * ListSemanticAction(int tabCount, Inner * inner, ListType type);
Text * LinkSemanticAction(char * string, char * link);

#endif
