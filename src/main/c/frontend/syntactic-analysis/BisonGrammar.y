%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */
	int integer;
	char* string;
	Token token;

	/** Non-terminals. */

	Text * text;
	Block * block;
	Program * program;
	MasterBlock * master_block;
	Styling * styling;
	List * list;
	Sublist * sublist;
	StylingBlock * stylingBlock;

}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */
%token <string> STRING;
%token <token> H1_TOKEN
%token <token> H2_TOKEN
%token <token> H3_TOKEN
%token <token> H4_TOKEN
%token <token> H5_TOKEN
%token <token> H6_TOKEN
%token <token> B_TOKEN
%token <token> I_TOKEN
%token <token> C_TOKEN
%token <string> STYLING_VALUE
%token <token> BEGIN_STYLING
%token <token> END_STYLING_VALUE
%token <token> END_STYLING
%token <token> U_TOKEN
%token <token> FF_TOKEN
%token <token> FS_TOKEN
%token <token> FC_TOKEN
%token <token> BC_TOKEN
%token <token> UC_TOKEN
%token <token> P_TOKEN
%token <string> WS
%token <integer> UNORDERED_LIST
%token <integer> ORDERED_LIST
%token <string> START_LINK
%token <token> END_LINK
%token <token> BLOCKQUOTE_TOKEN

%token <token> THIRD_TIER_ITEM
%token <token> SECOND_TIER_ITEM
%token <token> FIRST_TIER_ITEM
%token <token> THIRD_TIER_ITEM_ORDERED
%token <token> SECOND_TIER_ITEM_ORDERED
%token <token> FIRST_TIER_ITEM_ORDERED


%token <token> UNKNOWN

/** Non-terminals. */
%type <text> text
%type <block> block
%type <program> program
%type <master_block> master_block
%type <styling> styling
%type <list> list
%type <stylingBlock> stylingBlock

%left WS
%%

program: master_block                  {$$ = MasterBlockProgramSemanticAction(currentCompilerState(), $1);}
	;


master_block: block						{$$ = MasterBlockSemanticAction($1);}
            | master_block block	    {$$ = UnionMasterBlockSemanticAction($1, $2);}
	;


stylingBlock: styling					{$$ = StylingBlockSemanticAction($1);}
			| stylingBlock styling		{$$ = UnionStylingBlockSemanticAction($1, $2);}
	;

styling: FS_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, FS);}
	| FF_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, FF);}
	| FC_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, FC);}
	| BC_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, BC);}
	| UC_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, UC);}
	| U_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, U);}
	| P_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, P);}
	;
	
block:  H1_TOKEN text							{$$ = HeaderBlockSemanticAction($2,H1);}
	| H2_TOKEN text    						{$$ = HeaderBlockSemanticAction($2,H2);}
	| H3_TOKEN text							{$$ = HeaderBlockSemanticAction($2,H3);}
	| H4_TOKEN text	    					{$$ = HeaderBlockSemanticAction($2,H4);}
	| H5_TOKEN text 							{$$ = HeaderBlockSemanticAction($2,H5);}
	| H6_TOKEN text 							{$$ = HeaderBlockSemanticAction($2,H6);}
	| BEGIN_STYLING stylingBlock END_STYLING	{$$ = BlockStylingBlockSemanticAction($2);}
	| BLOCKQUOTE_TOKEN text					{$$ = BlockquoteBlockSemanticAction($2);}
	| text                                     {$$ = TextBlockSemanticAction($1);}
	| list                                      {$$ = ListBlockSemanticAction($1);}
	;


list: FIRST_TIER_ITEM text							{$$ = ListSemanticAction( $2, UL, DEPTH_1);}
	| SECOND_TIER_ITEM text							{$$ = ListSemanticAction( $2, UL, DEPTH_2);}
	| THIRD_TIER_ITEM text							{$$ = ListSemanticAction( $2, UL, DEPTH_3);}
	| FIRST_TIER_ITEM_ORDERED text					{$$ = ListSemanticAction( $2, OL, DEPTH_1);}
	| SECOND_TIER_ITEM_ORDERED text					{$$ = ListSemanticAction( $2, OL, DEPTH_2);}
	| THIRD_TIER_ITEM_ORDERED text					{$$ = ListSemanticAction( $2, OL, DEPTH_3);}
	;

text: text WS text                              {$$ = UnionTextSemanticAction($1, $2, $3);}
	| STRING 									{$$ = TextSemanticAction($1);}
	| START_LINK STRING END_LINK                {$$ = LinkSemanticAction($1,$2);}
	| B_TOKEN text B_TOKEN						{$$ = FormatTextSemanticAction($2, BOLD);}
	| I_TOKEN text I_TOKEN						{$$ = FormatTextSemanticAction($2, ITALIC);}
	| C_TOKEN text C_TOKEN						{$$ = FormatTextSemanticAction($2, CODE);}
	;

%%
