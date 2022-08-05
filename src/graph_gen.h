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


#pragma once
#include "Word.h"
#include <vector>
#include <string>

/// <summary>
/// Builds an array of Words from a file
/// </summary>
/// <param name="file">The file to load words from</param>
/// <returns>An array of Words</returns>
std::vector<Word> load_words(std::string& file);

/// <summary>
///Adds neighborhood data to the array of words
///</summary>
/// 
/// <param name="words"> 
///The words to group 
/// </param>
void build_neighborhoods(std::vector<Word>& words);