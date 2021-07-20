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

ada::compiler::compiler(FILE* outfile):
	outfile(outfile)
{}

void ada::compiler::compile_heuristic(const ast_prolog& prolog)
{
	for(const auto* rule = prolog.rule_list; rule; rule = rule->next)
	{
		// TODO
		printf("%s(...)\n", rule->rule->id);
	}

	// TODO write tries
}

void ada::compiler::compile_optimal(const ast_prolog& prolog)
{
	for(const auto* rule = prolog.rule_list; rule; rule = rule->next)
	{
		// TODO
		printf("%s(...)\n", rule->rule->id);
	}

	// TODO write tries
}
