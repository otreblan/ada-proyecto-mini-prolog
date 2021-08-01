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

#include <climits>

#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

#include "trie_map.hpp"

void ada::trie_map::dump(FILE* file) const
{
	char buffer[PIPE_BUF];
	rapidjson::FileWriteStream fws(file, buffer, sizeof(buffer));
	rapidjson::Writer writer(fws);

	writer.StartObject();

	writer.Key("rules");
	writer.StartArray();
	for(const auto& [key, value]: tm)
	{
		writer.StartObject();

		writer.Key("name");
		writer.String(key.first);

		writer.Key("length");
		writer.Uint64(key.second);

		writer.Key("sigma");
		writer.String("TODO");

		writer.Key("matrix");
		writer.StartArray();
		// TODO
		writer.EndArray();

		writer.EndObject();
	}
	writer.EndArray();

	writer.EndObject();
}

void ada::trie_map::load(FILE* file)
{
	// TODO
}
