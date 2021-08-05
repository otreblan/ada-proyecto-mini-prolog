%{
#include <stdlib.h>

#include "parser.h"
#include "utils.h"
%}

%option noinput
%option nounput

%%

[(),] { return yytext[0]; }

[a-zA-Z_1-9]+ { yylval.strval = strdup(yytext); return id; }

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
