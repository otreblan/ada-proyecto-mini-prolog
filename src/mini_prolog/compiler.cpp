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

#include <string_view>

#include "compiler.hpp"

ada::compiler::rule_map_t ada::compiler::collapse_rules() const
{
	rule_map_t rmap;

	for(const auto* rule_l = prolog.rule_list; rule_l; rule_l = rule_l->next)
	{
		if(const auto* rule = rule_l->rule)
		{
			std::string s = rule_s(*rule);
			size_t size = s.size();
			rmap[{rule->id, size}].emplace_back(std::move(s));
		}
	}

	return rmap;
}

std::string ada::compiler::rule_s(const ast_rule& rule)
{
	std::string s;

	for(const auto* seq = rule.character_list; seq; seq = seq->next)
	{
		s.push_back(seq->c);
	}

	return s;
}

void ada::compiler::print(const rule_map_t& rmap, FILE* file)
{
	for(const auto& [rule, S]: rmap)
	{
		for(std::string_view str: S)
		{
			fprintf(file, "%s(", rule.first.c_str());

			for(size_t i = 0; i < str.size(); i++)
			{
				fprintf(file, "%s%c", i != 0 ? ", " : "", str[i]);
			}
			fprintf(file, ")\n");
		}
	}
}

ada::compiler::compiler(FILE* outfile, const ast_prolog& prolog):
	outfile(outfile),
	prolog(prolog)
{}

void ada::compiler::compile_heuristic()
{
	const rule_map_t rmap = collapse_rules();

	print(rmap);

	// TODO write tries
}

void ada::compiler::compile_optimal()
{
	const rule_map_t rmap = collapse_rules();

	print(rmap);

	// TODO write tries
}
