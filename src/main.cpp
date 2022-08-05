/*
* Copyright(C) 2022 - William Mosier

* This program is free software : you can redistribute it and /or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.If not, see < http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

#include <stdlib.h>

#include "Word.h"
#include "clique_gen.h"
#include "graph_gen.h"

typedef struct {
	bool help;
	std::string file;
	std::string output_file;
	
	bool save_graph;
	std::string graph_file;


}Options;

Options process_options(std::vector<std::string>& args) {
	Options opt = {
		/*.help = */ false,
		/*.file = */"words_alpha.txt",
		/*.output_file = */ "cliques.txt",
		/*.save_graph = */false,
		/*.graph_file = */"word_graph.txt"
		
	};

	for (auto i = args.begin(); i != args.end(); ++i)
	{
		if (*i == "-h" || *i == "--help") {
			opt.help = true;
		}

		if (*i == "-f" || *i == "--file") {
			i++;
			
			if (i == args.end()) {
				return opt;
			}
			opt.file = *i;
		}
		
		if (*i == "-o" || *i == "--out") {
			i++;

			if (i == args.end()) {
				return opt;
			}
			opt.file = *i;
		}

		if (*i == "-g" || *i == "--graph") {
			i++;

			if (i == args.end()) {
				return opt;
			}
			opt.save_graph = true;
		}

		if (*i == "-q" || *i == "--save_graphf") {
			i++;

			if (i == args.end()) {
				return opt;
			}
			opt.save_graph = true;
			opt.graph_file = *i;
		}
	}
	
	return opt;
}

int main(int argc, char** argv) {
	using namespace std;
	vector<string> args(argv + 1, argv + argc);
	Options ops = process_options(args);

	if (ops.help)
	{
		std::cout << "Syntax: " << argv[0] << " [-h,--help 'help'] [-f,--file 'file of valid words'] [-o, --out 'specifies file to save results to'] [-g --graph 'saves intermediate graph'] [-q --save_graphf 'specifies the file to save the intermediate graph to']" << std::endl;
		return 0;
	}


	std::cout << "--- reading words file ---" << '\n';

	vector<Word> words = load_words(ops.file);

	std::cout << "--- building neighborhoods--- " << '\n';

	build_neighborhoods(words);

	std::cout << "--- start clique finding(THIS WILL TAKE A WHILE!)--- " << '\n';

	std::vector<std::array<size_t, 5>> cliques = find_cliques(words);

	std::cout << "--- Saving Cliques to file: " << ops.output_file << " ---\n";

	save_cliques(cliques, words, ops.output_file);

	std::cout << "--- Cliques Saved ---" << std::endl;

	return 0;
}
