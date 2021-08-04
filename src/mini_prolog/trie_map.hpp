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
#include <stack>
#include <string>
#include <string_view>

#include <rapidjson/reader.h>

#include "trie.hpp"

namespace ada
{

class trie_map
{
private:
	using key_t = std::pair<std::string, size_t>;

	/// The map itself.
	std::map<key_t, trie> tm;

	class json_handler:
		public rapidjson::BaseReaderHandler<rapidjson::UTF8<>, json_handler>
	{
	private:
		enum class state
		{
			AFTER_KEY,
			BEFORE_KEY,
			IN_ARRAY,
		};

		std::stack<std::pair<state, std::string>> context;

		trie_map& tm;


	public:
		json_handler(trie_map& tm):
			tm(tm)
		{};
		// TODO
	};
public:
	/// Write the tries as json.
	void dump(FILE* file) const;

	/// Load tries from json.
	bool load(FILE* file);

	/// Add a new trie for a rule and length pair.
	void add_trie(
		std::string_view                rule,
		size_t                          length,
		const std::vector<std::string>& S,
		const std::vector<size_t>&      p
	);
};

};
