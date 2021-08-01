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

#include <cstdlib>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace ada
{

class trie
{
private:
	/// Size of the strings in S.
	size_t m;

	/// Alphabet.
	std::set<char> sigma;

	/// A mapping between the alphabet and the index of each character.
	std::unordered_map<char, size_t> sigma_order;

	/// The trie itself.
	std::vector<ssize_t> matrix;
public:
	trie(const std::vector<std::string>& S, const std::vector<size_t>& p);

	/// Get the alphabet as a string.
	std::string sigma_str() const;

	friend class trie_map;
};

};
