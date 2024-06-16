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
typedef enum TextType TextType;
typedef enum NodeType NodeType;
typedef enum ItemType ItemType;

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
typedef struct FirstTierNode FirstTierNode;
typedef struct FirstTierItem FirstTierItem;
typedef struct SecondTierNode SecondTierNode;
typedef struct SecondTierItem SecondTierItem;
typedef struct ThirdTierNode ThirdTierNode;
typedef struct ThirdTierItem ThirdTierItem;
typedef struct FirstTList FirstTList;
typedef struct SecondTList SecondTList;
typedef struct ThirdTList ThirdTList;
typedef struct FirstTNodeOrdered FirstTNodeOrdered;
typedef struct FirstTNodeUnordered FirstTNodeUnordered;
typedef struct SecondTNodeOrdered SecondTNodeOrdered;
typedef struct SecondTNodeUnordered SecondTNodeUnordered;
typedef struct ThirdTNodeOrdered ThirdTNodeOrdered;
typedef struct ThirdTNodeUnordered ThirdTNodeUnordered;
typedef struct FirstTItemOrdered FirstTItemOrdered;
typedef struct FirstTItemUnordered FirstTItemUnordered;
typedef struct SecondTItemOrdered SecondTItemOrdered;
typedef struct SecondTItemUnordered SecondTItemUnordered;
typedef struct ThirdTItemOrdered ThirdTItemOrdered;
typedef struct ThirdTItemUnordered ThirdTItemUnordered;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum NodeType {
	NODE,
	LEAF
};

enum ItemType {
	ITEM,
	LIST_ITEM
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
	int tabCount;
	ListType type;
};


struct Styling {
	char * string;
	StylingType type;
};

struct Block {
	union {
		Text * text;
		StylingBlock * styling;
		FirstTList * list;
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



struct FirstTierNode {
	union {
		FirstTierItem * item;
		struct {
			FirstTierNode * node;
			FirstTierItem * appended;
		};
	};
	NodeType type;
};

struct FirstTierItem {
	ItemType type;
	union {
		SecondTierNode * node;
		Text * text;
	};
};

struct SecondTierNode {
	union {
		SecondTierItem * item;
		struct {
			SecondTierNode * node;
			SecondTierItem * appended;
		};
	};
	NodeType type;
};

struct SecondTierItem {
	ItemType type;
	union {
		ThirdTierNode * node;
		Text * text;
	};
};

struct ThirdTierNode {
	union {
		ThirdTierItem * item;
		struct {
			ThirdTierNode * node;
			ThirdTierItem * appended;
		};
	};
	NodeType type;
};

struct ThirdTierItem {
	Text * text;
	ListType type;
};

struct ThirdTItemOrdered {
		Text * text;
};

struct ThirdTItemUnordered {
		Text * text;
};

struct ThirdTNodeUnordered {
	union {
		ThirdTItemUnordered * item;
		struct {
			ThirdTNodeUnordered * node;
			ThirdTItemUnordered * appended;
		};
	};
	NodeType type;
};

struct ThirdTNodeOrdered {
	union {
		ThirdTItemOrdered * item;
		struct {
			ThirdTNodeOrdered * node;
			ThirdTItemOrdered * appended;
		};
	};
	NodeType type;
};

struct SecondTItemUnordered {
	union {
		ThirdTList * list;
		Text * text;
	};
	ItemType type;
};



struct SecondTItemOrdered {
	union {
		ThirdTList * list;
		Text * text;
	};
	ItemType type;
};

struct SecondTNodeUnordered {
	union {
		SecondTItemUnordered * item;
		struct {
			SecondTNodeUnordered * node;
			SecondTItemUnordered * appended;
		};
	};
	NodeType type;
};

struct SecondTNodeOrdered {
	union {
		SecondTItemOrdered * item;
		struct {
			SecondTNodeOrdered * node;
			SecondTItemOrdered * appended;
		};
	};
	NodeType type;
};

struct FirstTItemUnordered {
	union {
		SecondTList * list;
		Text * text;
	};
	ItemType type;
};



struct FirstTItemOrdered {
	union {
		SecondTList * list;
		Text * text;
	};
	ItemType type;
};

struct FirstTNodeUnordered {
	union {
		FirstTItemUnordered * item;
		struct {
			FirstTNodeUnordered * node;
			FirstTItemUnordered * appended;
		};
	};
	NodeType type;
};

struct FirstTNodeOrdered {
	union {
		FirstTItemOrdered * item;
		struct {
			FirstTNodeOrdered * node;
			FirstTItemOrdered * appended;
		};
	};
	NodeType type;
};

struct ThirdTList {
	union {
		ThirdTNodeOrdered * ordered;
		ThirdTNodeUnordered * unordered;
	};
	ListType type;
};

struct SecondTList {
	union {
		SecondTNodeOrdered * ordered;
		SecondTNodeUnordered * unordered;
	};
	ListType type;
};

struct FirstTList {
	union {
		FirstTNodeOrdered * ordered;
		FirstTNodeUnordered * unordered;
	};
	ListType type;
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
void releaseFirstTierNode(FirstTierNode * node);
void releaseFirstTierItem(FirstTierItem * item);
void releaseSecondTierNode(SecondTierNode * node);
void releaseSecondTierItem(SecondTierItem * item);
void releaseThirdTierNode(ThirdTierNode * node);
void releaseThirdTierItem(ThirdTierItem * item);
void releaseFirstTList(FirstTList * list);
void releaseSecondTList(SecondTList * list);
void releaseThirdTList(ThirdTList * list);
void releaseFirstTNodeOrdered(FirstTNodeOrdered * node);
void releaseFirstTNodeUnordered(FirstTNodeUnordered * node);
void releaseSecondTNodeOrdered(SecondTNodeOrdered * node);
void releaseSecondTNodeUnordered(SecondTNodeUnordered * node);
void releaseThirdTNodeOrdered(ThirdTNodeOrdered * node);
void releaseThirdTNodeUnordered(ThirdTNodeUnordered * node);
void releaseFirstTItemOrdered(FirstTItemOrdered * item);
void releaseFirstTItemUnordered(FirstTItemUnordered * item);
void releaseSecondTItemOrdered(SecondTItemOrdered * item);
void releaseSecondTItemUnordered(SecondTItemUnordered * item);
void releaseThirdTItemOrdered(ThirdTItemOrdered * item);
void releaseThirdTItemUnordered(ThirdTItemUnordered * item);

#endif