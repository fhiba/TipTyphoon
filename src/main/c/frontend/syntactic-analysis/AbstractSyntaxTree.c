#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PUBLIC FUNCTIONS */



void releaseWord(Word * word) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (word != NULL) {
		free(word->word);
		free(word);
	}
}

void releaseBlock(Block * block) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (block != NULL) {
		switch (block->type) {
		case WORD:
			releaseWord(block->word);
			break;
		case WORD_BLOCK:
			releaseWord(block->word);
			releaseBlock(block->nextBlock);
			break;
		default:
			releaseBlock(block->childBlock);
		break;
		}
		free(block);
	}
}

void releaseProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseBlock(program->block);
		free(program);
	}
}
