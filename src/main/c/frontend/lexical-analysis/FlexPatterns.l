%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x HEADING

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%




"#+ "                             { return HeadingLexemeAction(createLexicalAnalyzerContext()); BEGIN(HEADING); }
<HEADING>[^[:space:]]+            { return StringLexemeAction(createLexicalAnalyzerContext()); }
<HEADING>[[:space:]]+             { return IgnoredLexemAction(createLexicalAnalyzerContext()); }
<HEADING>"\n"                     { return EndHeadingLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }


[^[:space:]#]+                    { return StringLexemeAction(createLexicalAnalyzerContext()); }
[[:space:]]+					  { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.								  { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
