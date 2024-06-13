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
	newBlock->type = TEXT;
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


Block * ListBlockSemanticAction(List * list) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->list = list;
	newBlock->type = LIST;
	return newBlock;
}

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
	return out;
}

StylingBlock * StylingBlockSemanticAction(Styling * styling){
	StylingBlock * out = calloc(1, sizeof(StylingBlock));
	out->styling = styling;
	return out;
}