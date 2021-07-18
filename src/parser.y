%{
#include <stdio.h>

int yylex();
void yyerror(const char* s);
%}

%define parse.lac full
%define parse.error verbose

%union {
	char charval;
}

%token duenho
%token hermanos

%token<charval> character

%%

prolog
	: rule_list
	;

rule_list
	: rule
	| rule rule_list
	;

rule
	: id '(' character_list ')'
	;

id
	: duenho
	| hermanos
	;

character_list
	: character
	| character ',' character_list
	;

%%

void yyerror(const char* s)
{
	fprintf(stderr, "%s\n", s);
}
