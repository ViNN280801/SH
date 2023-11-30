#include <iostream>
#include <iterator>
#include <cctype> // for "ispunct()" func
#include <fstream>
#include <locale>
#include <vector>
#include <iomanip>

// Returns content from a file
std::string getContentOfFile(const std::string &nameoffile)
{
    // Initializing file stream variable and openning file
    std::fstream fs(nameoffile);
    std::string line, content("");
    // Check if file had opened
    if (fs.is_open())
        // While not EOF (end of file) - write to 'content' string
        while (fs.good())
        {
            fs >> line;
            content += line + " ";
        }
    else
        std::cout << "Warning: There is no file with name " << nameoffile
                  << ". Returning empty string." << std::endl;

    return content;
}

// Modifies string: removes all symbols (except whitespaces -> ' ') which are not an eng alphabet letter
void removePunct(std::string &_s)
{
    // Iterating over the string
    for (auto it{std::cbegin(_s)}; it != std::cend(_s); ++it)
        // If symbol is not a eng alphabet letter - erase it
        if (ispunct(*it))
            _s.erase(it);
}

// Returns minimal from two  variables of same type
template <typename T>
const T &min(const T &x, const T &y) { return (x < y) ? x : y; }

// Returns dynamic array of words in a string, except any spaces
std::vector<std::string> split_str(const std::string &str, const std::string &separator = " ")
{
    std::vector<std::string> splitted_str;
    std::string strCopy(str);

    // Splitting string on words
    size_t pos{strCopy.find(separator)}, initial_pos{};
    while (pos != std::string::npos)
    {
        splitted_str.push_back(strCopy.substr(initial_pos, pos - initial_pos));
        initial_pos = pos + 1;
        pos = strCopy.find(separator, initial_pos);
    }
    // Adding end word to an array
    splitted_str.push_back(strCopy.substr(initial_pos, min(pos, strCopy.size()) - initial_pos + 1));

    return splitted_str;
}

// Returns user's multiline input
std::string multiLineInput()
{
    std::string text, line;
    std::cout << "Enter text (Type ##EXIT## - to exit): " << std::endl;
    for (;;)
    {
        std::getline(std::cin, line, '\n');
        if (line == "##EXIT##")
            break;
        text += line + " ";
    }
    return text;
}

bool contains(const std::vector<std::pair<std::string, int>> &v, const std::string &word)
{
    for (auto it{std::cbegin(v)}; it != std::cend(v); ++it)
        if (it->first == word)
            return true;
    return false;
}

void sortByAlphabet(std::vector<std::pair<std::string, int>> &v)
{
    for (size_t i{}; i < v.size(); i++)
    {
        for (size_t j{i + 1}; j < v.size(); j++)
        {
            if (v.at(i).first > v.at(j).first)
            {
                std::swap(v.at(i).first, v.at(j).first);
                std::swap(v.at(i).second, v.at(j).second);
            }
        }
    }
}

void sortByCountOfOccurrences(std::vector<std::pair<std::string, int>> &v)
{
    for (size_t i{}; i < v.size(); i++)
    {
        for (size_t j{i + 1}; j < v.size(); j++)
        {
            if (v.at(i).second > v.at(j).second)
            {
                std::swap(v.at(i).first, v.at(j).first);
                std::swap(v.at(i).second, v.at(j).second);
            }
        }
    }
}

#include <cstring>

template <typename T, typename U>
void printVectorOfPairsAsATable(const std::vector<std::pair<T, U>> &vec)
{
    std::cout << std::setw(26) << std::setfill('-') << '\n';
    std::cout.flush();
    for (const auto &el : vec)
    {
        std::cout << '|' << el.first << std::setw(25 - el.first.length() - 2)
                  << std::setfill(' ') << el.second << '|' << std::endl;
    }
    std::cout << std::setw(26) << std::setfill('-') << '\n';
}

template <typename T, typename U>
void writeDataToFile(const std::vector<std::pair<T, U>> &vec, size_t size, const char *nameoffile)
{
    if (size != 0 && size != std::string::npos)
    {
        // Doesn't overwrite existing data, adds new ones
        std::fstream fs(nameoffile, std::ios_base::app);
        fs << std::setw(26) << std::setfill('-') << '\n';
        fs.flush();
        for (size_t i{}; i < size; i++)
            fs << '|' << vec.at(i).first << std::setw(25 - vec.at(i).first.length() - 2)
               << std::setfill(' ') << vec.at(i).second << '|' << std::endl;
        fs << std::setw(27) << std::setfill('-') << "\n\n";
        std::cout << "Data has been successfully written to a " << nameoffile << std::endl;
    }
    else
        std::cout << "Data hasn't been written to a " << nameoffile << std::endl;
}

// Prints all occurrences in the text and theirs frequency
void printCountOfOccurrencesInText(const std::string &text)
{
    // Initializing vector of strings that contains each word from the text
    std::vector<std::string> words(split_str(text));

    // That vector will contains pair of values:
    // 1 - word
    // 2 - count of occurrences
    std::vector<std::pair<std::string, int>> occurrences;

    // Iterating over each word in a text
    for (auto it{std::cbegin(words)}; it != std::cend(words); ++it)
    {
        int counter{};
        for (auto jt{it + 1}; jt != std::cend(words); ++jt)
        {
            // If found occurrence - incrementing it counter
            if (*it == *jt)
                counter++;
        }
        // Adding element only if 'occurrences' doesn't contains it yet
        if (!contains(occurrences, *it))
            occurrences.push_back(std::make_pair(*it, std::move(counter + 1)));
    }

    std::cout << "All occurrences: " << std::endl;
    printVectorOfPairsAsATable(occurrences);
    std::cout << "Count of unique words: " << occurrences.size() << std::endl;

    size_t count{};
    std::cout << "How many words do you want to write to a files: ";
    std::cin >> count;

    // Sorting by alphabet and writing data to file
    sortByAlphabet(occurrences);
    writeDataToFile(occurrences, count, "alphaSorted.txt");

    // Sorting by count of occurrences and writing data to file
    sortByCountOfOccurrences(occurrences);
    writeDataToFile(occurrences, count, "countSorted.txt");
}

int main()
{
    // Setting russian language
    setlocale(LC_ALL, "rus");

    std::string text(getContentOfFile("input.txt"));
    std::cout << text << std::endl;
    removePunct(text);
    printCountOfOccurrencesInText(text);

    std::string str(multiLineInput());
    removePunct(str);
    std::cout << str << std::endl;
    printCountOfOccurrencesInText(str);

    return EXIT_SUCCESS;
}
