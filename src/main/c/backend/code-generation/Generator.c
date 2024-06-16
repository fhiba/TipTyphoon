#include "Generator.h"
#include "../domain-specific/LinkChecker.h"
/* MODULE INTERNAL STATE */
FILE *file;

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
    vfprintf(file, effectiveFormat, arguments);
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
void _openList(ListType type);
void _closeList(ListType type);
void _generateList(FirstTList * list);
void _generateSimple(Block * block);
void _generateLink(Link * link);
void _generateText(Text * text);
void _generateBlock(Block * block);
void _generateStyling(StylingBlock * styling);
void _generateStyle(Styling * style);
void _generateUnorderedList(List * list);
void outputTypeEnd(ListType type);

StylingBlock* stylesToApply = NULL;



ListTypeNode * insertIntoList(ListTypeNode * head, ListType type) {
    ListTypeNode * newNode = (ListTypeNode *) calloc(1, sizeof(ListTypeNode));
    newNode->type = type;
    newNode->next = head;
    return newNode;
}

ListTypeNode * removeHead(ListTypeNode * head) {
    ListTypeNode * aux = head;
    head = head->next;
    free(aux);
    return head;
}


void generate(CompilerState * compilerState) {
    logDebugging(_logger, "Generating final output...");
    Program * program = compilerState->abstractSyntaxtTree;
	_generatePrologue();
	_generateProgram(program);
	_generateEpilogue(compilerState->value);
	logDebugging(_logger, "Generation is done.");
}

void _generateProgram(Program * program) {
    if(program == NULL)
        return;
    logDebugging(_logger, "Generating program output...");
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
    logDebugging(_logger, "Generating Block...");
    switch (block->type)
    {
        case H1:
            logDebugging(_logger, "Generating Header1...");
            _generateHeader(block,1);
            break;
        case H2:
            logDebugging(_logger, "Generating Header2...");
            _generateHeader(block,2);
            break;
        case H3:
            logDebugging(_logger, "Generating Header3...");
            _generateHeader(block,3);
            break;
        case H4:
            logDebugging(_logger, "Generating Header4...");
            _generateHeader(block,4);
            break;
        case H5:
            logDebugging(_logger, "Generating Header5...");
            _generateHeader(block,5);
            break;
        case H6:
            logDebugging(_logger, "Generating Header6...");
            _generateHeader(block,6);
            break;
        case BQ:
            logDebugging(_logger, "Generating BlockQuote...");
            _generateBlockQuote(block);
            break;
        case LIST:
            logDebugging(_logger, "Generating List...");
            _generateList(block->list);
            break;
        case SIMPLE:
            logDebugging(_logger, "Generating Simple Block...");
            _generateSimple(block);
            break;
        case STYLING:
            stylesToApply = block->styling;
            break;
    }
}


void _generateThirdTItem(void * item) {
    logDebugging(_logger, "Generating Third Tier Item...");
    _output(0, "<li>");
    _generateText(((ThirdTItemUnordered*)item)->text);
    _output(0, "</li>\n");
}


void _generateThirdTNode(void * node) {
    logDebugging(_logger, "Generating Third Tier Node...");
    switch (((ThirdTNodeOrdered*)node)->type)
    {
    case NODE:
        _generateThirdTNode(((ThirdTNodeOrdered*)node)->node);
        _generateThirdTItem(((ThirdTNodeOrdered*)node)->appended);
        break;
    case LEAF:
        _generateThirdTItem(((ThirdTNodeOrdered*)node)->item);
        break;
    default:
        break;
    }
}

void _generateThirdTList(ThirdTList * list) {
    logDebugging(_logger, "Generating Third Tier List...");
    switch (list->type)
    {
    case UL:
        logDebugging(_logger, "Generating Unordered List...");
        _openList(UL);
        _generateThirdTNode(list->ordered);
        _closeList(UL);
        break;
    case OL:
        logDebugging(_logger, "Generating Ordered List...");
        _openList(OL);
        _generateThirdTNode(list->unordered);
        _closeList(OL);
        break;
    default:
        logCritical(_logger, "Unknown list type: %d", list->type);
        break;
    }
}

void _generateSecondTItem(void *item)
{
    logDebugging(_logger, "Generating Second Tier Item...");
    _output(0, "<li>");
    switch (((SecondTItemOrdered *)item)->type)
    {
    case ITEM:
        _generateText(((SecondTItemOrdered *)item)->text);
        break;
    case LIST_ITEM:
        _generateThirdTList(((SecondTItemOrdered *)item)->list);
        break;
    default:
        break;
    }
    _output(0, "</li>\n");
}

void _generateSecondTNode(void * node) {
    logDebugging(_logger, "Generating Second Tier Node...");
    switch (((SecondTNodeOrdered*)node)->type)
    {
    case NODE:
        _generateSecondTNode(((SecondTNodeOrdered*)node)->node);
        _generateSecondTItem(((SecondTNodeOrdered*)node)->appended);
        break;
    case LEAF:
        _generateSecondTItem(((SecondTNodeOrdered*)node)->item);
        break;
    default:
        break;
    }
}

void _generateSecondTList(SecondTList * list) {
    logDebugging(_logger, "Generating Second Tier List...");
    switch (list->type)
    {
    case UL:
        logDebugging(_logger, "Generating Unordered List...");
        _openList(UL);
        _generateSecondTNode(list->ordered);
        _closeList(UL);
        break;
    case OL:
        logDebugging(_logger, "Generating Ordered List...");
        _openList(OL);
        _generateSecondTNode(list->unordered);
        _closeList(OL);
        break;
    default:
        logCritical(_logger, "Unknown list type: %d", list->type);
        break;
    }
}

void _generateFirstTItem(void *item)
{
    logDebugging(_logger, "Generating First Tier Item...");
    _output(0, "<li>");
    switch (((FirstTItemOrdered *)item)->type)
    {
    case ITEM:

        _generateText(((FirstTItemOrdered *)item)->text);

        break;
    case LIST_ITEM:
        _generateSecondTList(((FirstTItemOrdered *)item)->list);
        break;
    default:
        break;
    }
    _output(0, "</li>\n");
}

void _generateFirstTNode(void * node) {
    logDebugging(_logger, "Generating First Tier Node...");
    switch (((FirstTNodeOrdered*)node)->type)
    {
    case NODE:
        _generateFirstTNode(((FirstTNodeOrdered*)node)->node);
        _generateFirstTItem(((FirstTNodeOrdered*)node)->appended);
        break;
    case LEAF:
        _generateFirstTItem(((FirstTNodeOrdered*)node)->item);
        break;
    default:
        break;
    }
}

void _generateList(FirstTList * list) {
    logDebugging(_logger, "Generating List...");
    switch (list->type)
    {
    case UL:
        logDebugging(_logger, "Generating Unordered List...");
        _openList(UL);
        _generateFirstTNode(list->ordered);
        _closeList(UL);
        break;
    case OL:
        logDebugging(_logger, "Generating Ordered List...");
        _openList(OL);
        _generateFirstTNode(list->unordered);
        _closeList(OL);
        break;
    default:
        logCritical(_logger, "Unknown list type: %d", list->type);
        break;
    }
}

void _openList(ListType type) {
    switch (type)
    {
    case UL:
        _output(0, "<ul");
        if (stylesToApply != NULL)
        {
            _generateStyling(stylesToApply);
            stylesToApply = NULL;
        }
        _output(0, ">\n");
        break;
    case OL:
        _output(0, "<ol");
        if (stylesToApply != NULL)
        {
            _generateStyling(stylesToApply);
            stylesToApply = NULL;
        }
        _output(0, ">\n");
        break;
    default:
        break;
    }
}
void _closeList(ListType type) {
    switch (type)
    {
    case UL:
        _output(0, "</ul>\n");
        break;
    case OL:
        _output(0, "</ol>\n");
        break;
    default:
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
    logDebugging(_logger, "Generating Header...");
    _output(0, "%s", "<h");
    _output(0, "%d", level);
    char * aux = processText(block->text);
    _output(0, " id=\"%s\"",aux);
    free(aux);
    if(stylesToApply != NULL){
        logDebugging(_logger, "Applying styles to header...");
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
    file = fopen("output.html", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
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
    fclose(file);
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
        _output(0, "%s", text->ws);
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
    logDebugging(_logger, "Generating style %s...",style);
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
            logDebugging(_logger, "Adding background color...");
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
    logDebugging(_logger, "Applying style %s...",styling->type);
    _output(0, "%s", " style=\"");
    switch (styling->type)
    {
        case STYLING_BLOCK_LIST:
            logDebugging(_logger, "Styling Block List");
            _generateStyling(styling->block);
            _generateStyle(styling->styling);
            break;
        case STYLING_BLOCK:
            logDebugging(_logger, "Styling Block");
            _generateStyle(styling->style);
            break;
    }
    _output(0, "%s", "\"");
}