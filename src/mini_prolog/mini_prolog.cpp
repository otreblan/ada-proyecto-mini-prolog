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

#include <cstdio>
#include <cstdlib>
#include <getopt.h>

#include "compiler.hpp"
#include "executor.hpp"
#include "mini_prolog.hpp"
#include "utils.h"

void ada::mini_prolog::usage(int exit_code)
{
	fprintf(stderr, "%s",
		"Usage: mini-prolog (-H|-O|-e) [-oFILE] FILE\n"
		"\t-h, --help        Show this help\n"
		"\t-H, --heuristic   Compile with heuristic.\n"
		"\t-O, --optim       Compile optimaly.\n"
		"\t-e, --execute     Execute queries.\n"
		"\t-o, --output=FILE Place the output in FILE.\n"
	);
	exit(exit_code);
}

ada::mini_prolog::mini_prolog(int argc, char* argv[])
{
	if(argc < 2)
		usage(EXIT_FAILURE);

	int c;
	static const char shortopts[] = "hHOeo:";
	static const option options[] =
	{
		{"help",      no_argument,       nullptr, 'h'},
		{"heuristic", no_argument,       nullptr, 'H'},
		{"optim",     no_argument,       nullptr, 'O'},
		{"execute",   no_argument,       nullptr, 'e'},
		{"output",    required_argument, nullptr, 'o'},
	};

	// Defaults
	action      = action_type::none;
	output_path = "a.out";

	while((c = getopt_long(argc, argv, shortopts, options, nullptr)) != -1)
	{
		switch(c)
		{
			case 'h':
				usage(EXIT_SUCCESS);
				break;

			case 'H':
				action = action_type::heuristic;
				break;

			case 'O':
				action = action_type::optim;
				break;

			case 'e':
				action = action_type::execute;
				break;

			case 'o':
				output_path = optarg;
				break;

			default:
				exit(EXIT_FAILURE);
		}
	}

	// Positional arguments
	for(int i = optind; i < argc; i++)
	{
		input_path = argv[i];
	}
}

int ada::mini_prolog::run()
{
	if(action == action_type::none)
	{
		fprintf(stderr, "%s\n", "Missing action");
		return EXIT_FAILURE;
	}

	FILE* input = fopen(input_path.c_str(), "r");
	if(!input)
	{
		perror(input_path.c_str());
		return EXIT_FAILURE;
	}

	ast_prolog* prolog = parse_file(input);
	fclose(input);

	if(!prolog)
		return EXIT_FAILURE;

	switch(action)
	{
		case action_type::execute:
			executor().execute(*prolog);
			break;

		case action_type::heuristic:
		case action_type::optim:
		{
			if(FILE* output = fopen(output_path.c_str(), "w"))
			{
				compiler c(output);

				switch(action)
				{
					case action_type::heuristic:
						c.compile_heuristic(*prolog);
						break;

					case action_type::optim:
						c.compile_optimal(*prolog);
						break;

					default:
						break;
				}

				break;
			}

			perror(output_path.c_str());
			break;
		}

		default:
			break;
	}

	ast_prolog_free(prolog);
	return EXIT_SUCCESS;
}
