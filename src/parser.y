%{
#include <stdio.h>

#include "utils.h"

int yylex();
void yyerror(ast_prolog** prolog, const char* s);
%}

%code requires {
#include "ast.h"
}

%parse-param { ast_prolog** prolog }
%define parse.lac full
%define parse.error verbose

%union {
	char* strval;

	ast_character_list* character_list;
	ast_rule*           rule;
	ast_rule_list*      rule_list;
}

%destructor { free($$); }                    <strval>
%destructor { ast_rule_free($$); }           <rule>
%destructor { ast_rule_list_free($$); }      <rule_list>

%token duenho
%token hermanos

%token<strval>  id

%type<rule>           rule
%type<rule_list>      rule_list

%%

prolog
	: rule_list
	{
		if(prolog)
			*prolog = ast_prolog1($1);
		else
			ast_rule_list_free($1);
	}
	;

rule_list
	: rule           { $$ = ast_rule_list1($1);     }
	| rule rule_list { $$ = ast_rule_list2($1, $2); }
	;

rule
	: id id { $$ = ast_rule1($1, $2); }
	;

%%

void yyerror(__attribute__((unused)) ast_prolog** prolog, const char* s)
{
	fprintf(stderr, "%s\n", s);
}

ast_prolog* parse_file(FILE* file)
{
	if(!file)
		return NULL;

	ast_prolog* prolog = NULL;
	__parse_file_init(file);

	yyparse(&prolog);

	__parse_file_free();
	return prolog;
}
