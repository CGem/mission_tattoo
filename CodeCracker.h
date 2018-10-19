#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class CodeCracker
{
public:
	//ctor
	CodeCracker();

	//default dtor
	~CodeCracker() {};

	//Converts morse code to letters
	void transliterateMorse(int code[], int length);

	//Calls a function to find the possible combinations of letters
	void findLetterCombos();
	
private:
	//Recursive function to generate every possible letter combination
	void addLetter(std::map<int, char>& temp, int firstIndex, int secondIndex, int buffer);

	//The alphabet in morse code
	std::map <char, std::vector<int>> m_morseList;

	//List of all the possible letters at each index of the message array
	std::vector <std::vector<char>> m_letters;

	//The message to be decrypted
	std::vector <int> m_message;

	//Stores the number of possible solutions
	int m_count = 0;

	//File in which to print solutions
	std::ofstream m_stringPossibilities;

};