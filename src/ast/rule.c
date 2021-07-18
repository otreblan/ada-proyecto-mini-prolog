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

#include "character_list.h"
#include "rule.h"

static ast_rule* ast_rule_alloc();

static ast_rule* ast_rule_alloc()
{
	ast_rule* rule = malloc(sizeof(ast_rule));

	if(rule)
		*rule = (ast_rule)
		{
			.character_list = NULL
		};

	return rule;
}

ast_rule* ast_rule1(ast_id id, ast_character_list* character_list)
{
	ast_rule* rule = ast_rule_alloc();

	if(rule)
	{
		rule->id             = id;
		rule->character_list = character_list;
	}

	return rule;
}

void ast_rule_free(ast_rule* rule)
{
	if(rule)
	{
		ast_character_list_free(rule->character_list);
	}
	free(rule);
}
