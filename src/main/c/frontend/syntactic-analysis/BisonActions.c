#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */
Program * MasterBlockProgramSemanticAction(CompilerState * compilerState, MasterBlock * block)
{
    _logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->masterBlock = block;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}

MasterBlock * MasterBlockSemanticAction(Block * block) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	MasterBlock * newMasterBlock = calloc(1, sizeof(MasterBlock));
	newMasterBlock->block = block;
	newMasterBlock->type = MASTER_BLOCK;
	return newMasterBlock;
}
MasterBlock * UnionMasterBlockSemanticAction(MasterBlock * first, Block * second) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	MasterBlock * newMasterBlock = calloc(1, sizeof(MasterBlock));
	newMasterBlock->type = MASTER_BLOCK_LIST;
	newMasterBlock->first = first;
	newMasterBlock->second = second;
	return newMasterBlock;
}

Block * HeaderBlockSemanticAction(Text * text, int number) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->text = text;
	switch (number)
	{
	case 1:
		newBlock->type = H1;
		break;
	case 2:
		newBlock->type = H2;
		break;
	case 3:
		newBlock->type = H3;
		break;
	case 4:
		newBlock->type = H4;
		break;
	case 5:
		newBlock->type = H5;
		break;
	default:
		newBlock->type = H6;
		break;
	}
	return newBlock;
}

Block * TextBlockSemanticAction(Text * text){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->text = text;
	newBlock->type = SIMPLE;
	return newBlock;
}


Block * BlockStylingBlockSemanticAction(StylingBlock * styling) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->styling = styling;
	newBlock->type = STYLING;
	return newBlock;
}


// Styling * UnionStylingSemanticAction(Styling * first, Styling * second) {
// 	_logSyntacticAnalyzerAction(__FUNCTION__);
// 	Styling * out = calloc(1, sizeof(Styling));
// 	out->type = S_UNION;
// 	out->first = first;
// 	out->second = second;
// 	return out;
// }


Styling * StylingSemanticAction(char * string, StylingType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Styling * out = calloc(1, sizeof(Styling));
	out->type = type;
	out->string = string;
	return out;
}



Text * TextSemanticAction(char * string){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Text * text = calloc(1, sizeof(Text));
	text->string = string;
	text->type = TEXT;
	return text;
}

Text * UnionTextSemanticAction(Text * left, char * ws, Text * right) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Text * out = calloc(1, sizeof(Text));
	out->type = UNION;
	out->left = left;
	out->ws = ws;
	out->right = right;
	return out;
}



Text * FormatTextSemanticAction(Text * text, TextType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Text * newText = calloc(1, sizeof(Text));
	newText->type = type;
	newText->child = text;
	return newText;
}

List * ListSemanticAction(int tabCount, Text * text, ListType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List * list = calloc(1, sizeof(List));
	list->content = text;
	list->tabCount = tabCount;
	list->type = type;
	return list;
}


// Block * ListBlockSemanticAction(List * list) {
// 	_logSyntacticAnalyzerAction(__FUNCTION__);
// 	Block * newBlock = calloc(1, sizeof(Block));
// 	newBlock->list = list;
// 	newBlock->type = LIST;
// 	return newBlock;
// }

Text * LinkSemanticAction(char * string, char * link){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Text * text = calloc(1, sizeof(Text));
	Link * newLink = calloc(1, sizeof(Link));
	newLink->string = string;
	newLink->link = link;
	text->type = LINK;
	text->link = newLink;	
	return text;
}

Block * BlockquoteBlockSemanticAction(Text * text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->text = text;
	newBlock->type = BQ;
	return newBlock;
}

StylingBlock * UnionStylingBlockSemanticAction(StylingBlock * block, Styling * styling){
	StylingBlock * out = calloc(1, sizeof(StylingBlock));
	out->block = block;
	out->styling = styling;
	out->type = STYLING_BLOCK_LIST;
	return out;
}

StylingBlock * StylingBlockSemanticAction(Styling * styling){
	StylingBlock * out = calloc(1, sizeof(StylingBlock));
	out->styling = styling;
	out->type = STYLING_BLOCK;
	return out;
}


Block * FirstTierNodeBlockSemanticAction(FirstTierNode * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->list = node;
	newBlock->type = LIST;
	return newBlock;
}
Block * ListBlockSemanticAction(FirstTList * list) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->list = list;
	newBlock->type = LIST;
	return newBlock;

}

FirstTList * FirstTOrderedListSemanticAction(FirstTNodeOrdered * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTList * list = calloc(1, sizeof(FirstTList));
	list->type = OL;
	list->ordered = node;
	return list;
}
FirstTList * FirstTUnorderedListSemanticAction(FirstTNodeUnordered * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTList * list = calloc(1, sizeof(FirstTList));
	list->type = UL;
	list->unordered = node;
	return list;
}
FirstTNodeOrdered * FirstTNodeOrderedSemanticAction(FirstTItemOrdered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTNodeOrdered * node = calloc(1, sizeof(FirstTNodeOrdered));
	node->type = LEAF;
	node->item = item;
	return node;
}
FirstTNodeOrdered * FirstTNodeOrderedAppendSemanticAction(FirstTNodeOrdered * node, FirstTItemOrdered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTNodeOrdered * newNode = calloc(1, sizeof(FirstTNodeOrdered));
	newNode->type = NODE;
	newNode->node = node;
	newNode->appended = item;
	return newNode;
}
FirstTNodeUnordered * FirstTNodeUnorderedSemanticAction(FirstTItemUnordered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTNodeUnordered * node = calloc(1, sizeof(FirstTNodeUnordered));
	node->type = LEAF;
	node->item = item;
	return node;
}
FirstTNodeUnordered * FirstTNodeUnorderedAppendSemanticAction(FirstTNodeUnordered * node, FirstTItemUnordered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTNodeUnordered * newNode = calloc(1, sizeof(FirstTNodeUnordered));
	newNode->type = NODE;
	newNode->node = node;
	newNode->appended = item;
	return newNode;
}
FirstTItemOrdered * FirstTItemOrderedSemanticAction(Text * text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTItemOrdered * item = calloc(1, sizeof(FirstTItemOrdered));
	item->text = text;
	item->type = ITEM;
	return item;
}
FirstTItemOrdered * SecondTListToOrderedSemanticAction(SecondTList * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTItemOrdered * item = calloc(1, sizeof(FirstTItemOrdered));
	item->type = LIST_ITEM;
	item->list = node;
	return item;
}
FirstTItemUnordered * FirstTItemUnorderedSemanticAction(Text * text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTItemUnordered * item = calloc(1, sizeof(FirstTItemUnordered));
	item->text = text;
	item->type = ITEM;
	return item;
}
FirstTItemUnordered * SecondTListToUnorderedSemanticAction(SecondTList * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FirstTItemUnordered * item = calloc(1, sizeof(FirstTItemUnordered));
	item->type = LIST_ITEM;
	item->list = node;
	return item;
}
SecondTList * SecondTOrderedListSemanticAction(SecondTNodeOrdered * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTList * list = calloc(1, sizeof(SecondTList));
	list->type = OL;
	list->ordered = node;
	return list;
}
SecondTList * SecondTUnorderedListSemanticAction(SecondTNodeUnordered * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTList * list = calloc(1, sizeof(SecondTList));
	list->type = UL;
	list->unordered = node;
	return list;
}
SecondTNodeOrdered * SecondTNodeOrderedSemanticAction(SecondTItemOrdered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTNodeOrdered * node = calloc(1, sizeof(SecondTNodeOrdered));
	node->type = LEAF;
	node->item = item;
	return node;
}
SecondTNodeOrdered * SecondTNodeOrderedAppendSemanticAction(SecondTNodeOrdered * node, SecondTItemOrdered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTNodeOrdered * newNode = calloc(1, sizeof(SecondTNodeOrdered));
	newNode->type = NODE;
	newNode->node = node;
	newNode->appended = item;
	return newNode;
}
SecondTNodeUnordered * SecondTNodeUnorderedSemanticAction(SecondTItemUnordered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTNodeUnordered * node = calloc(1, sizeof(SecondTNodeUnordered));
	node->type = LEAF;
	node->item = item;
	return node;
}
SecondTNodeUnordered * SecondTNodeUnorderedAppendSemanticAction(SecondTNodeUnordered * node, SecondTItemUnordered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTNodeUnordered * newNode = calloc(1, sizeof(SecondTNodeUnordered));
	newNode->type = NODE;
	newNode->node = node;
	newNode->appended = item;
	return newNode;
}
SecondTItemOrdered * SecondTItemOrderedSemanticAction(Text * text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTItemOrdered * item = calloc(1, sizeof(SecondTItemOrdered));
	item->text = text;
	item->type = ITEM;
	return item;
}
SecondTItemOrdered * ThirdTListToOrderedSemanticAction(ThirdTList * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTItemOrdered * item = calloc(1, sizeof(SecondTItemOrdered));
	item->type = LIST_ITEM;
	item->list = node;
	return item;
}
SecondTItemUnordered * SecondTItemUnorderedSemanticAction(Text * text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTItemUnordered * item = calloc(1, sizeof(SecondTItemUnordered));
	item->text = text;
	item->type = ITEM;
	return item;
}
SecondTItemUnordered * ThirdTListToUnorderedSemanticAction(ThirdTList * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SecondTItemUnordered * item = calloc(1, sizeof(SecondTItemUnordered));
	item->type = LIST_ITEM;
	item->list = node;
	return item;
}
ThirdTList * ThirdTOrderedListSemanticAction(ThirdTNodeOrdered * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTList * list = calloc(1, sizeof(ThirdTList));
	list->type = OL;
	list->ordered = node;
	return list;
}
ThirdTList * ThirdTUnorderedListSemanticAction(ThirdTNodeUnordered * node) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTList * list = calloc(1, sizeof(ThirdTList));
	list->type = UL;
	list->unordered = node;
	return list;
}
ThirdTNodeOrdered * ThirdTNodeOrderedSemanticAction(ThirdTItemOrdered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTNodeOrdered * node = calloc(1, sizeof(ThirdTNodeOrdered));
	node->type = LEAF;
	node->item = item;
	return node;
}
ThirdTNodeOrdered * ThirdTNodeOrderedAppendSemanticAction(ThirdTNodeOrdered * node, ThirdTItemOrdered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTNodeOrdered * newNode = calloc(1, sizeof(ThirdTNodeOrdered));
	newNode->type = NODE;
	newNode->node = node;
	newNode->appended = item;
	return newNode;
}
ThirdTNodeUnordered * ThirdTNodeUnorderedSemanticAction(ThirdTItemUnordered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTNodeUnordered * node = calloc(1, sizeof(ThirdTNodeUnordered));
	node->type = LEAF;
	node->item = item;
	return node;
}
ThirdTNodeUnordered * ThirdTNodeUnorderedAppendSemanticAction(ThirdTNodeUnordered * node, ThirdTItemUnordered * item) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTNodeUnordered * newNode = calloc(1, sizeof(ThirdTNodeUnordered));
	newNode->type = NODE;
	newNode->node = node;
	newNode->appended = item;
	return newNode;
}
ThirdTItemOrdered * ThirdTItemOrderedSemanticAction(Text * text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTItemOrdered * item = calloc(1, sizeof(ThirdTItemOrdered));
	item->text = text;
	return item;
}
ThirdTItemUnordered * ThirdTItemUnorderedSemanticAction(Text * text) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ThirdTItemUnordered * item = calloc(1, sizeof(ThirdTItemUnordered));
	item->text = text;
	return item;
}

