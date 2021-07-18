// Mini prolog
// Copyright © 2021 otreblan
//
// mini-prolog is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// mini-prolog is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with mini-prolog.  If not, see <http://www.gnu.org/licenses/>.

#include <stdlib.h>

#include "prolog.h"
#include "rule_list.h"

static ast_prolog* ast_prolog_alloc();

static ast_prolog* ast_prolog_alloc()
{
	ast_prolog* prolog = malloc(sizeof(ast_prolog));

	if(prolog)
		*prolog = (ast_prolog)
		{
			.rule_list = NULL
		};

	return prolog;
}

ast_prolog* ast_prolog1(ast_rule_list* rule_list)
{
	ast_prolog* prolog = ast_prolog_alloc();

	if(prolog)
		prolog->rule_list = rule_list;

	return prolog;
}

void ast_prolog_free(ast_prolog* prolog)
{
	if(prolog)
	{
		ast_rule_list_free(prolog->rule_list);
	}
	free(prolog);
}
