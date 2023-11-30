#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Initializing string with special symbols and punctuation character
const string punctuation{"`~!@#$%^&*()_-+=[]{}\\|;:'\",.<>/?"};

enum menu
{
	start = 1,
	finish
};

enum subMenu
{
	fileInput = 1,
	userInput,
	back
};

// Reads all content from file. Returns content as string
string read_content_from_file(const string &filename)
{
	// Initializing input file stream
	ifstream is(filename);
	// Setting position to end of file
	is.seekg(0, ios::end);
	// Initializing size of file with 'tellg()' method
	// 'tellg()' returns position of the current char
	long int size{is.tellg()};
	// Initializing content of file with empty char ' '
	string content(size, ' ');
	// Setting position to begining of file
	is.seekg(0);
	// Reading all from input file stream and writing it into a 'content' string
	is.read(&content[0], size);

	// Return content from file
	return content;
}

// Removes all punctuation characters and special symbols except spaces
// Returns modified copy of original string
string remove_punctuation(const string &str)
{
	// Initializing copy of original string
	string str_copy{str};

	// Following 'for' loop removes all punctuation characters except spaces
	for (size_t punct_index = 0UL; punct_index < punctuation.length(); punct_index++)
	{
		for (size_t char_index = 0UL; char_index < str_copy.length(); char_index++)
		{
			// Using 'erase()' method for remove character
			if (punctuation[punct_index] == str_copy[char_index])
				str_copy.erase(char_index, 1UL);
		}
	}

	// Returning modified string without punctuation characters and special symbols
	return str_copy;
}

// Returns count of symbols as size_t in string
size_t count_of_symbols(const string &str)
{
	// Initializing counter for symbols
	// This is necessary so that such an extra character as '\n' does not get into the counter
	size_t counter{};

	// Common 'for' loop for count characters in string
	// Simply using the 'length()' method is not enough here, as mentioned earlier
	for (size_t char_index = 0UL; char_index < str.length(); char_index++)
	{
		// Increment if char is not a '\n' symbol
		if (str[char_index] != '\n')
			counter++;
	}

	// Returning count of symbols without '\n'
	return counter;
}

// Returns count of words as size_t in string
size_t count_of_words(const string &str)
{
	// Initializing counter to count words and temporaly variable
	// Temporaly variable using for transition between words
	size_t counter{}, temp{};

	/* How to avoid, for example, this case:
	We have string: "This is , , uncommon string !"
	Our counter returns 6 words, but exactly in this string 4 words
	To avoid this, we have to delete all punctuation and special symbols except spaces
	So, use 'remove_punctuation()' function */

	// Initializing copy of 'str' to avoid changes in original string
	string str_copy{remove_punctuation(str)};

	// Using 'for()' loop to iterate by characters in string
	for (size_t char_index = 0UL; char_index < str_copy.length(); char_index++)
	{
		// if symbol in string is space or symbol of transition on new line ('\n'), or tabulation symbol ('\t')
		// Zeroing out temporaly variable
		if (str_copy[char_index] == ' ' || str_copy[char_index] == '\n' || str_copy[char_index] == '\t')
			temp = 0;
		else if (temp == 0)
		{
			temp = 1;
			// Counting words
			counter++;
		}
	}

	// Return count of words
	return counter;
}

// Returns count of sentences in text as size_t
size_t count_of_sentences(const string &str)
{
	// Initializing counter for paragraphs
	size_t counter{};

	/* Now, we need to  count how many '\n' symbols we have in text
	So we'll count how many paragraphs we have in the text */

	// Removing all spaces using 'for' loop
	for (size_t char_index = 0UL; char_index < str.length(); char_index++)
	{
		// Check if symbol is character with 'isalpha()' function and the next symbol is point
		// To avoid this case: "String with . . . points."
		// There is 1 sentence, but if we will count just points, we will get 4 sentences, because this string contains 4 points
		if (isalpha(str[char_index]) && str[char_index + 1] == '.')
			counter++;
	}

	// Returning count of parahraphs
	return counter;
}

// Returns count of paragraphs in text as size_t
size_t count_of_paragraphs(const string &str)
{
	// Initializing counter for paragraphs
	size_t counter{};

	/* Now, we need to  count how many '\n' symbols we have in text
	So we'll count how many paragraphs we have in the text */

	// Removing all spaces using 'for' loop
	for (size_t char_index = 0UL; char_index < str.length(); char_index++)
	{
		if (str[char_index] == '\n')
			counter++;
	}

	// Returning count of parahraphs
	return counter;
}

// Returns string which contains:
// count of symbols, words, sentences and parahraphs in the text
string string_results(const string &text)
{
	return "Count of symbols in text: " + to_string(count_of_symbols(text)) + "\n" +
		   "Count of words in text: " + to_string(count_of_words(text)) + "\n" +
		   "Count of sentences in text: " + to_string(count_of_sentences(text)) + "\n" +
		   "Count of paragraphs: " + to_string(count_of_paragraphs(text)) + "\n";
}

// Returns true if file exists, returns false if there is no file with given name of file
bool is_file_exist(const string &filename)
{
	// Initializing input file stream
	ifstream ifs(filename);

	// Checking if file is exists
	if (ifs.good())
		return true;
	else
		return false;
}

// Saving string results (result of working 'string_results()' function) into a file
void save_str_to_file(const string &data)
{
	// Initializing string to store user's choice about saving the file
	string save{};
	cout << "Do you want to save results into a file? (y/N): ";

	// Using infinite loop for handling errors with incorrect input
	while (true)
	{
		cin >> save;
		if (save == "Y" || save == "y")
		{
			// Initializing string to store name of file, which will be contain 'data' parameter
			string filename{};

			cout << "Enter name of file: ";
			cin >> filename;

			if (is_file_exist(filename))
			{
				cout << "File with given name exists, do you want to rewrite (rw) this file or add new results (a)? " << endl;
				cout << "rw/A: ";

				// Clearing out 'save' string
				save.clear();

				while (true)
				{
					// Reassigning 'save' variable to store new choice of user
					cin >> save;
					if (save == "RW" || save == "Rw" || save == "rW" || save == "rw")
					{
						// Initializing output file stream
						ofstream ofs(filename);
						// Writing string to file
						ofs << data;
						// Closing output file stream
						ofs.close();
						break;
					}
					else if (save == "A" || save == "a")
					{
						// Initializing output file stream
						ofstream ofs(filename, std::ios_base::app);
						// Writing string to file
						ofs << data;
						// Closing output file stream
						ofs.close();
						break;
					}
					else
						cout << "Incorrect input. Try again. " << endl;
				}
			}
			else
			{
				// Initializing output file stream
				ofstream ofs(filename);
				// Writing string to file
				ofs << data;
				// Closing output file stream
				ofs.close();
				break;
			}
			cout << "Data successfully saved into a file " << filename << endl;

			// Breaking infinite loop
			break;
		}
		else if (save == "N" || save == "n")
			break;
		else
			cout << "Incorrect input. Try again. " << endl;
	}
}

// Prints table with results
void print_table(const string &text)
{
	// Printing static table
	// 'setw()' - sets width of output stream
	// 'setfill()' - filling with char in brackets
	cout << right << "+--------------------------------------+" << endl;
	cout << "|Count of symbols in text:   " << setw(10) << setfill(' ') << count_of_symbols(text) << '|' << endl;
	cout << "|-----------------------------" << setw(10) << setfill('-') << '|' << endl;
	cout << "|Count of words in text:     " << setw(10) << setfill(' ') << count_of_words(text) << '|' << endl;
	cout << "|-----------------------------" << setw(10) << setfill('-') << '|' << endl;
	cout << "|Count of sentences in text: " << setw(10) << setfill(' ') << count_of_sentences(text) << '|' << endl;
	cout << "|-----------------------------" << setw(10) << setfill('-') << '|' << endl;
	cout << "|Count of paragraphs:        " << setw(10) << setfill(' ') << count_of_paragraphs(text) << '|' << endl;
	cout << "+--------------------------------------+" << endl;
}

int main(int arhc, char *argv[])
{
	cout << endl;
	cout << "***************************************************************************" << endl;
	cout << "*Adjei-Boye Nii Adjetey											        " << endl;
	cout << "*Group 414															        " << endl;
	cout << "*Control work 4													        " << endl;
	cout << "*Variant 1															        " << endl;
	cout << "*Count the number of characters, words, lines, paragraphs in a given text. " << endl;
	cout << "*Count the number of words in sentences and output a statistical.			" << endl;
	cout << "*table in which the length of the sentence in words will correspond.		" << endl;
	cout << "*to the number of such sentences in the analyzed text.	\n					" << endl;
	cout << "***************************************************************************" << endl;

	int userchoice1 = 0;
	do
	{
		cout << endl
			 << "MAIN MENU" << endl;
		cout << "1 - Start " << endl;
		cout << "2 - Exit " << endl;
		while (!(cin >> userchoice1) && (userchoice1 < 1 || userchoice1 > 2))
		{
			cout << "Invalid Input, please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		switch (userchoice1)
		{
			{
			case start:
				int userchoice2 = 0;
				do
				{
					cout << endl
						 << "SUB MENU" << endl;
					cout << "1 - File Input " << endl;
					cout << "2 - User Input " << endl;
					while (!(cin >> userchoice2) && (userchoice2 < 1 || userchoice2 > 3))
					{
						cout << "Invalid Input, please try again." << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					switch (userchoice2)
					{
						{
						case fileInput:
							string filename{};

							cout << "Enter file name: ";
							cin >> filename;

							// Initializing 'data' variable which contain content from file
							string data(read_content_from_file(filename));
							// Initializing 'results' variable which contain results of counting symbols, words, sentences and paragraphs
							string results(string_results(data));
							// Printing table
							print_table(data);
							// Saving results into file
							save_str_to_file(results);
							break;
						}
						{
						case userInput:
							// Initializing string which will be contain user's text
							string text;

							cout << "Enter text (Enter # to terminate input): " << endl;
							cin.ignore();
							getline(cin, text, '#');

							// Initializing 'results' variable which contain results of counting symbols, words, sentences and paragraphs
							string results(string_results(text));
							// Printing table
							print_table(text);
							// Saving results into file
							save_str_to_file(results);
							break;
						}
						{
						case back:
							break;
						}
					}
				} while (userchoice2 != 3);
				break;
			}
			{
			case finish:
				break;
			}
		}

	} while (userchoice1 != 2);
}
