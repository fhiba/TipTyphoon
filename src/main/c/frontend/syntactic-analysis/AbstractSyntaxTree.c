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

void releaseTInline(TInline * tInline){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(tInline != NULL){
		switch (tInline->type)
		{
		case T_UNION:
			releaseTInline(tInline->first);
			releaseTInline(tInline->second);
			break;
		case T_STRING:
			free(tInline->string);
			break;
		case CODE:
		case ITALIC:
		case BOLD:
			releaseTInline(tInline->child);
			break;
		}
		free(tInline);
	}
}


void releaseNTInline(NTInline * ntInline) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (ntInline != NULL) {
		switch (ntInline->type) {
		case NT_STRING:
			free(ntInline->string);
			break;
		case T_INLINE_FIRST:
		case NT_INLINE_FIRST:
			releaseNTInline(ntInline->nt_inline);
			releaseTInline(ntInline->t_inline);
			break;
		case NT_UNION:
			releaseNTInline(ntInline->first);
			releaseNTInline(ntInline->second);
			break;
		}
		free(ntInline);
	}
}


void releaseBlock(Block * block) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (block != NULL) {
		switch (block->type) {
		case WNL:
		case HEADER:
			releaseBlock(block->childBlock);
			break;
		case SIMPLE:
			if(block->t_inline == NULL)
				releaseNTInline(block->nt_inline);
			else
				releaseTInline(block->t_inline);
			break;
		case STYLING:
			releaseStyling(block->styling);
			break;
		}
		free(block);
	}
}

void releaseProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseMasterBlock(program->masterBlock);
		free(program);
	}
}

void releaseMasterBlock(MasterBlock * masterBlock) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (masterBlock != NULL) {
		if(masterBlock->type == MASTER_BLOCK_LIST){
			releaseBlock(masterBlock->block);
			releaseMasterBlock(masterBlock->nextBlock);
		} else {
			releaseBlock(masterBlock->onlyBlock);
		}
		free(masterBlock);
	}
}
void releaseStyling(Styling * styling) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (styling != NULL) {
		switch (styling->type) {
		case P:
		case FF:
		case FS:
		case FC:
		case BC:
		case UC:
		case U:
			free(styling->string);
			break;
		case S_UNION:
			releaseStyling(styling->first);
			releaseStyling(styling->second);
			break;
		}
		free(styling);
	}
}