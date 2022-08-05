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


#include "clique_gen.h"
#include <algorithm>
#include <fstream>

std::vector<size_t> intersection(std::vector<size_t>& a, std::vector<size_t>& b);

void sort_all_neighbors(std::vector<Word>& words) {
	for (auto it = words.begin(); it!= words.end();it++)
	{
		std::sort((*it).neighbors.begin(), (*it).neighbors.end());
	}
}

std::vector<std::array<size_t, 5>> find_cliques(std::vector<Word>& words)
{
	std::vector<std::array<size_t, 5>> cliques;

	sort_all_neighbors(words);

	for (size_t i = 0; i < words.size(); i++) {


		for (auto j : words[i].neighbors)
		{
			if (j < i)
			{
				continue;
			}

			std::vector<size_t> Nij = intersection(words[i].neighbors, words[j].neighbors);

			if (Nij.size() < 3)
			{
				continue;
			}

			for (auto k : Nij)
			{
				if (k < j)
				{
					continue;
				}

				std::vector<size_t> Nijk = intersection(Nij, words[k].neighbors);

				if (Nij.size() < 2)
				{
					continue;
				}

				for (auto l : Nijk)
				{
					if (l < k)
					{
						continue;
					}

					std::vector<size_t> Nijkl = intersection(Nijk, words[l].neighbors);

					for (auto r : Nijkl)
					{
						if (r < l) {
							continue;
						}
						std::array<size_t, 5> arr = { i,j,k,l,r };
						cliques.push_back(arr);

					}

				}

			}

		}
	}
	return cliques;
}

namespace my_code {
	template<class InputIt1, class InputIt2, class OutputIt>
	inline OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2,
		OutputIt d_first)
	{
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				++first1;
			}
			else {
				if (!(*first2 < *first1)) {
					*d_first++ = *first1++; // *first1 and *first2 are equivalent.
				}
				++first2;
			}
		}
		return d_first;
	}
}

//Assumes a & b are sorted, returns a sorted vector
std::vector<size_t> intersection(std::vector<size_t>& a, std::vector<size_t>& b) {

	std::vector<size_t> ret;

	my_code::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));

	//The result of std::set_intersection seems to be sorted, so I can skip the second sorting step
	//std::sort(ret.begin(), ret.end());

	return ret;

}

void save_cliques(std::vector<std::array<size_t, 5>>& cliques, std::vector<Word>& words, std::string file)
{
	std::ofstream outfile(file);

	for (auto it = cliques.begin(); it != cliques.end(); it++)
	{
		outfile << words[(*it)[0]] << '\t' << words[(*it)[1]] << '\t' << words[(*it)[2]] << '\t' << words[(*it)[3]] << '\t' << words[(*it)[4]] << '\n';
	}

	outfile.close();
}
