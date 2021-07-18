%{
#include <stdlib.h>

#include "compiler/parser.h"
#include "parser.h"
%}

%option noinput
%option nounput

%%

duenho   { return duenho; }
hermanos { return hermanos; }

[(),] { return yytext[0]; }

[a-zA-Z] { yylval.charval = yytext[0]; return character; }

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
