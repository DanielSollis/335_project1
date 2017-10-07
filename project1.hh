///////////////////////////////////////////////////////////////////////////////
// project1.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "windows.h"
// Convenient typedef for a vector of strings.
typedef std::vector<std::string> string_vector;

// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or false on I/O error.
bool load_words(string_vector& words, const std::string& path) {
	words.clear();

	std::ifstream text_input("../" + path); // IF RUNTIME ISSUE: TRY DELETING "../" ARGUMENT
	if (!text_input) {
		return false;
	}
	while (!text_input.eof()) {
		std::string word_input;
		getline(text_input, word_input);
		words.push_back(word_input);
	}
	text_input.close();
	words.pop_back();
	return true;
}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const std::string& string1, const std::string& string2) {
	if (string1 == string2 || string1.length() != string2.length()) {
		return false;
	}
	size_t beg = 0;
	size_t end = string1.length() - 1;
	for (beg, end; beg < string1.length(); end--, beg++) {
		if (string1.at(beg) != string2.at(end)) {
			return false;
		}
	}
	return true;
}

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const std::string& alleged_substring,
	const std::string& alleged_superstring) {
	if (alleged_superstring.find(alleged_substring) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
	std::string total_string = strings[0];
	char most_common = 'a';
	int most_common_length = 0;
	std::vector<char> seen_chars;

	for (size_t i = 1; i < strings.size(); i++) {
		total_string.append(strings[i]);
	}

	for (size_t i = 0; i < total_string.length(); i++) {
		char counting_char = total_string.at(i);
		if (std::find(seen_chars.begin(), seen_chars.end(), counting_char) == seen_chars.end()) {
			int char_length = 0;
			for (size_t j = 0; j < total_string.length(); j++) {
				if (total_string.at(j) == counting_char) {
					char_length++;
				}
			}
			seen_chars.push_back(counting_char);
			if (char_length > most_common_length) {
				most_common = counting_char;
				most_common_length = char_length;
			}
		}
	}
	return most_common;
}

// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
std::string longest_mirrored_string(const string_vector& strings) {
	std::string best = "";
	for (size_t i = 0; i < strings.size() - 1; i++) {
		for (size_t j = 0; j < strings.size() - 1; j++) {
			if (is_mirrored(strings[i], strings[j])) {
				if (strings[i].size() > best.length()) {
					best = strings[i];
				}
			}
		}
	}
	return best;
}

// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
	int longest = 0;
	string_vector trio;
	trio.push_back("");
	trio.push_back("");
	trio.push_back("");
	for (size_t i = 0; i < strings.size(); i++) {
		for (size_t j = 0; j < strings.size(); j++) {
			if (strings[j].size() <= strings[i].size() && strings[i] != strings[j]) {
				for (size_t k = 0; k < strings.size(); k++) {
					if (strings[k].size() <= strings[j].size() && strings[j] != strings[k]) {
						if (is_substring(strings[j], strings[i]) && is_substring(strings[k], strings[j])) {
							int trio_length = strings[i].length() + strings[j].length() + strings[k].length();
							if (trio_length > longest) {
								longest = trio_length;
								trio[0] = strings[i];
								trio[1] = strings[j];
								trio[2] = strings[k];
							}
						}
					}
				}
			}
		}
	}
	return trio;
}
