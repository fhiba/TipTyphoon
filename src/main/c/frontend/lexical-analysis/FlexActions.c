#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

/*
Token HeadingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->length) 
	{
	case 1:
		token = HEADING1_BEGIN;
		break;
	case 2:
		token = HEADING2_BEGIN;
		break;
	case 3:
		token = HEADING3_BEGIN;
		break;
	case 4:
		token = HEADING4_BEGIN;
		break;
	case 5:
		token = HEADING5_BEGIN;
		break;
	default:
		token = HEADING6_BEGIN;
		break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}
*/

Token HeadingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = HEADER_TOKEN;
	return HEADER_TOKEN;
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

Token WhitespaceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	return WHITESPACE;
}

Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	return STRING;
}

Token TokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token newToken;
	switch (lexicalAnalyzerContext->lexeme[0])
	{
	case '_':
		newToken = I_TOKEN;
		break;
	
	case '*':
		newToken = B_TOKEN;
		break;
	default:
		return NoTokenLexemeAction(lexicalAnalyzerContext);
		break;
	}

	lexicalAnalyzerContext->semanticValue->token = newToken;
	return newToken;

}

Token NoTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	return NO_TOKEN;
}

Token NewlineLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	
	lexicalAnalyzerContext->semanticValue->token = NEW_LINE;
	return NEW_LINE;
}


Token StylingValueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	return STYLING_VALUE;
}

Token UTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = U_TOKEN;
	return U_TOKEN;
}

Token FFTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = FF_TOKEN;
	return FF_TOKEN;
}

Token FSTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = FS_TOKEN;
	return FS_TOKEN;
}

Token FCTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = FC_TOKEN;
	return FC_TOKEN;

}

Token BCTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = BC_TOKEN;
	return BC_TOKEN;
}

Token UCTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = UC_TOKEN;
	return UC_TOKEN;
}

Token PTokenLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = P_TOKEN;
	return P_TOKEN;
}

Token EndStylingValueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = END_STYLING_VALUE;
	return END_STYLING_VALUE;
}

Token BeginStylingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = BEGIN_STYLING;
	return BEGIN_STYLING;
}


Token EndStylingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = END_STYLING;
	return END_STYLING;
}