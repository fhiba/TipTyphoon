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

Block *WordBlockSemanticAction(Word *word, Block *nextBlock) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	if(nextBlock != NULL) {
		newBlock->type = WORD_BLOCK;
		newBlock->word = word;
		newBlock->nextBlock = nextBlock;
	}
	else {
		newBlock->type = WORD;
		newBlock->word = word;
	}
    return newBlock;
}

Block *HeadingBlockSemanticAction(Block *block, BlockType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * newBlock = calloc(1, sizeof(Block));
	block->type = type;
	block->childBlock = block;
	return newBlock;
}

Program *ExpressionProgramSemanticAction(CompilerState *compilerState, Block *block)
{
    _logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->block = block;
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

Word *StringSemanticAction(char *word)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Word * newWord = calloc(1, sizeof(Word));
	newWord->word = word;

    return newWord;
}
