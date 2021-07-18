%{
#include <stdlib.h>

#include "parser.h"
%}

%option noinput
%option nounput

%%

duenho   { return duenho; }
hermanos { return hermanos; }

[(),] { return yytext[0]; }

[a-zA-Z] { yylval.charval = yytext[0]; return character; }

%%
