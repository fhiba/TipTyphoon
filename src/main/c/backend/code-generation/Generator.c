#include "Generator.h"

/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PRIVATE FUNCTIONS */

// static const char _expressionTypeToCharacter(const ExpressionType type);
// static void _generateConstant(const unsigned int indentationLevel, Constant * constant);
// static void _generateEpilogue(const int value);
// static void _generateExpression(const unsigned int indentationLevel, Expression * expression);
// static void _generateFactor(const unsigned int indentationLevel, Factor * factor);
// static void _generateProgram(Program * program);
// static void _generatePrologue(void);
// static char * _indentation(const unsigned int indentationLevel);
// static void _output(const unsigned int indentationLevel, const char * const format, ...);

// /**
//  * Converts and expression type to the proper character of the operation
//  * involved, or returns '\0' if that's not possible.
//  */

// /*
// static const char _expressionTypeToCharacter(const ExpressionType type) {
// 	switch (type) {
// 		case ADDITION: return '+';
// 		case DIVISION: return '/';
// 		case MULTIPLICATION: return '*';
// 		case SUBTRACTION: return '-';
// 		default:
// 			logError(_logger, "The specified expression type cannot be converted into character: %d", type);
// 			return '\0';
// 	}
// }

// /**
//  * Generates the output of a constant.
//  */
// static void _generateConstant(const unsigned int indentationLevel, Constant * constant) {
// 	_output(indentationLevel, "%s", "[ $C$, circle, draw, black!20\n");
// 	_output(1 + indentationLevel, "%s%d%s", "[ $", constant->value, "$, circle, draw ]\n");
// 	_output(indentationLevel, "%s", "]\n");
// }

// /**
//  * Creates the epilogue of the generated output, that is, the final lines that
//  * completes a valid Latex document.
//  */
// static void _generateEpilogue(const int value) {
// 	_output(0, "%s%d%s",
// 		"            [ $", value, "$, circle, draw, blue ]\n"
// 		"        ]\n"
// 		"    \\end{forest}\n"
// 		"\\end{document}\n\n"
// 	);
// }

// /**
//  * Generates the output of an expression.
//  */
// static void _generateExpression(const unsigned int indentationLevel, Expression * expression) {
// 	_output(indentationLevel, "%s", "[ $E$, circle, draw, black!20\n");
// 	switch (expression->type) {
// 		case ADDITION:
// 		case DIVISION:
// 		case MULTIPLICATION:
// 		case SUBTRACTION:
// 			_generateExpression(1 + indentationLevel, expression->leftExpression);
// 			_output(1 + indentationLevel, "%s%c%s", "[ $", _expressionTypeToCharacter(expression->type), "$, circle, draw, purple ]\n");
// 			_generateExpression(1 + indentationLevel, expression->rightExpression);
// 			break;
// 		case FACTOR:
// 			_generateFactor(1 + indentationLevel, expression->factor);
// 			break;
// 		default:
// 			logError(_logger, "The specified expression type is unknown: %d", expression->type);
// 			break;
// 	}
// 	_output(indentationLevel, "%s", "]\n");
// }

// /**
//  * Generates the output of a factor.
//  */
// static void _generateFactor(const unsigned int indentationLevel, Factor * factor) {
// 	_output(indentationLevel, "%s", "[ $F$, circle, draw, black!20\n");
// 	switch (factor->type) {
// 		case CONSTANT:
// 			_generateConstant(1 + indentationLevel, factor->constant);
// 			break;
// 		case EXPRESSION:
// 			_output(1 + indentationLevel, "%s", "[ $($, circle, draw, purple ]\n");
// 			_generateExpression(1 + indentationLevel, factor->expression);
// 			_output(1 + indentationLevel, "%s", "[ $)$, circle, draw, purple ]\n");
// 			break;
// 		default:
// 			logError(_logger, "The specified factor type is unknown: %d", factor->type);
// 			break;
// 	}
// 	_output(indentationLevel, "%s", "]\n");
// }

// /**
//  * Generates the output of the program.
//  */
// static void _generateProgram(Program * program) {
// 	_generateExpression(3, program->expression);
// }

// /**
//  * Creates the prologue of the generated output, a Latex document that renders
//  * a tree thanks to the Forest package.
//  *
//  * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
//  */
// static void _generatePrologue(void) {
// 	_output(0, "%s",
// 		"\\documentclass{standalone}\n\n"
// 		"\\usepackage[utf8]{inputenc}\n"
// 		"\\usepackage[T1]{fontenc}\n"
// 		"\\usepackage{amsmath}\n"
// 		"\\usepackage{forest}\n"
// 		"\\usepackage{microtype}\n\n"
// 		"\\begin{document}\n"
// 		"    \\centering\n"
// 		"    \\begin{forest}\n"
// 		"        [ \\text{$=$}, circle, draw, purple\n"
// 	);
// }

// /**
//  * Generates an indentation string for the specified level.
//  */
static char * _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}

/**
 * Outputs a formatted string to standard output.
 */
static void _output(const unsigned int indentationLevel, const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(stdout, effectiveFormat, arguments);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}

// /** PUBLIC FUNCTIONS */
void _generateProgram(Program * program);
void _generateEpilogue();
void _generatePrologue();
void _generateMasterBlock(MasterBlock * master);
void _generateHeader(Block * block, int level);
void _generateBlockQuote(Block * block);
void _generateList(List * list);
void _generateSimple(Block * block);
void _generateOrderedList(List * list);
void _generateLink(Link * link);
void _generateText(Text * text);
void _generateBlock(Block * block);
void _generateStyling(StylingBlock * styling);
void _generateStyle(Styling * style);
void _generateUnorderedList(List * list);


StylingBlock* stylesToApply = NULL;



void generate(CompilerState * compilerState) {
	logDebugging(_logger, "Generating final output...");
	_generatePrologue();
    Program * program = compilerState->abstractSyntaxtTree;
	_generateProgram(program);
	_generateEpilogue(compilerState->value);
	logDebugging(_logger, "Generation is done.");
}

void _generateProgram(Program * program) {
    if(program == NULL)
        return;
    _generateMasterBlock(program->masterBlock);
}

void _generateMasterBlock(MasterBlock * master) {
    if(master == NULL) 
        return;
    if(master->type == MASTER_BLOCK_LIST){
        _generateMasterBlock(master->first);
        _generateBlock(master->second);
    } else {
        _generateBlock(master->block);
    }
}

void _generateBlock(Block * block) {
    switch (block->type)
    {
        case H1:
            _generateHeader(block,1);
            break;
        case H2:
            _generateHeader(block,2);
            break;
        case H3:
            _generateHeader(block,3);
            break;
        case H4:
            _generateHeader(block,4);
            break;
        case H5:
            _generateHeader(block,5);
            break;
        case H6:
            _generateHeader(block,6);
            break;
        case BQ:
            _generateBlockQuote(block);
            break;
        case LIST:
            _generateList(block->list);
            break;
        case SIMPLE:
            _generateSimple(block);
            break;
        case STYLING:
            stylesToApply = block->styling;
            break;
    }
}

void _generateUnorderedList(List * list) {
    _output(0, "%s", "<ul");
    if(stylesToApply != NULL){
        _generateStyling(stylesToApply);
        stylesToApply = NULL;
    }
    _output(0, "%s", ">\n");
     _output(0, "%s", "<li>\n");
    _generateText(list->content);
    _output(0, "%s", "</li>\n");
    _output(0, "%s", "</ul>\n");
}

void _generateOrderedList(List * list) {
    _output(0, "%s", "<ol");
    if(stylesToApply != NULL){
        _generateStyling(stylesToApply);
        stylesToApply = NULL;
    }
    _output(0, "%s", ">\n");
    _output(0, "%s", "<li>\n");
    _generateText(list->content);
    _output(0, "%s", "</li>\n");
    _output(0, "%s", "</ol>\n");
}

void _generateList(List * list) {
    switch (list->type)
    {
        case UL:
            _generateUnorderedList(list);
            break;
        case OL:
            _generateOrderedList(list);
            break;
    }
}


void _generateBlockQuote(Block * block) {
    _output(0, "%s", "<blockquote");
    if(stylesToApply != NULL){
        _generateStyling(stylesToApply);
        stylesToApply = NULL;
    }
    _output(0, "%s", ">\n");
        _generateText(block->text);
    _output(0, "%s", "</blockquote>\n");
}

void _generateHeader(Block * block, int level) {
    _output(0, "%s", "<h");
    _output(0, "%d", level);
    if(stylesToApply != NULL){
        _generateStyling(stylesToApply);
        stylesToApply = NULL;
    }
    _output(0, "%s", ">\n");
        _generateText(block->text);
    _output(0, "%s", "</h");
    _output(0, "%d", level);
    _output(0, "%s", ">\n");
}


void _generateSimple(Block * block) {
    _output(0, "%s", "<p");
    if(stylesToApply != NULL){
        _generateStyling(stylesToApply);
        stylesToApply = NULL;
    }
    _output(0, "%s", ">\n");
        _generateText(block->text);
    _output(0, "%s", "</p>\n");
}

void _generatePrologue(){
    _output(0, "%s", "<!DOCTYPE html>\n");
    _output(0, "%s", "<html>\n");
    _output(0, "%s", "<head>\n");
    _output(0, "%s", "<title>HTML Output</title>\n");
    _output(0, "%s", "</head>\n");
    _output(0, "%s", "<body>\n");

}

void _generateEpilogue(){
    _output(0, "%s", "</body>\n");
    _output(0, "%s", "</html>\n");
    //open file
    //write output to file
    //close file
    
}

void _generateText(Text * text) {
    switch (text->type)
    {

    case TEXT:
        _output(0, "%s", text->string);
        break;
    case UNION:
        _generateText(text->left);
        _output(0, "%s", text->string);
        _generateText(text->right);
        break;
    case BOLD:
        _output(0, "%s", "<strong>");
        _generateText(text->child);
        _output(0, "%s", "</strong>");
        break;
    case ITALIC:
        _output(0, "%s", "<em>");
        _generateText(text->child);
        _output(0, "%s", "</em>");
        break;
    case CODE:
        _output(0, "%s", "<code>");
        _generateText(text->child);
        _output(0, "%s", "</code>");
        break;
    case LINK:
        _generateLink(text->link);
        break;
    };
}

void _generateLink(Link * link) {
    _output(0, "%s", "<a href=\"");
    _output(0, "%s", link->link);
    _output(0, "%s", "\">");
    _output(0,"%s",link->string);
    _output(0, "%s", "</a>");
}


void _generateStyle(Styling * style) {
    switch (style->type)
    {
    	case FF:
            _output(0, "%s", "font-family:");
            _output(0, "%s", style->string);
            _output(0, "%s", ", sans-serif;");
            _output(0, "%s", ";");
            break;
	    case FS:
            _output(0, "%s", "font-size:");
            _output(0, "%s", style->string);
            _output(0, "%s", ";");
            break;
	    case FC:
            _output(0, "%s", "color:");
            _output(0, "%s", style->string);
            _output(0, "%s", ";");
            break;
	    case BC:
            _output(0, "%s", "background-color:");
            _output(0, "%s", style->string);
            _output(0, "%s", ";");
            break;
	    case UC:
            _output(0, "%s", "text-decoration-color:");
            _output(0, "%s", style->string);
            _output(0, "%s", ";");
            break;
	    case U:
            _output(0, "%s", "text-decoration:");
            _output(0, "%s", "underline;");
            break;
	    case P:
            _output(0, "%s", "justify-content:");
            _output(0, "%s", style->string);
            _output(0, "%s", ";");
            break;
    }
}

void _generateStyling(StylingBlock * styling) {
    _output(0, "%s", " style=\"");
    switch (styling->type)
    {
        case STYLING_BLOCK_LIST:
            _generateStyling(styling->block);
            _generateStyle(styling->styling);
            break;
        case STYLING_BLOCK:
            _generateStyle(styling->style);
            break;
    }
    _output(0, "%s", "\"");
}