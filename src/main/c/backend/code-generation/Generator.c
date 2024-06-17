#include "Generator.h"
#include "../domain-specific/LinkChecker.h"
/* MODULE INTERNAL STATE */
FILE *file;
boolean lastWasList = false;
ListDepth lastListDepth = -1;
ListType depthArray[3];
StylingType appliedStyles[7];

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
    fflush(file);
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
void _closePrevListType(ListDepth newDepth, ListDepth lastDepth);
void _applyStyling();
void _cleanStyles();

StylingBlock* stylesToApply = NULL;



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
    if(lastWasList) {
        _closePrevListType(-1, lastListDepth);
    }
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
    logDebugging(_logger, "Block type: %d", block->type);
    logDebugging(_logger, "last was list? %s", lastWasList == true? "true":"false"); 
    if(lastWasList && block->type != LIST && block->type != STYLING) { 
        logDebugging(_logger, "Closing previous list...");
        _closePrevListType(-1, lastListDepth);
        lastWasList = false;
    }
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
            lastWasList = true;
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

void _generateUnorderedList(List * list) {
    _output(0, "%s", "<ul");
    if(stylesToApply != NULL){
        _output(0, "%s", " style=\"");
        _applyStyling();
        _output(0, "%s", "\"");
        stylesToApply = NULL;
    }
    _output(0, "%s", ">\n");
     _output(0, "%s", "<li>\n");
    _generateText(list->content);
    _output(0, "%s", "</li>\n");
}

void _generateOrderedList(List * list) {
    _output(0, "%s", "<ol");
    if(stylesToApply != NULL){
        _output(0, "%s", " style=\"");
        _applyStyling();
        _output(0, "%s", "\"");
        stylesToApply = NULL;
    }
    _output(0, "%s", ">\n");
    _output(0, "%s", "<li>\n");
    _generateText(list->content);
    _output(0, "%s", "</li>\n");

}


void _generateListType(List * list) {
    switch (list->type)
    {
        case UL:
            _generateUnorderedList(list);
            break;
        case OL:
            _generateOrderedList(list);
            break;
        default:
            logError(_logger, "Unknown list type");
            break;
    }
    depthArray[list->depth] = list->type;
}

void _closePrevListType(ListDepth newDepth, ListDepth lastDepth) {
    if(newDepth == -1){
        _output(0, "</li>\n");
        switch(depthArray[lastDepth]){
            case UL:
                _output(0, "</ul>\n");
                break;
            case OL:
                _output(0, "</ol>\n");
                break;
            default:
                logError(_logger, "Unknown list type");
                break;
        }
        lastDepth--;
    }
    while((int)lastDepth > (int)newDepth){
        switch(depthArray[lastDepth]){
            case UL:
                _output(0, "</ul>\n");
                break;
            case OL:
                _output(0, "</ol>\n");
                break;
            default:
                logError(_logger, "Unknown list type");
                break;
        }
        lastDepth--;
    }
}

void _generateList(List * list) {
    if(lastWasList) {
        if(lastListDepth < list->depth) { // sub item o sub lista
            _generateListType(list);

        } else if(lastListDepth > list->depth){ //cerrando sub item o sub lista
            _closePrevListType(list->depth, lastListDepth);
            
            if(list->type == depthArray[list->depth]) {
                _output(0, "<li");
                if (stylesToApply != NULL)
                {
                    _output(0, "%s", " style=\"");
                    _applyStyling();
                    _output(0, "%s", "\"");
                    stylesToApply = NULL;
                }
                _output(0, ">\n");
                _generateText(list->content);
            } else{
                _generateListType(list);
            }
            
        } else { // mismo depth, puede ser otra lista o sub item
            if (list->depth > DEPTH_1)
            {
                if (depthArray[lastListDepth] != list->type)
                {
                    _generateListType(list);
                }
                else
                {
                    _output(0, "<li");
                    if (stylesToApply != NULL)
                    {
                        _output(0, "%s", " style=\"");
                        _applyStyling();
                        _output(0, "%s", "\"");
                        stylesToApply = NULL;
                    }
                    _output(0, ">\n");
                    _generateText(list->content);
                }
            }
            else{
                if(list->type == depthArray[lastListDepth]) {
                    _output(0, "<li");
                    if (stylesToApply != NULL)
                    {
                        _output(0, "%s", " style=\"");
                        _applyStyling();
                        _output(0, "%s", "\"");
                        stylesToApply = NULL;
                    }

                    _output(0, ">\n");
                    _generateText(list->content);
                } else{
                    _generateListType(list);
                }
            }
        }
    } else {
        _generateListType(list);
    }
    lastListDepth = list->depth;
}


void _generateBlockQuote(Block * block) {
    _output(0, "%s", "<blockquote");
    if (stylesToApply != NULL)
    {
        _output(0, "%s", " style=\"");
        _applyStyling();
        _output(0, "%s", "\"");
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
    if (stylesToApply != NULL)
    {
        _output(0, "%s", " style=\"");
        _applyStyling();
        _output(0, "%s", "\"");
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
    if (stylesToApply != NULL)
    {
        _output(0, "%s", " style=\"");
        _applyStyling();
        _output(0, "%s", "\"");
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
    if(appliedStyles[style->type]) {
        logDebugging(_logger, "Style already applied, skipping...");
        return;
    }
    switch (style->type)
    {
    	case FF:
            _output(0, "%s", "font-family:");
            _output(0, "%s", style->string);
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
            _output(0, "%s", "text-align:");
            _output(0, "%s", style->string);
            _output(0, "%s", ";");
            break;
    }
    appliedStyles[style->type] = true;
}

void _generateStyling(StylingBlock * styling) {
    logDebugging(_logger, "Applying styling...");
    switch (styling->type)
    {
        case STYLING_BLOCK_LIST:
            logDebugging(_logger, "Styling Block List");
            _generateStyling(styling->block);
            _generateStyle(styling->styling);
            break;
        case STYLING_BLOCK:
            logDebugging(_logger, "Styling Block");
            _generateStyle(styling->styling);
            break;
    }
    
}
void _applyStyling() {
        _generateStyling(stylesToApply);
    _cleanStyles();
}
void _cleanStyles() {
    for (size_t i = 0; i < 7; i++) {
        appliedStyles[i] = false;
    }
    
}