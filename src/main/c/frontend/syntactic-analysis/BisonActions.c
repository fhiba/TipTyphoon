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

MasterBlock * MasterBlockSemanticAction(Block * block, MasterBlock * masterBlock, MasterBlockType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	MasterBlock * newMasterBlock = calloc(1, sizeof(MasterBlock));
	if(type == MASTER_BLOCK_LIST) {
		newMasterBlock->block = block;
		newMasterBlock->nextBlock = masterBlock;
		newMasterBlock->type = MASTER_BLOCK_LIST;
	} else {
		newMasterBlock->onlyBlock = block;
		newMasterBlock->type = MASTER_BLOCK;
	}

	return newMasterBlock;
}

Block * HeaderBlockSemanticAction(Block * block) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->childBlock = block;
	newBlock->type = HEADER;
	return newBlock;
}

Block * TSimpleBlockSemanticAction(TInline * tInline){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->t_inline = tInline;
	newBlock->type = SIMPLE;
	return newBlock;
}

Block * NTSimpleBlockSemanticAction(NTInline * ntInline){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->nt_inline = ntInline;
	newBlock->type = SIMPLE;
	return newBlock;
}


Block * WNLBlockSemanticAction(Block * block) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->childBlock = block;
	newBlock->type = WNL;
	return newBlock;
}

Block * StylingBlockSemanticAction(Styling * styling) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	newBlock->styling = styling;
	newBlock->type = STYLING;
	return newBlock;
}

TInline * TStringSemanticAction(char * string){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TInline * out = calloc(1,sizeof(TInline));
	out->type = T_STRING;
	out->string = string;
	return out;
}

TInline * TInlineSemanticAction(TInline * tInline, TInlineType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TInline * out = calloc(1,sizeof(TInline));
	out->type = type;
	out->child = tInline;
	return out;
}

TInline * UnionSemanticAction(TInline * first, NTInline * middle, TInline * last){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TInline * out = calloc(1,sizeof(TInline));
	out->type = T_UNION;
	out->first = first;
	out->divider = middle;
	out->second = last;
	return out;
}

NTInline * NTStringSemanticAction(char * string) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	NTInline * out = calloc(1, sizeof(NTInline));
	out->type = NT_STRING;
	out->string = string;
	return out;

}

NTInline * appendUnionSemanticAction(NTInline * first, NTInline * second) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	NTInline * out = calloc(1, sizeof(NTInline));
	out->type = NT_UNION;
	out->first = first;
	out->second = second;
	return out;
}

NTInline * appendTSemanticAction(TInline * first, NTInline * second) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	NTInline * out = calloc(1, sizeof(NTInline));
	out->type = T_INLINE_FIRST;
	out->t_inline = first;
	out->nt_inline = second;
	return out;
}

NTInline * appendNTSemanticAction(NTInline * first, TInline * second) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	NTInline * out = calloc(1, sizeof(NTInline));
	out->type = NT_INLINE_FIRST;
	out->t_inline = second;
	out->nt_inline = first;
	return out;
}


Styling * UnionStylingSemanticAction(Styling * first, Styling * second) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Styling * out = calloc(1, sizeof(Styling));
	out->type = S_UNION;
	out->first = first;
	out->second = second;
	return out;
}


Styling * StylingSemanticAction(char * string, StylingType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Styling * out = calloc(1, sizeof(Styling));
	out->type = type;
	out->string = string;
	return out;
}