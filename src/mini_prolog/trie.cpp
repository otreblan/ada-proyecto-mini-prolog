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

#include <iostream>

#include "trie.hpp"

static size_t m_init(const std::vector<std::string>& S);
static std::set<char> sigma_init(const std::vector<std::string>& S);
static std::unordered_map<char, size_t> sigma_order_init(const std::set<char>& sigma);

static size_t m_init(const std::vector<std::string>& S)
{
	return S.empty() ? 0 : S.front().size();
}

static std::set<char> sigma_init(const std::vector<std::string>& S)
{
	std::set<char> sigma;

	for(std::string_view str: S)
		sigma.insert(str.begin(), str.end());

	return sigma;
}

static std::unordered_map<char, size_t> sigma_order_init(const std::set<char>& sigma)
{
	std::unordered_map<char, size_t> sigma_order;
	size_t order = 0;

	for(char c: sigma)
		sigma_order[c] = order++;

	return sigma_order;
}

ada::trie::trie(
	const std::vector<std::string>& S,
	const std::vector<size_t>&      p
	):
	m(m_init(S)),
	nodes_n(1), // Root
	sigma(sigma_init(S)),
	sigma_order(sigma_order_init(sigma)),
	matrix(sigma_order.size()*m*(1+S.size()), -1),
	p(p)
{
	for(std::string_view str: S)
	{
		ssize_t node_i = 0;

		for(size_t p_i : p)
		{
			char c = str.at(p_i);
			node_i = matrix_index(node_i == 0 ? 0 : matrix.at(node_i), c);

			if(matrix.at(node_i) == -1)
				matrix.at(node_i) = nodes_n++;
		}
	}
}

ssize_t ada::trie::matrix_index(ssize_t node, char c) const
{
	if(node < 0 || sigma_order.find(c) == sigma_order.end())
		return -1;

	return node*sigma_order.size()+sigma_order.at(c);
}

std::string ada::trie::sigma_str() const
{
	std::string s;

	for(char c: sigma)
		s.push_back(c);

	return s;
}

void ada::trie::print_edges(std::ostream& os, size_t node) const
{
	for(char c: sigma)
	{
		size_t i = matrix_index(node, c);

		if(matrix.at(i) != -1)
		{
			os
				<< '\t'
				<< node
				<< " -> "
				<< matrix.at(i)
				<< " [label=\""
				<< c
				<< "\"];\n"
			;
			print_edges(os, matrix.at(i));
		}
	}
}

std::ostream& ada::operator<<(std::ostream& os, const trie& t)
{
	os <<
		"digraph D {\n"
		"\tforcelabels=true;\n"
		"\tlabelloc=\"t\";\n"
		"\tlabeljust=\"l\";\n"
		"\tlabel=\"# aristas: " << t.nodes_n-1 << "\";\n"
	;

	os << "\n\t//Nodes\n";
	for(size_t n = 0; n < t.nodes_n; n++)
	{
		os << '\t' << n << " [label=\"\"];\n";
	}

	os << "\n\t//Edges\n";
	t.print_edges(os, 0);

	os << "}\n";
	return os;
}
