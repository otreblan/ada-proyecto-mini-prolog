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

#include "rule.h"

static ast_rule* ast_rule_alloc();

static ast_rule* ast_rule_alloc()
{
	ast_rule* rule = malloc(sizeof(ast_rule));

	if(rule)
		*rule = (ast_rule)
		{
			.str = NULL,
			.id  = NULL
		};

	return rule;
}

ast_rule* ast_rule1(char* id, char* str)
{
	ast_rule* rule = ast_rule_alloc();

	if(rule)
	{
		rule->id  = id;
		rule->str = str;
	}

	return rule;
}

void ast_rule_free(ast_rule* rule)
{
	if(rule)
	{
		free(rule->id);
		free(rule->str);
	}
	free(rule);
}
