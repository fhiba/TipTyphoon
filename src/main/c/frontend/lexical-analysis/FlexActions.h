#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */


Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token TokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token HeadingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token StylingValueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token UTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token FFTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token FSTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token FCTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token BCTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token UCTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token PTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token EndStylingValueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token EndStylingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token BeginStylingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token WhitespaceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token BeginLinkLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token EndLinkLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token BlockquoteLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token FirstOListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token FirstListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token SecondOListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token SecondListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ThirdOListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ThirdListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

#endif