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
typedef enum StylingType StylingType;
typedef enum SublistType SublistType;
typedef enum ListType ListType;
typedef enum TextType TextType;


typedef struct Inner Inner;
typedef struct Text Text;
typedef struct Link Link;
typedef struct Sublist Sublist;
typedef struct List List;
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

enum ListType{
	UL,
	OL
};


enum BlockType {
	H1,
	H2,
	H3,
	H4,
	H5,
	H6,
	BQ,
	LIST,
	SIMPLE,
	STYLING
};

enum TextType {
	TEXT,
	UNION,
	BOLD,
	ITALIC,
	CODE,
	LINK
};

struct List{
	Inner * content;
	int tabCount;
	ListType type;
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

struct Inner {
	Text * text;
};

struct Block {
	union {
		Inner * inner;
		Styling * styling;
		List * list;
	};
	BlockType type;
};

struct MasterBlock {
	union {
		Block * block;
		struct {
			MasterBlock * first;
			Block * second;
		};
	};
	MasterBlockType type;
};

struct Program {
	MasterBlock * masterBlock;
};
struct Text {
	union{
		char * string;
		struct {
			Text * left;
			char * ws;
			Text * right;
		};
		Text * child;
		Link * link;
	};
	TextType type;
};

struct Link {
	char * string;
	char * link;
};

/**
 * Node recursive destructors.
 */
void releaseBlock(Block * block);
void releaseProgram(Program * program);
void releaseMasterBlock(MasterBlock * masterBlock);
void releaseStyling(Styling * styling);
void releaseText(Text * text);
void releaseInner(Inner * inner);
void releaseStr(char * str);
void releaseList(List * list);
void releaseLink(Link * link);
#endif