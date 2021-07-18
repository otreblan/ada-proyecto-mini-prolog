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

#include <string>

namespace ada
{

class mini_prolog
{
private:
	enum class action_type
	{
		none,
		heuristic,
		optim,
		execute,
	};

	/// The action to do.
	action_type action;

	/// The path to the input of this program.
	std::string input_path;

	/// The path to the output of this program.
	std::string output_path;


	[[noreturn]]
	void usage(int exit_code);

public:
	mini_prolog(int argc, char* argv[]);

	/// Compile or execute and return the exit code.
	int run();
};

};
