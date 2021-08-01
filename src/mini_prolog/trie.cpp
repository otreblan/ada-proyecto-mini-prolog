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

#include "trie.hpp"

ada::trie::trie(
	const std::vector<std::string>& S,
	const std::vector<size_t>&      p
	)
{
	// m
	m = S.empty() ? 0 : S.front().size();

	// sigma
	for(std::string_view str: S)
		sigma.insert(str.begin(), str.end());

	// sigma_order
	size_t order = 0;
	for(char c: sigma)
		sigma_order[c] = order++;

	// matrix
	// TODO
}

std::string ada::trie::sigma_str() const
{
	std::string s;

	for(char c: sigma)
		s.push_back(c);

	return s;
}
