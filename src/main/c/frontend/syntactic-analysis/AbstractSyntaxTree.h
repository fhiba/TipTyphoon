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
typedef enum MasterBlockType MasterBlockType;
typedef enum NTInlineType NTInlineType;
typedef enum TInlineType TInlineType;
typedef enum StylingType StylingType;
typedef struct Styling Styling;

typedef struct Word Word;
typedef struct Block Block;
typedef struct MasterBlock MasterBlock;
typedef struct Program Program;
typedef struct NTInline NTInline;
typedef struct TInline TInline;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */


enum StylingType {
	FF,
	FS,
	FC,
	BC,
	UC,
	U,
	P,
	S_UNION
};

enum MasterBlockType {
	MASTER_BLOCK,
	MASTER_BLOCK_LIST
};


enum BlockType {
	HEADER,
	SIMPLE,
	WNL,
	STYLING
};


enum NTInlineType {
	NT_STRING,
	NT_INLINE_FIRST,
	T_INLINE_FIRST,
	NT_UNION
};

enum TInlineType {
	T_STRING,
	ITALIC,
	CODE,
	BOLD,
	T_UNION
};

struct NTInline{
	union{
		char* string;
		struct{
			NTInline * nt_inline;
			TInline * t_inline;
		};
		struct{	
			NTInline * first;
			NTInline * second;
		};
	};
	NTInlineType type;
};



struct TInline{
	union{
		char* string;
		struct{
			TInline * first;
			NTInline * divider;
			TInline * second;
		};
		TInline * child;
	};
	TInlineType type;
};


struct Styling {
	union {
		char * string;
		struct {
			Styling * first;
			Styling * second;
		};
	};
	StylingType type;
};

struct Block {
	union {
		NTInline * nt_inline;
		TInline * t_inline;
		Block * childBlock;
		Styling * styling;
	};
	BlockType type;
};

struct MasterBlock {
	union {
		Block * onlyBlock;
		struct {
			Block * block;
			MasterBlock * nextBlock;
		};
	};
	MasterBlockType type;
};

struct Program {
	MasterBlock * masterBlock;
};

/**
 * Node recursive destructors.
 */
void releaseTInline(TInline * tInline);
void releaseNTInline(NTInline * ntInline);
void releaseBlock(Block * block);
void releaseProgram(Program * program);
void releaseMasterBlock(MasterBlock * masterBlock);
void releaseStyling(Styling * styling);
#endif
