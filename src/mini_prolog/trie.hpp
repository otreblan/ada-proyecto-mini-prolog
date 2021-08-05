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

	/// The number of nodes in the trie.
	size_t nodes_n;

	/// Alphabet.
	std::set<char> sigma;

	/// A mapping between the alphabet and the index of each character.
	std::unordered_map<char, size_t> sigma_order;

	/// The trie itself.
	std::vector<ssize_t> matrix;
public:
	trie(const std::vector<std::string>& S, const std::vector<size_t>& p);
	trie(){};

	/// Returns the index in the matrix that has node as row and c as column.
	/// If it doesn't exist, -1 is returned.
	ssize_t matrix_index(ssize_t node, char c) const;

	/// Get the alphabet as a string.
	std::string sigma_str() const;

	friend std::ostream& operator<<(std::ostream& os, const trie& t);
	void print_edges(std::ostream& os, size_t node) const;

	friend class trie_map;
	friend class executor;

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(m, nodes_n, sigma, sigma_order, matrix);
	}
};

std::ostream& operator<<(std::ostream& os, const trie& t);

};
