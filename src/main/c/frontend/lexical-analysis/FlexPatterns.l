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
TB >
TH     #+" "
TL -" "
TOL [0-9]+". "
TipStyling "[//]: # \"#"
comment "[comment]:"
TSuc uc:
TSbg bg:
TSfc fc:
TSfs fs:
TSff ff:
TSu u:
TSp position:
TScolor #[0-9a-fA-F]{6}|red|green|blue|yellow|black|white|orange|purple|pink|brown|gray|grey
TSbool true|false
TSposition left|right|center
TSsize [0-9]+px
TSend ";"
TSstring \"([[:alnum:]]{+}[ ])+\"
%%

^{TB}                                                                       {return BlockquoteLexemeAction(createLexicalAnalyzerContext());}                                
^"    "+{TOL}|(\t)+{TOL}|{TOL}                                              {return ListLexemeAction(createLexicalAnalyzerContext());}   
^"    "+{TL}|(\t)+{TL}|{TL}                                                 {return ListLexemeAction(createLexicalAnalyzerContext());}
^{comment}.*$                                                               {IgnoredLexemeAction(createLexicalAnalyzerContext());}
^{TipStyling}                                                               {BEGIN(styling); return BeginStylingLexemeAction(createLexicalAnalyzerContext());}
<styling>{TSuc}                                                             {BEGIN(styling_color); return UCTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{TSbg}                                                             {BEGIN(styling_color); return BCTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>[[:space:]]+                                                       {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>[[:space:]]+                                                  {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_position>[[:space:]]+                                              {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_color>[[:space:]]+                                                 {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_size>[[:space:]]+                                                  {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling_ff>[[:space:]]+                                                    {IgnoredLexemeAction(createLexicalAnalyzerContext());}
<styling>{TSfc}                                                             {BEGIN(styling_color); return FCTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{TSfs}                                                             {BEGIN(styling_size); return FSTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{TSff}                                                             {BEGIN(styling_ff); return FFTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{TSu}                                                              {BEGIN(styling_bool); return UTokenLexemeAction(createLexicalAnalyzerContext());}
<styling>{TSp}                                                              {BEGIN(styling_position); return PTokenLexemeAction(createLexicalAnalyzerContext());}
<styling_ff>{TSstring}                                                      {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>{TSbool}                                                      {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_position>{TSposition}                                              {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_size>{TSsize}                                                      {return StylingValueLexemeAction(createLexicalAnalyzerContext());}            
<styling_color>{TScolor}                                                    {return StylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_size>{TSend}                                                       {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_ff>{TSend}                                                         {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_color>{TSend}                                                      {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>{TSend}                                                       {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling_position>{TSend}                                                   {BEGIN(styling);return EndStylingValueLexemeAction(createLexicalAnalyzerContext());}
<styling>"\""                                                               {BEGIN(INITIAL);return EndStylingLexemeAction(createLexicalAnalyzerContext());}
<styling>.                                                                  {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_bool>.                                                             {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_size>.                                                             {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_position>.                                                         {return UnknownLexemeAction(createLexicalAnalyzerContext());}
<styling_color>.                                                            {return UnknownLexemeAction(createLexicalAnalyzerContext());}
^"> "                                                                       {return BlockquoteLexemeAction(createLexicalAnalyzerContext());}
\[([[:space:]]{-}[\n]|{string})+\]"( "                                       {BEGIN(hyper);return BeginLinkLexemeAction(createLexicalAnalyzerContext());}
<hyper>"http"("s")?"://"[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}("/"[^\s]*)?|#([[:graph:]]{-}[[:upper:][:space:]])+         {return StringLexemeAction(createLexicalAnalyzerContext());}
<hyper>" )"                                                                  {BEGIN(INITIAL);return EndLinkLexemeAction(createLexicalAnalyzerContext());}
{nl}                                                                        {IgnoredLexemeAction(createLexicalAnalyzerContext());}
^{TH}                                                                       {return HeadingLexemeAction(createLexicalAnalyzerContext());}
{string}                                                                    {return StringLexemeAction(createLexicalAnalyzerContext()); }
{whitespace}                                                                {return WhitespaceLexemeAction(createLexicalAnalyzerContext()); }
{token}                                                                     {return TokenLexemeAction(createLexicalAnalyzerContext()); }
.                                                                           {return UnknownLexemeAction(createLexicalAnalyzerContext()); }


%%
/*EOF RULEEEE*/
/*

{headerInit}                                                { BEGIN(HEADING); return HeadingLexemeAction(createLexicalAnalyzerContext()); }
<HEADING>{endline}                                          { BEGIN(INITIAL);WhitespaceLexemeAction(createLexicalAnalyzerContext());  }
<HEADING>[[:space:]]+{initItalic}                           { BEGIN(HEADING_ITALIC_FIRST); return BeginItalicLexemeAction(createLexicalAnalyzerContext()); }
<HEADING>{initItalic}[[:space:]]                            { return StringLexemeAction(createLexicalAnalyzerContext());}
<HEADING>[<<EOF>>]                                          { BEGIN(INITIAL); IgnoredLexemeAction(createLexicalAnalyzerContext());  }
<HEADING>[[:space:]]+                                       { return WhitespaceLexemeAction(createLexicalAnalyzerContext());}
<HEADING>[[:graph:]]+                                       { return StringLexemeAction(createLexicalAnalyzerContext()); }
<HEADING>.                                                  { UnknownLexemeAction(createLexicalAnalyzerContext()); }
<HEADING_ITALIC_FIRST>([[:graph:]]{-}[_])+                  { return StringLexemeAction(createLexicalAnalyzerContext());}
<HEADING_ITALIC_FIRST>[[:space:]]+{initItalic}              { BEGIN(HEADING); return StringLexemeAction(createLexicalAnalyzerContext());}
<HEADING_ITALIC_FIRST>{initItalic}[:space:]                 { BEGIN(HEADING);return CloseItalicLexemeAction(createLexicalAnalyzerContext()); } 
<HEADING_ITALIC_FIRST>{initItalic}[[:graph:]]+              { BEGIN(HEADING); return StringLexemeAction(createLexicalAnalyzerContext());}

{initItalic}[[:space:]]                                     { return StringLexemeAction(createLexicalAnalyzerContext());}
{initItalic}                                                { BEGIN(ITALIC); return BeginItalicLexemeAction(createLexicalAnalyzerContext());}
<ITALIC>{initBold}                                          { BEGIN(ITALIC_BOLD); return BeginItaliccreateLexicalAnalyzerContext(createLexicalAnalyzerContext())}
<ITALIC>{initBold}[[:space:]]                                { return StringLexemeAction(createLexicalAnalyzerContext());}
<ITALIC>([[:graph:]]{-}[_\*])+                                { return StringLexemeAction(createLexicalAnalyzerContext()); }
<ITALIC>[[:space:]]+{initItalic}                            { BEGIN(INITIAL); return StringLexemeAction(createLexicalAnalyzerContext());}
<ITALIC>{initItalic}                                        { BEGIN(INITIAL); return CloseItalicLexemeAction(createLexicalAnalyzerContext()); } 

{initBold}[[:space:]]                                      { return StringLexemeAction(createLexicalAnalyzerContext());}
{initBold}                                                 { BEGIN(BOLD); return BeginBoldLexemeAction(createLexicalAnalyzerContext());}
<BOLD>([[:graph:]]{-}[\*])+                                { return StringLexemeAction(createLexicalAnalyzerContext()); }
<BOLD>[[:space:]]+{initBold}                               { BEGIN(INITIAL); return StringLexemeAction(createLexicalAnalyzerContext());}
<BOLD>{initBold}                                           { BEGIN(INITIAL); return CloseBoldLexemeAction(createLexicalAnalyzerContext()); } 

<ITALIC_BOLD>[:space:]                                     { BEGIN(ITALIC); return StringLexemeAction(createLexicalAnalyzerContext());}
<ITALIC_BOLD>([[:graph:]]{-}[\*])+                         { return StringLexemeAction(createLexicalAnalyzerContext()); }

{endline}                                                   { return NewBlockLexemeAction(createLexicalAnalyzerContext());}


*/
#include "FlexExport.h"
