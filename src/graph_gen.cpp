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


#include "graph_gen.h"

#include <fstream>
#include <string.h>
#include <algorithm>
#include <array>

bool has_exclusive_chars(std::string a);

std::vector<Word> load_words(std::string& file)
{
	std::vector<Word> words;

	std::ifstream infile;

	infile.open(file);

	if (infile.fail())
	{
		std::cerr << "Failed to open file" << std::endl;
		exit(-1);
	}

	for (std::string line; getline(infile, line);) {
		if (line.size() == 5)
		{
			if (has_exclusive_chars(line)) {
				Word w;

				for (size_t i = 0; i < 5; i++)
				{
					w.str[i] = line[i];
				}
				
				words.push_back(w);
			}
		}
	}

	infile.close();
	words.shrink_to_fit();

	return words;
}

//4828993[us]
bool has_exclusive_chars(Word& a_, Word& b_) {
	const char* a = &a_.str[0];
	const char* b = &b_.str[0];

	const size_t cachea = 5;
	const size_t cacheb = 5;

	for (size_t i = 0; i < cachea; i++) {
		for (size_t x = 0; x < cacheb; x++) {
			if (a[i] == b[x])
			{
				return false;
			}
		}
	}

	return true;

}


bool has_exclusive_chars(std::string a) {
	std::sort(a.begin(), a.end());
	return std::unique(a.begin(), a.end()) == a.end();
}

void build_neighborhoods(std::vector<Word>& words)
{
	auto cache_size = words.size();
	for (size_t i = 0; i < cache_size; i++)
	{
		words[i].neighbors.reserve(2000);
		for (size_t j = 0; j < cache_size; j++) {
			if (has_exclusive_chars(words[i], words[j]))
			{
				words[i].neighbors.push_back(j);
			}
		}
	}
}

