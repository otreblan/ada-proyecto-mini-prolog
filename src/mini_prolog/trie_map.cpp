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

#include <rapidjson/error/en.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/reader.h>
#include <rapidjson/writer.h>

#include "trie_map.hpp"

void ada::trie_map::dump(FILE* file) const
{
	using namespace rapidjson;

	char            buffer[PIPE_BUF];
	FileWriteStream fws(file, buffer, sizeof(buffer));
	Writer          writer(fws);

	writer.StartObject();

	writer.Key("rules");
	writer.StartArray();
	for(const auto& [key, value]: tm)
	{
		assert(key.second == value.m);

		writer.StartObject();

		writer.Key("name");
		writer.String(key.first);

		writer.Key("length");
		writer.Uint64(key.second);

		writer.Key("sigma");
		writer.String(value.sigma_str());

		writer.Key("matrix");
		writer.StartArray();
		for(ssize_t i: value.matrix)
		{
			writer.Int64(i);
		}
		writer.EndArray();

		writer.EndObject();
	}
	writer.EndArray();

	writer.EndObject();
}

bool ada::trie_map::load(FILE* file)
{
	using namespace rapidjson;

	char           buffer[PIPE_BUF];
	json_handler   handler(*this);
	Reader         reader;
	FileReadStream frs(file, buffer, sizeof(buffer));

	if(!reader.Parse<ParseFlag::kParseNumbersAsStringsFlag>(frs, handler))
	{
		ParseErrorCode e = reader.GetParseErrorCode();
		fprintf(stderr, "%s\n", GetParseError_En(e));
		return false;
	}

	return true;
}

void ada::trie_map::add_trie(
	std::string_view                rule,
	size_t                          length,
	const std::vector<std::string>& S,
	const std::vector<size_t>&      p
)
{
	tm.emplace(std::make_pair(std::make_pair(rule, length), trie(S, p)));
}

bool ada::trie_map::json_handler::StartObject()
{
	assert(!context_stack.empty());

	auto& top = context_stack.top();

	if(!top.object)
		return false;

	top.s = state::BEFORE_KEY;

	return true;
}

bool ada::trie_map::json_handler::EndObject(rapidjson::SizeType)
{
	assert(!context_stack.empty());

	context_stack.pop();

	return true;
}

bool ada::trie_map::json_handler::StartArray()
{
	// TODO
	return true;
}

bool ada::trie_map::json_handler::EndArray(rapidjson::SizeType)
{
	// TODO
	return true;
}

bool ada::trie_map::json_handler::Key(const char* str, rapidjson::SizeType, bool)
{
	// TODO
	return true;
}

bool ada::trie_map::json_handler::String(const char* str, rapidjson::SizeType, bool)
{
	// TODO
	return true;
}

bool ada::trie_map::json_handler::Uint64(uint64_t n)
{
	// TODO
	return true;
}

bool ada::trie_map::json_handler::Default()
{
	return false;
}
