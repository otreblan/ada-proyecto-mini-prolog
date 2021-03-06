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
#include <string_view>

#include "trie_map.hpp"
#include "utils.h"

namespace ada
{

class executor
{
private:
	/// The queries
	const ast_prolog& prolog;

	/// The tries
	const trie_map& tm;

	std::vector<char> matches;

	void query(std::string_view rule, std::string_view str);

	bool traverse(const trie& t, std::string_view str, ssize_t node_i);

	bool has_char(const trie& t, ssize_t node_i);

	std::string reorder(const std::vector<size_t>& p, std::string_view str);

public:
	executor(const ast_prolog& prolog, const trie_map& tm);

	/// Executes the queries and prints the results in the file.
	void execute();
};

};
