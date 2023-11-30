#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <clocale>

bool myIsPunct(char c)
{
    std::string toremove("[$&+,:;=?@#|'<>.-^*()%!]");
    for (size_t i{}; i < toremove.size(); i++)
        if (c == toremove.at(i))
            return true;
    return false;
}

// Returns "true" if file with specified name exists, otherwise - "false"
bool exists(const char *filename)
{
    std::ifstream ifs(filename);
    return ifs.good();
}

// Returns content of file as a string
// 'filename' - name of the file
std::string readFileToStr(const char *filename)
{
    if (!exists(filename))
    {
        std::cout << "Filename with specified name doesn't exitst in current folder. Exiting with status -1\n";
        exit(-1);
    }

    // Opening file
    std::fstream fs(filename);

    // Initializing output string stream
    std::ostringstream ss;

    // Putting all data from the 'fs' buffer to the output string stream 'ss'
    ss << fs.rdbuf();

    // Returning content of 'ss' as a std::string type
    return ss.str();
}

// Removes punctuation from the specified string
void removePunct(std::string &str)
{
    auto it{str.cbegin()};
    while (it != str.cend())
    {
        if (myIsPunct(*it))
            str.erase(it);
        ++it;
    }

    // Erasing last symbol if it is a endline symbol
    if (*(str.cend() - 1) == '\n')
        str.erase(str.cend() - 1);
}

// Returns vector of words in a string, except any spaces
// 'str' - string to split
// ' delim' - delimeter by which string will be splitted
std::vector<std::string> split_str(const std::string &str, const std::string &delim = " ")
{
    std::vector<std::string> splitted_str;
    std::string strCopy(str);

    // Splitting string on words
    size_t pos{strCopy.find(delim)}, initial_pos{};
    while (pos != std::string::npos)
    {
        splitted_str.emplace_back(strCopy.substr(initial_pos, pos - initial_pos));
        initial_pos = pos + 1;
        pos = strCopy.find(delim, initial_pos);
    }

    // Adding last word
    splitted_str.emplace_back(strCopy.substr(initial_pos, std::min(pos, strCopy.size()) - initial_pos + 1));

    return splitted_str;
}

// Returns "true" if vector of strings contains specified string
bool isContains(const std::vector<std::string> &v, const std::string &s)
{
    for (const auto &word : v)
        if (s == word)
            return true;
    return false;
}

// Returns vector of words which are occuring in the same contexts
std::vector<std::string> getWordsInSameContexts(const std::string &text)
{
    // Making a copy of text
    std::string textCopy(text);

    // At first removing all punctuation and last endline symbol ('\n')
    removePunct(textCopy);

    // Splitting text by words and creating result vector of words in same contexts
    std::vector<std::string> vec(split_str(textCopy)), wordsInSameContexts;

    /* --- Comparing pairs of words in the text --- */
    // Getting words with even indeces (i, i + 2, i + 4, ..., where i = 0)
    for (auto fst{vec.cbegin()}, snd{std::next(std::next(fst))};
         fst != vec.cend() && snd != vec.cend(); ++fst, ++snd)
    {
        // Getting words with odd indeces (i + 1, i + 3, i + 5, ..., where i = 0)
        for (auto anotherFst{fst + 1}, anotherSnd{std::next(std::next(anotherFst))};
             anotherFst != vec.cend() && anotherSnd != vec.cend(); ++anotherFst, ++anotherSnd)
        {
            // Comparing them and if they are equal -> adding them to the vector
            if (*fst == *anotherFst && *snd == *anotherSnd)
            {
                if (!isContains(wordsInSameContexts, *std::next(fst)))
                    wordsInSameContexts.emplace_back(*std::next(fst));
                if (!isContains(wordsInSameContexts, *std::prev(anotherSnd)))
                    wordsInSameContexts.emplace_back(*std::prev(anotherSnd));
            }
        }
    }
    return wordsInSameContexts;
}

// Returns vector of words which are occuring in the same contexts
// (if there is no occurences - returns empty string)
std::string getOccurrenceContext(const std::string &text)
{
    std::string textCopy(text);
    removePunct(textCopy);
    std::vector<std::string> vec(split_str(textCopy));
    for (auto fst{vec.cbegin()}, snd{std::next(std::next(fst))};
         fst != vec.cend() && snd != vec.cend(); ++fst, ++snd)
        for (auto anotherFst{fst + 1}, anotherSnd{std::next(std::next(anotherFst))};
             anotherFst != vec.cend() && anotherSnd != vec.cend(); ++anotherFst, ++anotherSnd)
            if (*fst == *anotherFst && *snd == *anotherSnd)
                return *fst + " " + *std::next(std::next(fst));
    return "";
}

// Prints all words in same contexts
void printWordsInSameContexts(const std::vector<std::string> &words)
{
    std::cout << "All words that are occuring in the same contexts: " << std::endl;
    for (const auto &word : words)
        std::cout << word << std::endl;
    std::endl(std::cout);
}

// Prints all permutations of words in same contexts
void printPermutationsOfWordsInSameContexts(std::vector<std::string> words, const std::string &context)
{
    std::vector<std::string> splittedContext(split_str(context));
    
    if (splittedContext.empty())
        return;
    
    unsigned permutations{};
    for (size_t i{}; i < words.size(); i++)
    {
        for (size_t j{}; j < words.size(); j++)
        {
            std::cout << *splittedContext.cbegin() + ' ' + words.at(i) + ' ' + *(splittedContext.cend() - 1) << '\n'
                      << *splittedContext.cbegin() + ' ' + words.at(j) + ' ' + *(splittedContext.cend() - 1) << "\n\n";
            permutations++;
        }
    }
    std::cout << "Count of permutations = " << permutations - 1 << std::endl;
}

int main()
{
    setlocale(LC_ALL, "rus");

    std::cout << "From input.txt:\n";
    std::string str(readFileToStr("input.txt"));
    printPermutationsOfWordsInSameContexts(getWordsInSameContexts(str), getOccurrenceContext(str));

    std::cout << "\n\nFrom input_2.txt:\n";
    str = readFileToStr("input_2.txt");
    printPermutationsOfWordsInSameContexts(getWordsInSameContexts(str), getOccurrenceContext(str));

    std::cout << "Enter your file name: ";
    std::string usersFilename;
    std::getline(std::cin, usersFilename, '\n');
    std::cout << "\n\nFrom " << usersFilename << std::endl;
    str = readFileToStr(usersFilename.c_str());
    printPermutationsOfWordsInSameContexts(getWordsInSameContexts(str), getOccurrenceContext(str));

    std::cout << "($ - to end entering)\nEnter your text: ";
    std::string usersText;
    std::getline(std::cin, usersText, '$');
    printPermutationsOfWordsInSameContexts(getWordsInSameContexts(usersText), getOccurrenceContext(usersText));
    // напишите функцию вычисляющую напишите программу вычисляющую$
    // я пишу экзамен я сдаю экзамен$

    return EXIT_SUCCESS;
}
