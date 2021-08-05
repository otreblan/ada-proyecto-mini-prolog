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

#include <numeric>
#include <string_view>

#include "compiler.hpp"
#include "trie_map.hpp"

ada::compiler::rule_map_t ada::compiler::collapse_rules() const
{
	rule_map_t rmap;

	for(const auto* rule_l = prolog.rule_list; rule_l; rule_l = rule_l->next)
	{
		if(const auto* rule = rule_l->rule)
		{
			std::string s = rule->str;
			size_t size = s.size();
			rmap[{rule->id, size}].emplace_back(std::move(s));
		}
	}

	return rmap;
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

ada::compiler::compiler(std::ostream& os, const ast_prolog& prolog):
	os(os),
	prolog(prolog)
{}

void ada::compiler::compile(
	std::function<std::vector<size_t>(const std::vector<std::string>&)> f)
{
	const rule_map_t rmap = collapse_rules();
	trie_map tm;

	//print(rmap);
	for(const auto& [rule, S]: rmap)
		tm.add_trie(rule.first, S, f(S));

	tm.dump(os);
}

void ada::compiler::compile_heuristic()
{
	compile([](const std::vector<std::string>& S) -> std::vector<size_t>
	{
		if(S.empty())
			return {};

		auto h = [&](size_t i)
		{
			std::set<char> sigma;
			for(const auto& s: S)
				sigma.insert(s.at(i));

			return sigma.size();
		};

		size_t m = S.front().size();

		std::vector<size_t> p(m);
		std::iota(p.begin(), p.end(), 0);

		std::sort(p.begin(), p.end(),
			[&](size_t l, size_t r)
			{
				return h(l) < h(r);
			}
		);

		return p;
	});
}

void ada::compiler::compile_optimal()
{
	compile([](const std::vector<std::string>& S) -> std::vector<size_t>
	{
		//TODO
		return {};
	});
}
