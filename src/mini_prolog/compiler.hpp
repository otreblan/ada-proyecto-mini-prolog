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

#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils.h"

namespace ada
{

class compiler
{
private:
	using rule_map_t = std::map<std::pair<std::string, size_t>, std::vector<std::string>>;

	std::ostream& os;
	const ast_prolog& prolog;

	/// Gather S sets for each pair of rules and it's sequence length.
	rule_map_t collapse_rules() const;

	/// Make a string from a rule's character_list.
	static std::string rule_s(const ast_rule& rule);

	/// Print the mmap from collapse_rules().
	static void print(const rule_map_t& rmap, FILE* file = stderr);

	/// Compile the tries with f() as the function that gives the order.
	void compile(std::function<std::vector<size_t>(const std::vector<std::string>&)> f);

public:
	compiler(std::ostream& os, const ast_prolog& prolog);

	void compile_heuristic();
	void compile_optimal();
};

};
