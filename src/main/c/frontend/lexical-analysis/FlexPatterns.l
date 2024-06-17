%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack
%x styling
%x styling_bool
%x styling_color
%x styling_position
%x styling_size
%x styling_ff
%x hyper
/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */
nl      \n
token_class      [_\*`]
token           (_|\*|`)
escaped_token  \\(\\\\)*[_\*`]
string         (([[:graph:]]{-}[_\*`])|{escaped_token})+
whitespace [[:space:]]{-}[\n]+
BlockQuote >
Header     #+" "
List -" "
OrderedList [0-9]+". "
TipStyling "[//]: # \"#"
comment "[comment]:"
UnderlineColour uc:
Background bg:
FontColour fc:
FontSize fs:
FontFamily ff:
Underline u:
Position position:
ColourRegex #[0-9a-fA-F]{6}|red|green|blue|yellow|black|white|orange|purple|pink|brown|gray|grey
Boolean true|false
PositionValue left|right|center
Size [0-9]+px
EndStyling ";"
Fonts Arial|Sans-serif|Serif|Monospace|Cursive|Fantasy
StylingString \"([[:alnum:]]{+}[ ])+\"
URI "http"("s")?"://"[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}("/"[^\s]*)?|#([[:graph:]]{-}[[:upper:][:space:]])+ 
%%

^{BlockQuote}                                                               {return BlockquoteLexemeAction(createLexicalAnalyzerContext());}                                
^{List}                                                                     {return FirstListLexemeAction(createLexicalAnalyzerContext());}                               
^{OrderedList}                                                              {return FirstOListLexemeAction(createLexicalAnalyzerContext());}
^"    "{List}|(\t){List}|{List}                                            {return SecondListLexemeAction(createLexicalAnalyzerContext());}
^"    "{OrderedList}|(\t){OrderedList}                       {return SecondOListLexemeAction(createLexicalAnalyzerContext());}
^"    "{2,}{List}|(\t){2,}{List}                                      {return ThirdListLexemeAction(createLexicalAnalyzerContext());}
^"    "{2,}{OrderedList}|(\t){2,}{OrderedList}         {return ThirdOListLexemeAction(createLexicalAnalyzerContext());}
^{comment}.*$                                                               {IgnoredLexemeAction(createLexicalAnalyzerContext());}
^{TipStyling}                                                               {BEGIN(styling); return BeginStylingLexemeAction(createLexicalAnalyzerContext());}
<styling>{UnderlineColour}                                                  {BEGIN(styling_color); return UCTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{Background}                                                       {BEGIN(styling_color); return BCTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>[[:space:]]+                                                       {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>[[:space:]]+                                                  {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_position>[[:space:]]+                                              {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_color>[[:space:]]+                                                 {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_size>[[:space:]]+                                                  {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_ff>[[:space:]]+                                                    {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling>{FontColour}                                                       {BEGIN(styling_color); return FCTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{FontSize}                                                         {BEGIN(styling_size); return FSTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{FontFamily}                                                       {BEGIN(styling_ff); return FFTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{Underline}                                                        {BEGIN(styling_bool); return UTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{Position}                                                         {BEGIN(styling_position); return PTokenLexemeAction(createLexicalAnalyzerContext());}
<styling_ff>{Fonts}                                                         {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>{Boolean}                                                     {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_position>{PositionValue}                                           {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_size>{Size}                                                        {return StylingValueLexemeAction(createLexicalAnalyzerContext());}            
<styling_color>{ColourRegex}                                                {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_size>{EndStyling}                                                  {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_ff>{EndStyling}                                                    {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_color>{EndStyling}                                                 {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>{EndStyling}                                                  {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_position>{EndStyling}                                              {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling>"\""                                                               {BEGIN(INITIAL);return EndStylingLexemeAction(createLexicalAnalyzerContext());}
<styling>.                                                                  {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>.                                                             {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_size>.                                                             {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_position>.                                                         {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_color>.                                                            {return UnknownLexemeAction(createLexicalAnalyzerContext());}
^"> "                                                                       {return BlockquoteLexemeAction(createLexicalAnalyzerContext());}
\[([[:space:]]{-}[\n]|{string})+\]"( "                                      {BEGIN(hyper);return BeginLinkLexemeAction(createLexicalAnalyzerContext());}
<hyper>{URI}                                                                {return StringLexemeAction(createLexicalAnalyzerContext());}
<hyper>" )"                                                                 {BEGIN(INITIAL);return EndLinkLexemeAction(createLexicalAnalyzerContext());}
{nl}                                                                        {IgnoredLexemeAction(createLexicalAnalyzerContext());}
^{Header}                                                                   {return HeadingLexemeAction(createLexicalAnalyzerContext());}
{string}                                                                    {return StringLexemeAction(createLexicalAnalyzerContext()); }
{whitespace}                                                                {return WhitespaceLexemeAction(createLexicalAnalyzerContext()); }
{token}                                                                     {return TokenLexemeAction(createLexicalAnalyzerContext()); }
.                                                                           {return UnknownLexemeAction(createLexicalAnalyzerContext()); }


%%

#include "FlexExport.h"
