%{
#include <stdlib.h>

#include "parser.h"
#include "utils.h"
%}

%option noinput
%option nounput

%%

[(),] { return yytext[0]; }

[a-zA-Z] { yylval.charval = yytext[0]; return character; }

[a-zA-Z_]+ { yylval.strval = strdup(yytext); return id; }

[ \n\r\t]+ {}
%%

void __parse_file_init(FILE* file)
{
	yyin = file;
}

void __parse_file_free(void)
{
	yyin = stdin;
	yylex_destroy();
}
