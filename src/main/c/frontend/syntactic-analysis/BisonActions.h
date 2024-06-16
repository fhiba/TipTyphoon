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
StylingBlock * UnionStylingBlockSemanticAction(StylingBlock * block, Styling * styling);
StylingBlock * StylingBlockSemanticAction(Styling * styling);
Block * HeaderBlockSemanticAction(Text * text, int number);
Block * BlockStylingBlockSemanticAction(StylingBlock * block);
Block * TextBlockSemanticAction(Text * text);
// Block * ListBlockSemanticAction(List * list);
Block * BlockquoteBlockSemanticAction(Text * text);
Styling * StylingSemanticAction(char * string, StylingType type);
// Styling * UnionStylingSemanticAction(Styling * first, Styling * second);
Text * TextSemanticAction(char * string);
Text * UnionTextSemanticAction(Text* left, char * string, Text * right);
Text * FormatTextSemanticAction(Text * text, TextType type);
List * ListSemanticAction(int tabCount, Text * text, ListType type);
Text * LinkSemanticAction(char * string, char * link);


Block * FirstTierNodeBlockSemanticAction(FirstTierNode * node);

Block * ListBlockSemanticAction(FirstTList * list);
FirstTList * FirstTOrderedListSemanticAction(FirstTNodeOrdered * node);
FirstTList * FirstTUnorderedListSemanticAction(FirstTNodeUnordered * node);
FirstTNodeOrdered * FirstTNodeOrderedSemanticAction(FirstTItemOrdered * item);
FirstTNodeOrdered * FirstTNodeOrderedAppendSemanticAction(FirstTNodeOrdered * node, FirstTItemOrdered * item);
FirstTNodeUnordered * FirstTNodeUnorderedSemanticAction(FirstTItemUnordered * item);
FirstTNodeUnordered * FirstTNodeUnorderedAppendSemanticAction(FirstTNodeUnordered * node, FirstTItemUnordered * item);
FirstTItemOrdered * FirstTItemOrderedSemanticAction(Text * text);
FirstTItemOrdered * SecondTListToOrderedSemanticAction(SecondTList * node);
FirstTItemUnordered * FirstTItemUnorderedSemanticAction(Text * text);
FirstTItemUnordered * SecondTListToUnorderedSemanticAction(SecondTList * node);
SecondTList * SecondTOrderedListSemanticAction(SecondTNodeOrdered * node);
SecondTList * SecondTUnorderedListSemanticAction(SecondTNodeUnordered * node);
SecondTNodeOrdered * SecondTNodeOrderedSemanticAction(SecondTItemOrdered * item);
SecondTNodeOrdered * SecondTNodeOrderedAppendSemanticAction(SecondTNodeOrdered * node, SecondTItemOrdered * item);
SecondTNodeUnordered * SecondTNodeUnorderedSemanticAction(SecondTItemUnordered * item);
SecondTNodeUnordered * SecondTNodeUnorderedAppendSemanticAction(SecondTNodeUnordered * node, SecondTItemUnordered * item);
SecondTItemOrdered * SecondTItemOrderedSemanticAction(Text * text);
SecondTItemOrdered * ThirdTListToOrderedSemanticAction(ThirdTList * node);
SecondTItemUnordered * SecondTItemUnorderedSemanticAction(Text * text);
SecondTItemUnordered * ThirdTListToUnorderedSemanticAction(ThirdTList * node);
ThirdTList * ThirdTOrderedListSemanticAction(ThirdTNodeOrdered * node);
ThirdTList * ThirdTUnorderedListSemanticAction(ThirdTNodeUnordered * node);
ThirdTNodeOrdered * ThirdTNodeOrderedSemanticAction(ThirdTItemOrdered * item);
ThirdTNodeOrdered * ThirdTNodeOrderedAppendSemanticAction(ThirdTNodeOrdered * node, ThirdTItemOrdered * item);
ThirdTNodeUnordered * ThirdTNodeUnorderedSemanticAction(ThirdTItemUnordered * item);
ThirdTNodeUnordered * ThirdTNodeUnorderedAppendSemanticAction(ThirdTNodeUnordered * node, ThirdTItemUnordered * item);
ThirdTItemOrdered * ThirdTItemOrderedSemanticAction(Text * text);
ThirdTItemUnordered * ThirdTItemUnorderedSemanticAction(Text * text);

#endif
