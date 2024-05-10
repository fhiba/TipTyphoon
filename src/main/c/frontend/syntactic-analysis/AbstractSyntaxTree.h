#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */

typedef enum BlockType BlockType;

typedef struct Word Word;
typedef struct Block Block;
typedef struct Program Program;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */
enum BlockType {
	HEADING1,
	HEADING2,
	HEADING3,
	HEADING4,
	HEADING5,
	HEADING6,
	WORD,
	WORD_BLOCK
};

struct Word {
	char * word;
};


struct Block {
	union {
		Word * word2;
		struct {
			Word * word;
			Block * nextBlock;
		};
		Block * childBlock;
	};
	BlockType type;
};


struct Program {
	Block * block;
};

/**
 * Node recursive destructors.
 */
void releaseWord(Word * word);
void releaseBlock(Block * block);
void releaseProgram(Program * program);

#endif
