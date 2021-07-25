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
#include <map>
#include <string>

#include "utils.h"

namespace ada
{

class compiler
{
private:
	FILE* outfile;
	const ast_prolog& prolog;

	/// Gather S sets for each pair of rules and it's sequence length.
	std::multimap<std::pair<std::string, size_t>, std::string> collapse_rules() const;

	/// Make a string from a rule's character_list.
	static std::string rule_s(const ast_rule& rule);

public:
	compiler(FILE* outfile, const ast_prolog& prolog);

	void compile_heuristic();
	void compile_optimal();
};

};
