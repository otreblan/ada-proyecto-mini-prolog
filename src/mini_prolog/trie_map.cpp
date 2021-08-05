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

#include <cassert>
#include <climits>

#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>

#include <cereal/archives/json.hpp>

#include "trie_map.hpp"

void ada::trie_map::add_trie(
	std::string_view                rule,
	const std::vector<std::string>& S,
	const std::vector<size_t>&      p
)
{
	tm.emplace(std::make_pair(rule, trie(S, p)));
}

void ada::trie_map::dump(std::ostream& os) const
{
	cereal::JSONOutputArchive oarchive(os);

	oarchive(tm);
}

bool ada::trie_map::load(std::istream& is)
{
	cereal::JSONInputArchive iarchive(is);

	iarchive(tm);

	return true;
}
