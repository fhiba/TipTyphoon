#include "FlexActions.h"

/* MODULE INTERNAL STATE */
#define H1 2
#define H2 3
#define H3 4
#define H4 5
#define H5 6

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

Token WhitespaceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = lexicalAnalyzerContext->lexeme;
	return WS;
}


Token HeadingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->length)
	{
	case H1:
		token = H1_TOKEN;
		break;
	case H2:
		token = H2_TOKEN;
		break;
	case H3:
		token = H3_TOKEN;
		break;
	case H4:
		token = H4_TOKEN;
		break;
	case H5:
		token = H5_TOKEN;
		break;
	default:
		token = H6_TOKEN;
		break;
	}
	
	
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
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
	}

	lexicalAnalyzerContext->semanticValue->token = newToken;
	return newToken;

}



Token ListLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	int tabCount = 0;
	for(int i = 0; i < lexicalAnalyzerContext->length && (lexicalAnalyzerContext->lexeme[i] == ' ' || lexicalAnalyzerContext->lexeme[i] == '\t'); ++i) {
		if(lexicalAnalyzerContext->lexeme[i] == ' ' && tabCount % 4 == 0){
			tabCount++;
		} else if(lexicalAnalyzerContext->lexeme[i] == '\t'){
			tabCount++;
		}
	}
	int length = lexicalAnalyzerContext->length -2;
	if(lexicalAnalyzerContext->lexeme[length] == '-') {
		token = UNORDERED_LIST;
	} else {
		token = ORDERED_LIST;
	}
	lexicalAnalyzerContext->semanticValue->integer = tabCount;
	return token;
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


Token BeginLinkLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	int  length = lexicalAnalyzerContext->length - 3;
	char * helper = calloc(length, sizeof(char));
	for(int i = 1; i < length; ++i) {
		helper[i-1] = lexicalAnalyzerContext->lexeme[i];
	}
	lexicalAnalyzerContext->semanticValue->string = helper;
	return START_LINK;	
}

Token EndLinkLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = END_LINK;
	return END_LINK;
}
 
Token BlockquoteLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = BLOCKQUOTE_TOKEN;
	return BLOCKQUOTE_TOKEN;
}
