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

#include <cassert>
#include <cstdio>

#include "executor.hpp"

ada::executor::executor(const ast_prolog& prolog, const trie_map& tm):
	prolog(prolog),
	tm(tm)
{}

void ada::executor::execute()
{
	for(auto* list = prolog.rule_list; list; list = list->next)
	{
		if(auto* rule_str = list->rule)
		{
			assert(matches.empty());

			query(rule_str->id, rule_str->str);
			for(size_t i = 0; i < matches.size(); i++)
			{
				printf(
					"X = %c%s",
					matches[i],
					i == matches.size()-1 ? ".\n" : ", "
				);
			}

			matches.clear();
		}
	}
}

void ada::executor::query(std::string_view rule, std::string_view str)
{
	auto it = tm.tm.find(rule.data());

	if(it != tm.tm.end())
	{
		std::string r_str(reorder(it->second.p, str));
		traverse(it->second, r_str, 0);
	}
}

bool ada::executor::traverse(
	const trie& t,
	std::string_view str,
	ssize_t node_i
)
{
	if((size_t)node_i > t.nodes_n)
		return false;

	if(str.empty())
		return true;

	bool return_code = true;
	char c = str.at(0);

	if(c == 'X')
	{
		for(char c: t.sigma)
		{
			ssize_t i = t.matrix_index(node_i, c);

			if((i != -1) && traverse(
				t,
				str.substr(1),
				t.matrix.at(i)
			))
			{
				matches.push_back(c);
			}
		}
	}
	else
	{
		ssize_t i = t.matrix_index(node_i, c);
		if(i == -1)
			return false;

		return traverse(
			t,
			str.substr(1),
			t.matrix.at(i)
		);
	}

	return return_code;
}

std::string ada::executor::reorder(
	const std::vector<size_t>& p,
	std::string_view str
)
{
	std::string result;

	for(size_t p_i: p)
	{
		result.push_back(str.at(p_i));
	}

	return result;
}
