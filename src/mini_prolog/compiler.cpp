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

#include "compiler.hpp"

std::multimap<std::pair<std::string, size_t>, std::string> ada::compiler::collapse_rules() const
{
	std::multimap<std::pair<std::string, size_t>, std::string> mmap;

	for(const auto* rule_l = prolog.rule_list; rule_l; rule_l = rule_l->next)
	{
		if(const auto* rule = rule_l->rule)
		{
			std::string s = rule_s(*rule);
			mmap.emplace(std::make_pair(std::make_pair(rule->id, s.size()), s));
		}
	}

	return mmap;
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

ada::compiler::compiler(FILE* outfile, const ast_prolog& prolog):
	outfile(outfile),
	prolog(prolog)
{}

void ada::compiler::compile_heuristic()
{
	for(const auto* rule = prolog.rule_list; rule; rule = rule->next)
	{
		// TODO
		printf("%s(...)\n", rule->rule->id);
	}

	// TODO write tries
}

void ada::compiler::compile_optimal()
{
	for(const auto* rule = prolog.rule_list; rule; rule = rule->next)
	{
		// TODO
		printf("%s(...)\n", rule->rule->id);
	}

	// TODO write tries
}
