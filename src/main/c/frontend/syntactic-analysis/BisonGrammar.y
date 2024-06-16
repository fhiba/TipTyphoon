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
	FirstTierItem * first_tier_item;
	FirstTierNode * first_tier_node;
	SecondTierItem * second_tier_item;
	SecondTierNode * second_tier_node;
	ThirdTierItem * third_tier_item;
	ThirdTierNode * third_tier_node;
	FirstTList * first_tier_list;
	SecondTList * second_tier_list;
	ThirdTList * third_tier_list;
	FirstTNodeOrdered * first_tier_node_ordered;
	FirstTNodeUnordered * first_tier_node_unordered;
	SecondTNodeOrdered * second_tier_node_ordered;
	SecondTNodeUnordered * second_tier_node_unordered;
	ThirdTNodeOrdered * third_tier_node_ordered;
	ThirdTNodeUnordered * third_tier_node_unordered;
	FirstTItemOrdered * first_tier_item_ordered;
	FirstTItemUnordered * first_tier_item_unordered;
	SecondTItemOrdered * second_tier_item_ordered;
	SecondTItemUnordered * second_tier_item_unordered;
	ThirdTItemOrdered * third_tier_item_ordered;
	ThirdTItemUnordered * third_tier_item_unordered;
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
%type <first_tier_list> first_tier_list
%type <second_tier_list> second_tier_list
%type <third_tier_list> third_tier_list
%type <first_tier_item_ordered> first_tier_item_ordered
%type <first_tier_item_unordered> first_tier_item_unordered
%type <first_tier_node_ordered> first_tier_node_ordered
%type <first_tier_node_unordered> first_tier_node_unordered
%type <second_tier_item_ordered> second_tier_item_ordered
%type <second_tier_item_unordered> second_tier_item_unordered
%type <second_tier_node_ordered> second_tier_node_ordered
%type <second_tier_node_unordered> second_tier_node_unordered
%type <third_tier_item_ordered> third_tier_item_ordered
%type <third_tier_item_unordered> third_tier_item_unordered
%type <third_tier_node_ordered> third_tier_node_ordered
%type <third_tier_node_unordered> third_tier_node_unordered

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
	
block:  H1_TOKEN text							{$$ = HeaderBlockSemanticAction($2,1);}
	| H2_TOKEN text    						{$$ = HeaderBlockSemanticAction($2,2);}
	| H3_TOKEN text							{$$ = HeaderBlockSemanticAction($2,3);}
	| H4_TOKEN text	    					{$$ = HeaderBlockSemanticAction($2,4);}
	| H5_TOKEN text 							{$$ = HeaderBlockSemanticAction($2,5);}
	| H6_TOKEN text 							{$$ = HeaderBlockSemanticAction($2,6);}
	| BEGIN_STYLING stylingBlock END_STYLING	{$$ = BlockStylingBlockSemanticAction($2);}
	| BLOCKQUOTE_TOKEN text					{$$ = BlockquoteBlockSemanticAction($2);}
	| text                                     {$$ = TextBlockSemanticAction($1);}
	| first_tier_list						{$$ = ListBlockSemanticAction($1);}
	;

first_tier_list: first_tier_node_ordered { $$ = FirstTierNodeOrderedListSemanticAction($1);}
	| first_tier_node_unordered 	{$$ = FirstTierNodeUnorderedListSemanticAction($1);}
	;

first_tier_node_ordered: first_tier_item_ordered { $$ =ThirdTierNodeSemanticAction($1);};
			| first_tier_node_ordered first_tier_item_ordered { $$ = UnionThirdTierNodeSemanticAction($1, $2);}
			;

first_tier_node_unordered: first_tier_item_unordered { $$ =ThirdTierNodeSemanticAction($1);};
			| first_tier_node_unordered first_tier_item_unordered { $$ = UnionThirdTierNodeSemanticAction($1, $2);}
			;


first_tier_item_ordered: second_tier_list { $$ = SecondTierNodeToFirstTierItemSemanticAction($1);}
	| FIRST_TIER_ITEM_ORDERED text				{$$ = FirstTierItemSemanticAction($2, OL);}
	;
first_tier_item_unordered: second_tier_list { $$ = SecondTierNodeToFirstTierItemSemanticAction($1);}
	| FIRST_TIER_ITEM text				{$$ = FirstTierItemSemanticAction($2, UL);}
	;

second_tier_list : second_tier_node_ordered { $$ = SecondTierNodeOrderedListSemanticAction($1);}
	| second_tier_node_unordered 	{$$ = SecondTierNodeUnorderedListSemanticAction($1);}
	;



second_tier_node_ordered: second_tier_item_ordered { $$ =SecondTierNodeSemanticAction($1);};
			| second_tier_node_ordered second_tier_item_ordered { $$ = SecondTierNodeAppendSemanticAction($1, $2);}
			;
second_tier_node_unordered: second_tier_item_unordered { $$ =SecondTierNodeSemanticAction($1);};
			| second_tier_node_unordered second_tier_item_unordered { $$ = SecondTierNodeAppendSemanticAction($1, $2);}
			;

second_tier_item_ordered: third_tier_list   { $$ = ThirdTierNodeToSecondTierItemSemanticAction($1);}
	| SECOND_TIER_ITEM_ORDERED text				{$$ = SecondTierItemSemanticAction($2, OL);}
	;
second_tier_item_unordered: third_tier_list   { $$ = ThirdTierNodeToSecondTierItemSemanticAction($1);}
	| SECOND_TIER_ITEM text			{$$ = SecondTierItemSemanticAction($2, UL);}
	;

third_tier_list: third_tier_node_ordered { $$ = ThirdTierNodeListSemanticAction($1);}
	| third_tier_node_unordered 	{$$ = ThirdTierNodeListSemanticAction($1);}
	;

third_tier_node_ordered: third_tier_item_ordered { $$ =ThirdTierNodeSemanticAction($1);};
			| third_tier_node_ordered third_tier_item_ordered { $$ = ThirdTierNodeAppendSemanticAction($1, $2);}
			;
third_tier_node_unordered: third_tier_item_unordered { $$ =ThirdTierNodeSemanticAction($1);};
			| third_tier_node_ordered third_tier_item_unordered { $$ = ThirdTierNodeAppendSemanticAction($1, $2);}
			;
third_tier_item_ordered: THIRD_TIER_ITEM_ORDERED text				{$$ = ThirdTierItemSemanticAction($2, OL);}
	;

third_tier_item_unordered: THIRD_TIER_ITEM text			{$$ = ThirdTierItemSemanticAction($2, UL);}
	;


list: ORDERED_LIST text							{$$ = ListSemanticAction($1, $2, OL);}
	| UNORDERED_LIST text						    {$$ = ListSemanticAction($1, $2, UL);}
	;

text: text WS text                              {$$ = UnionTextSemanticAction($1, $2, $3);}
	| STRING 									{$$ = TextSemanticAction($1);}
	| START_LINK STRING END_LINK                {$$ = LinkSemanticAction($1,$2);}
	| B_TOKEN text B_TOKEN						{$$ = FormatTextSemanticAction($2, BOLD);}
	| I_TOKEN text I_TOKEN						{$$ = FormatTextSemanticAction($2, ITALIC);}
	| C_TOKEN text C_TOKEN						{$$ = FormatTextSemanticAction($2, CODE);}
	;

%%
