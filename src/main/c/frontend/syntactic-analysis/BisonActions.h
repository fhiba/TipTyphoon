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
MasterBlock * MasterBlockSemanticAction(Block * block, MasterBlock * nextBlock, MasterBlockType type);
TInline * TStringSemanticAction(char * string);
TInline * TInlineSemanticAction(TInline * tInline, TInlineType type);
TInline * UnionSemanticAction(TInline * first, NTInline * middle, TInline * last);
NTInline * NTStringSemanticAction(char * string);
NTInline * appendUnionSemanticAction(NTInline * first, NTInline * second);
NTInline * appendTSemanticAction(TInline * first, NTInline * second);
NTInline * appendNTSemanticAction(NTInline * first, TInline * second);
Block * HeaderBlockSemanticAction(Block * block);
Block * TSimpleBlockSemanticAction(TInline * tInline);
Block * NTSimpleBlockSemanticAction(NTInline * ntInline);
Block * WNLBlockSemanticAction(Block * block);
Block * StylingBlockSemanticAction(Styling * block);
Styling * UnionStylingSemanticAction(Styling * first, Styling * second);
Styling * StylingSemanticAction(char * string, StylingType type);
#endif
