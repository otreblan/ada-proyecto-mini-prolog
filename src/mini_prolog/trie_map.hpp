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

#include <iostream>
#include <map>

#include "trie.hpp"

namespace ada
{

class trie_map
{
private:
	using key_t = std::pair<std::string, size_t>;

	/// The map itself.
	std::map<key_t, trie> tm;

public:
	/// Write the tries as json.
	void dump(std::ostream& os) const;

	/// Load tries from json.
	bool load(std::istream& is);

	/// Add a new trie for a rule and length pair.
	void add_trie(
		std::string_view                rule,
		size_t                          length,
		const std::vector<std::string>& S,
		const std::vector<size_t>&      p
	);
};

};
