%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	char* string;
	Token token;

	/** Non-terminals. */

	Word * word;
	Block * block;
	Program * program;
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
%token <token> HEADING1_BEGIN
%token <token> HEADING2_BEGIN
%token <token> HEADING3_BEGIN
%token <token> HEADING4_BEGIN
%token <token> HEADING5_BEGIN
%token <token> HEADING6_BEGIN
%token <token> HEADING_END

%token <token> UNKNOWN

/** Non-terminals. */
%type <word> word
%type <block> block
%type <program> program

%%

program: block													{ $$ = BlockProgramSemanticAction(currentCompilerState(), $1); }
	;

block: HEADING1_BEGIN block HEADING_END							{ $$ = HeadingBlockSemanticAction( $2, HEADING1); }
	|HEADING2_BEGIN block HEADING_END							{ $$ = HeadingBlockSemanticAction( $2, HEADING2); }
	|HEADING3_BEGIN block HEADING_END							{ $$ = HeadingBlockSemanticAction( $2, HEADING3); }
	|HEADING4_BEGIN block HEADING_END							{ $$ = HeadingBlockSemanticAction( $2, HEADING4); }
	|HEADING5_BEGIN block HEADING_END							{ $$ = HeadingBlockSemanticAction( $2, HEADING5); }
	|HEADING6_BEGIN block HEADING_END							{ $$ = HeadingBlockSemanticAction( $2, HEADING6); }
	|word block													{ $$ = WordBlockSemanticAction( $1, $2); }
	|word														{ $$ = WordBlockSemanticAction( $1, NULL); }
	;
word: STRING													{ $$ = StringWordSemanticAction($1); }
	;
%%
