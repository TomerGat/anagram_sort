#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

static std::vector<std::string> empty = {}; //represents an empty vector of strings

//prints a vector of strings
void print_vec(std::vector<std::string>& vec) { 
	std::cout << "{ ";
	for (int i = 0; i < size(vec); i++) {
		if (i == size(vec) - 1) {
			std::cout << vec[i] + " ";
		}
		else {
			std::cout << vec[i] + ", ";
		}
	}
	std::cout << "} " << std::endl;
}

//prints a vector of vectors of strings
void print_thing(std::vector<std::vector<std::string>>& thing) {
	for (std::vector<std::string> inner : thing) {
		std::cout << "{ ";
		for (int i = 0; i < size(inner); i++) {
			if (i == size(inner) - 1) {
				std::cout << inner[i] + " ";
			}
			else {
				std::cout << inner[i] + ", ";
			}
		}
		std::cout << "} ";
	}
	std::cout << std::endl;
}

//creates a map containing the count of each letter in a string
std::map<char, int> create_map(const std::string& word) {
	std::map<char, int> wordmap = {};
	for (char ch : word) {
		wordmap[ch] = std::count(word.begin(), word.end(), ch);
	}
	return wordmap;
}

//removes empty vectors of strings from a vector of vectors of strings
std::vector<std::vector<std::string>> remove_empty(std::vector<std::vector<std::string>>& groups) {
	std::vector<std::vector<std::string>> newvector = {};
	for (std::vector<std::string> group : groups) {
		if (group == empty) {
			break;
		}
		newvector.push_back(group);
	}
	return newvector;
}

//sort a vector of strings into groups of anagrams
std::vector<std::vector<std::string>> find_anagrams(std::vector<std::string>& words) {
	bool empties = false;
	//create a vector containing a map for each word
	std::vector<std::map<char, int>> wordmaps = {};
	for (std::string word : words) {
		wordmaps.push_back(create_map(word));
	}
	std::vector<std::vector<std::string>> anagram_groups = {};
	for (int i = 0; i < size(words); i++) {
		bool inList = false;
		//check if word appears in an existing group
		for (std::vector<std::string> group : anagram_groups) {
			if (std::count(group.begin(), group.end(), words[i])) {
				inList = true;
				break;
			}
		}
		//if word isn't in an existing group
		if (!inList) {
			//create a new group containing only the current word
			anagram_groups.push_back({ words[i] });
			//iterating on the list of words and checking if other words in the list are anagrams of the current word
			for (int j = i; j < size(words); j++) {
				//if letters in both words are the same and word
				if ((wordmaps[i] == wordmaps[j]) && (!std::count(anagram_groups[i].begin(), anagram_groups[i].end(), words[j])) && (i != j)) {
					anagram_groups[i].push_back(words[j]);
				}
			}
		}
		else {
			//if word already exists, push back an empty group to preserve correct iteration
			anagram_groups.push_back({});
			empties = true; //setting empties to true to confirm existence of empty groups
		}
	}
	if (empties) {
		//remove empty groups
		remove(anagram_groups.begin(), anagram_groups.end(), empty);
		anagram_groups = remove_empty(anagram_groups);
	}
	return anagram_groups;
}

//main - driver function to check anagram function
int main() {
	std::vector<std::string> input = { "hello", "twist", "read", "read", "dread", "salted", "brush", "shrub", "dictionary", "indicatory", "deltas", "slated", "salted", "dear"};
	std::vector<std::vector<std::string>> groups = find_anagrams(input);
	std::cout << "List of words: " << std::endl;
	print_vec(input);
	std::cout << std::endl;
	std::cout << "Groups of anagrams in list of words: " << std::endl;
	print_thing(groups);
	return 0;
}

/*
Output from main (driver program for given list of words:

List of words:
{ hello, twist, read, read, dread, salted, brush, shrub, dictionary, indicatory, deltas, slated, salted, dear }

Groups of anagrams in list of words:
{ hello } { twist } { read, dear } { dread } { salted, deltas, slated } { brush, shrub } { dictionary, indicatory }

*/
