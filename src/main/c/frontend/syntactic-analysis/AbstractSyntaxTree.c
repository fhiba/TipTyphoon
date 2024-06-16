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

void releaseFirstTierNode(FirstTierNode * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseFirstTierNode(node->node);
			releaseFirstTierItem(node->appended);
		} else {
			releaseFirstTierItem(node->item);
		}
		free(node);
	}
}
void releaseFirstTierItem(FirstTierItem * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(item != NULL) {
		if(item->type == NODE_ITEM) {
			releaseSecondTierNode(item->node);
		} else {
			releaseText(item->text);
		}
		free(item);
	}
}
void releaseSecondTierNode(SecondTierNode * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseSecondTierNode(node->node);
			releaseSecondTierItem(node->appended);
		} else {
			releaseSecondTierItem(node->item);
		}
		free(node);
	}
}
void releaseSecondTierItem(SecondTierItem * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(item != NULL) {
		if(item->type == NODE_ITEM) {
			releaseThirdTierNode(item->node);
		} else {
			releaseText(item->text);
		}
		free(item);
	}
}
void releaseThirdTierNode(ThirdTierNode * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseThirdTierNode(node->node);
			releaseThirdTierItem(node->appended);
		} else {
			releaseThirdTierItem(node->item);
		}
		free(node);
	}
}
void releaseThirdTierItem(ThirdTierItem * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(item != NULL) {
		releaseText(item->text);
		free(item);
	}
}

void releaseFirstTList(FirstTList * list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(list != NULL) {
		if(list->type == OL) {
			releaseFirstTNodeOrdered(list->ordered);
		} else {
			releaseFirstTNodeUnordered(list->unordered);
		}
		free(list);
	}
}
void releaseSecondTList(SecondTList * list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(list != NULL) {
		if(list->type == OL) {
			releaseSecondTNodeOrdered(list->ordered);
		} else {
			releaseSecondTNodeUnordered(list->unordered);
		}
		free(list);
	}
}
void releaseThirdTList(ThirdTList * list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(list != NULL) {
		if(list->type == OL) {
			releaseThirdTNodeOrdered(list->ordered);
		} else {
			releaseThirdTNodeUnordered(list->unordered);
		}
		free(list);
	}
}
void releaseFirstTNodeOrdered(FirstTNodeOrdered * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseFirstTNodeOrdered(node->node);
			releaseFirstTItemOrdered(node->appended);
		} else {
			releaseFirstTItemOrdered(node->item);
		}
		free(node);
	}
}
void releaseFirstTNodeUnordered(FirstTNodeUnordered * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseFirstTNodeUnordered(node->node);
			releaseFirstTItemUnordered(node->appended);
		} else {
			releaseFirstTItemUnordered(node->item);
		}
		free(node);
	}
}
void releaseSecondTNodeOrdered(SecondTNodeOrdered * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseSecondTNodeOrdered(node->node);
			releaseSecondTItemOrdered(node->appended);
		} else {
			releaseSecondTItemOrdered(node->item);
		}
		free(node);
	}

}
void releaseSecondTNodeUnordered(SecondTNodeUnordered * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseSecondTNodeUnordered(node->node);
			releaseSecondTItemUnordered(node->appended);
		} else {
			releaseSecondTItemUnordered(node->item);
		}
		free(node);
	}
}
void releaseThirdTNodeOrdered(ThirdTNodeOrdered * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseThirdTNodeOrdered(node->node);
			releaseThirdTItemOrdered(node->appended);
		} else {
			releaseThirdTItemOrdered(node->item);
		}
		free(node);
	}
}
void releaseThirdTNodeUnordered(ThirdTNodeUnordered * node) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(node != NULL) {
		if(node->type == NODE) {
			releaseThirdTNodeUnordered(node->node);
			releaseThirdTItemUnordered(node->appended);
		} else {
			releaseThirdTItemUnordered(node->item);
		}
		free(node);
	}

}
void releaseFirstTItemOrdered(FirstTItemOrdered * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(item != NULL) {
		if(item->type == NODE_ITEM) {
			releaseSecondTList(item->list);
		} else {
			releaseText(item->text);
		}
				free(item);
	}

}
void releaseFirstTItemUnordered(FirstTItemUnordered * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(item != NULL) {
		if(item->type == NODE_ITEM) {
			releaseSecondTList(item->list);
		} else {
			releaseText(item->text);
		}
		free(item);
	}
}
void releaseSecondTItemOrdered(SecondTItemOrdered * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(item != NULL) {
		if(item->type == NODE_ITEM) {
			releaseThirdTList(item->list);
		} else {
			releaseText(item->text);
		}
		free(item);
	}

}
void releaseSecondTItemUnordered(SecondTItemUnordered * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if(item != NULL) {
		if(item->type == NODE_ITEM) {
			releaseThirdTList(item->list);
		} else {
			releaseText(item->text);
		}
		free(item);
	}

}
void releaseThirdTItemOrdered(ThirdTItemOrdered * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	releaseText(item->text);
	free(item);
}
void releaseThirdTItemUnordered(ThirdTItemUnordered * item) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	releaseText(item->text);
	free(item);
}