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

#include "rule_list.h"
#include "rule.h"

static ast_rule_list* ast_rule_list_alloc();

static ast_rule_list* ast_rule_list_alloc()
{
	ast_rule_list* rule_list = malloc(sizeof(ast_rule_list));

	if(rule_list)
		*rule_list = (ast_rule_list)
		{
			.rule = NULL,
			.next = NULL
		};

	return rule_list;
}

ast_rule_list* ast_rule_list1(ast_rule* rule)
{
	ast_rule_list* rule_list = ast_rule_list_alloc();

	if(rule_list)
		rule_list->rule = rule;

	return rule_list;
}

ast_rule_list* ast_rule_list2(ast_rule* rule, ast_rule_list* rule_list)
{
	ast_rule_list* _rule_list = ast_rule_list1(rule);

	if(_rule_list)
		_rule_list->next = rule_list;

	return _rule_list;
}

void ast_rule_list_free(ast_rule_list* rule_list)
{
	if(rule_list)
	{
		ast_rule_free(rule_list->rule);
		ast_rule_list_free(rule_list->next);
	}
	free(rule_list);
}
