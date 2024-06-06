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




void releaseBlock(Block * block) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (block != NULL) {
		switch (block->type) {
		case H1:
		case H2:
		case H3:
		case H4:
		case H5:
		case H6:
		case BQ:
		case SIMPLE:
			releaseText(block->text);
			break;
		case STYLING:
			releaseStylingBlock(block->styling);
			break;
		case LIST:
			releaseList(block->list);
			break;
		default:
			break;
		}
		free(block);
	}
}

// void releaseInner(Inner * inner) {
// 	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
// 	if (inner != NULL) {
// 		releaseText(inner->text);
// 		free(inner);
// 	}
// }

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
			releaseMasterBlock(masterBlock->first);
			releaseBlock(masterBlock->second);
		} else {
			releaseBlock(masterBlock->block);
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
			releaseStr(styling->string);
			break;
		default:
			break;
		}
		free(styling);
	}
}
void releaseText(Text * text) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (text != NULL) {
		switch (text->type) {
		case TEXT:
			releaseStr(text->string);
			break;
		case UNION:
			releaseText(text->left);
			releaseStr(text->ws);
			releaseText(text->right);
			break;
		case BOLD:
		case ITALIC:
		case CODE:
			releaseText(text->child);
			break;
		case LINK:
			releaseLink(text->link);
			break;
		default:
			break;
		}
		free(text);
	}
}
void releaseStr(char * string) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (string != NULL) {
		free(string);
	}
}

void releaseList(List * list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (list != NULL) {
		releaseText(list->content);
		free(list);
	}
}

void releaseLink(Link * link) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (link != NULL) {
		releaseStr(link->string);
		releaseStr(link->link);
		free(link);
	}
}

void releaseStylingBlock(StylingBlock * stylingBlock){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (stylingBlock != NULL) {
		if(stylingBlock->block != NULL){
			releaseStylingBlock(stylingBlock->block);
		}
		releaseStyling(stylingBlock->styling);
		free(stylingBlock);
	}
}