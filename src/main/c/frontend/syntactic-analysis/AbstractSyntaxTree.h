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
typedef enum StylingBlockType StylingBlockType;
typedef enum SublistType SublistType;
typedef enum ListType ListType;
typedef enum ListDepth ListDepth;
typedef enum TextType TextType;



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
typedef struct StylingBlock StylingBlock;


/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum ListDepth {
	DEPTH_1,
	DEPTH_2,
	DEPTH_3
};

enum StylingBlockType {
	STYLING_BLOCK,
	STYLING_BLOCK_LIST
};

enum StylingType {
	FF,
	FS,
	FC,
	BC,
	UC,
	U,
	P
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

struct StylingBlock {
	union{
		struct{
			StylingBlock * block;
			Styling * styling;
		};
		Styling * style;
	};
	StylingBlockType type;
};

struct List{
	Text * content;
	ListType type;
	ListDepth depth;
};


struct Styling {
	char * string;
	StylingType type;
};

struct Block {
	union {
		Text * text;
		StylingBlock * styling;
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
void releaseStylingBlock(StylingBlock * stylingBlock);
void releaseStyling(Styling * styling);
void releaseText(Text * text);
void releaseStr(char * str);
void releaseList(List * list);
void releaseLink(Link * link);
#endif