#include "CodeCracker.h"

CodeCracker::CodeCracker()
{
	m_morseList['a'] = { 0,1 };
	m_morseList['b'] = { 1,0,0,0 };
	m_morseList['c'] = { 1,0,1,0 };
	m_morseList['d'] = { 1,0,0 };
	m_morseList['e'] = { 0 };
	m_morseList['f'] = { 0,0,1,0 };
	m_morseList['g'] = { 1,1,0 };
	m_morseList['h'] = { 0,0,0,0 };
	m_morseList['i'] = { 0,0 };
	m_morseList['j'] = { 0,1,1,1 };
	m_morseList['k'] = { 1,0,1 };
	m_morseList['l'] = { 0,1,0,0 };
	m_morseList['m'] = { 1,1 };
	m_morseList['n'] = { 1,0 };
	m_morseList['o'] = { 1,1,1 };
	m_morseList['p'] = { 0,1,1,0 };
	m_morseList['q'] = { 1,1,0,1 };
	m_morseList['r'] = { 0,1,0 };
	m_morseList['s'] = { 0,0,0 };
	m_morseList['t'] = { 1 };
	m_morseList['u'] = { 0,0,1 };
	m_morseList['v'] = { 0,0,0,1 };
	m_morseList['w'] = { 0,1,1 };
	m_morseList['x'] = { 1,0,0,1 };
	m_morseList['y'] = { 1,0,1,1 };
	m_morseList['z'] = { 1,1,0,0 };

	m_stringPossibilities.open("Possible_letter_combinations.txt");
}

void CodeCracker::transliterateMorse(int code[], int length)
{
	/*
	//The start point of the message is unknown, so in order to make sure the solution doesn't start in the 
	//middle of a word a buffer of the last three characters is added onto the beginning of the message
	*/
	length += 3;

	m_message.resize(length);

	m_message[0] = code[length - 6];
	m_message[1] = code[length - 5];
	m_message[2] = code[length - 4];

	for (int i = 0; i < (length-3); i++)
	{
		m_message[i+3] = code[i];
	}

	//Print out the original message to the console
	std::cout << "message: ";
	for (int i = 0; i < length; i++)
	{
		std::cout << m_message[i]<<", ";
	}
	std::cout << '\n';

	m_letters.resize(length);

	std::map <char, std::vector<int>>::iterator it = m_morseList.begin();

	bool match = false;

	//Check the message against the list of morse code letters
	for (int i = 0; i < length; i++)
	{
		for (std::pair<char, std::vector<int>> element : m_morseList)
		{
			int letterLength = element.second.size();

			match = false;

			for (int k = 0; k < letterLength; k++)
			{
				if (i + (letterLength - 1) < length)
				{
					if (element.second[k] == m_message[i + k])
					{
						match = true;
					}
					else
					{
						match = false;
						break;
					}
				}
			}

			//When the letters match, record the letter at the index it was located in the message
			if (match)
			{
				m_letters[i].push_back(element.first);
			}
		}
	}

	//Print the results to the console
	for (int i = 0; i < length; i++)
	{
		std::cout << "Letters at index " << i << ": ";
		for (size_t j = 0; j < m_letters[i].size(); j++)
		{
			std::cout << m_letters[i][j] << ", ";
		}
		std::cout << '\n';
	}
}

void CodeCracker::addLetter(std::map <int, char>& temp, int firstIndex, int secondIndex, int buffer)
{
	//Variable to track the number of letter combinations found
	static int incrementIndex = 0;

	//Iterator to mark the point at which the current letter combination deviates from the previous one
	std::map<int, char>::iterator overwritePoint;

	unsigned int morseLength = m_morseList[m_letters[firstIndex][secondIndex]].size();

	//The index of the 'm.letters' vector at which the next letter in the current letter combination begins
	unsigned int newIndex = morseLength + firstIndex;

	//Check the new index is in range
	if (newIndex <= ( m_message.size()- buffer))
	{
		//Store the first letter alongside it's index in a temporary map
		if (temp.empty())
		{
			temp.insert(std::make_pair(firstIndex, m_letters[firstIndex][secondIndex]));
		}

		//Overwrite the current string of letters with the new one
		else
		{
			overwritePoint = temp.lower_bound(firstIndex);
			temp.erase(overwritePoint, temp.end());
			temp.insert(std::make_pair(firstIndex, m_letters[firstIndex][secondIndex]));
		}

		//Check the end of the message hasn't been reached
		if (newIndex < (m_message.size() - buffer))
		{
			//Enter the function again for each letter at the current index in 'm_letters'
			for (size_t i = 0; i < m_letters[newIndex].size(); i++)
			{
				addLetter(temp, newIndex, i, buffer);
			}

		}
		else
		{
			//Print the string of letters to a file
			if (m_stringPossibilities.is_open())
			{			
				for (std::pair<int, char> element : temp)
				{
					m_stringPossibilities << element.second;
				}
				m_stringPossibilities << '\n';
			}
			incrementIndex++;
		}
	}
	m_count = incrementIndex;
}

void CodeCracker::findLetterCombos()
{
	//Create a map to store each letter combination
	std::map <int, char> temp;

	//Find all the possible combinations starting from each of the first four characters in the message
	for (int i = 0; i < 4; i++)
	{	
		for (size_t j = 0; j < m_letters[i].size(); j++)
		{
			addLetter(temp, i, j, (3-i));
			temp.clear();
		}
	}

	//Print the total number of letter combinations to the file and then close the file
	m_stringPossibilities << "Number of combinations: " << m_count << '\n';
	m_stringPossibilities.close();
}



	
