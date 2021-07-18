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

static ast_character_list* ast_character_list_alloc();

static ast_character_list* ast_character_list_alloc()
{
	ast_character_list* character_list = malloc(sizeof(ast_character_list));

	if(character_list)
		*character_list = (ast_character_list)
		{
			.next = NULL
		};

	return character_list;
}

ast_character_list* ast_character_list1(char c)
{
	ast_character_list* character_list = ast_character_list_alloc();

	if(character_list)
		character_list->c = c;

	return character_list;
}

ast_character_list* ast_character_list2(char c, ast_character_list* character_list)
{
	ast_character_list* _character_list = ast_character_list1(c);

	if(_character_list)
		_character_list->next = character_list;

	return _character_list;
}

void ast_character_list_free(ast_character_list* character_list)
{
	if(character_list)
	{
		ast_character_list_free(character_list->next);
	}
	free(character_list);
}
