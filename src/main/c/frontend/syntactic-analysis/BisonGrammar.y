%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	char* string;
	Token token;

	/** Non-terminals. */

	TInline * t_inline;
	NTInline * nt_inline;
	Block * block;
	Program * program;
	MasterBlock * master_block;
	Styling * styling;
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
%token <string> WHITESPACE;
%token <token> HEADER_TOKEN
%token <token> B_TOKEN
%token <token> I_TOKEN
%token <token> C_TOKEN
%token <string> NO_TOKEN
%token <token> NEW_LINE
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


%token <token> UNKNOWN

/** Non-terminals. */
%type <nt_inline> nt_inline
%type <t_inline> t_inline
%type <block> block
%type <program> program
%type <master_block> master_block
%type <styling> styling
%%

program: master_block                  {$$ = MasterBlockProgramSemanticAction(currentCompilerState(), $1);}
	;


master_block: block						{$$ = MasterBlockSemanticAction($1, NULL, MASTER_BLOCK);}
            | block master_block		{$$ = MasterBlockSemanticAction($1, $2, MASTER_BLOCK_LIST);}
	;


styling: FS_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, FS);}
	| FF_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, FF);}
	| FC_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, FC);}
	| BC_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, BC);}
	| UC_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, UC);}
	| U_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, U);}
	| P_TOKEN STYLING_VALUE END_STYLING_VALUE 		{$$ = StylingSemanticAction($2, P);}
	| styling styling 								{$$ = UnionStylingSemanticAction($1, $2);}
	;
block: HEADER_TOKEN block						{$$ = HeaderBlockSemanticAction($2);}
    | t_inline 									{$$ = TSimpleBlockSemanticAction($1);}
    | nt_inline 								{$$ = NTSimpleBlockSemanticAction($1);}
	| BEGIN_STYLING styling END_STYLING			{$$ = StylingBlockSemanticAction($2);}
	| block NEW_LINE							{$$ = WNLBlockSemanticAction($1);}
	;


t_inline: STRING							{$$ = TStringSemanticAction($1);}
        | t_inline nt_inline t_inline		{$$ = UnionSemanticAction($1,$2,$3);}
    	| B_TOKEN t_inline B_TOKEN			{$$ = TInlineSemanticAction($2,BOLD);}
     	| I_TOKEN t_inline I_TOKEN			{$$ = TInlineSemanticAction($2,ITALIC);}
    	| C_TOKEN t_inline C_TOKEN			{$$ = TInlineSemanticAction($2,CODE);}
    ;

nt_inline: WHITESPACE						{$$ = NTStringSemanticAction($1);}
	    | NO_TOKEN							{$$ = NTStringSemanticAction($1);}
		| nt_inline nt_inline				{$$ = appendUnionSemanticAction($1,$2);}
        | t_inline nt_inline				{$$ = appendTSemanticAction($1,$2);}
        | nt_inline t_inline                {$$ = appendNTSemanticAction($1,$2);}
    ;
%%
