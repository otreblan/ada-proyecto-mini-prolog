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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ast_rule      ast_rule;
typedef struct _ast_rule_list ast_rule_list;

typedef struct _ast_rule_list
{
	ast_rule*      rule;
	ast_rule_list* next;
} ast_rule_list;

ast_rule_list* ast_rule_list1(ast_rule* rule);
ast_rule_list* ast_rule_list2(ast_rule* rule, ast_rule_list* rule_list);

void ast_rule_list_free(ast_rule_list* rule_list);

#ifdef __cplusplus
} // extern "C"
#endif
