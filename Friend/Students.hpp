#include <iostream>

#define ERR_MSG "Error: "
#define NUL '\0'

#define TPH_NUMBER_MIN 80000000000
#define TPH_NUMBER_MAX 89999999999

#define YEAR_OF_BIRTH_MIN 1962
#define YEAR_OF_BIRTH_MAX 2005

#define BUFF_SIZE 256

class Student{
private:
    enum Faculties {
        FRT = 0,
        FEL = 1,
        FKTI = 2,
        FEA = 3,
        FIBS = 4,
        GF = 5
    };

    char* lastname;
    char* name;
    char* patronymic;
    char* dateOfBirth;
    char* address;
    unsigned long int telephoneNumber;
    unsigned short int faculty;
    short int yearInUniversity;

public:
    Student(){
        this->lastname = new char[1];
        this->name = new char[1];
        this->patronymic = new char[1];
        this->dateOfBirth = new char[11]; // Size is 11, because template is: dd.mm.yyyy\0
        this->address = new char[1];
        this->telephoneNumber = TPH_NUMBER_MIN;
        this->faculty = 0;
        this->yearInUniversity = 1;
    };
    virtual ~Student(){
        delete[] this->lastname;
        this->lastname = nullptr;

        delete[] this->name;
        this->name = nullptr;

        delete[] this->patronymic;
        this->patronymic = nullptr;

        delete[] this->dateOfBirth;
        this->dateOfBirth = nullptr;

        delete[] this->address;
        this->address = nullptr;
    };

    size_t returnsCountOfElementsInCharArray(const char* str){
        size_t count { 0 };

        while(*str != NUL){
            count++;
            str++;
        }

        if(count == 0){
            std::cout << ERR_MSG << "your string is empty." << std::endl;
            exit(EXIT_FAILURE);
        }

        return count;
    }

    void showAllInfoAboutStudent(Student* students, short int sizeOfArr, short int iter){
        std::cout << std::endl << "==== ==== Student #" << iter <<  " ==== ==== " << std::endl;
        std::cout << "Lastname: " << students[iter].getLastName() << std::endl;
        std::cout << "Name: " << students[iter].getName() << std::endl;
        std::cout << "Patronymic: " << students[iter].getPatronymic() << std::endl;
        std::cout << "Date of birth: " << students[iter].getDateOfBirth() << std::endl;
        std::cout << "Address: " << students[iter].getAddress() << std::endl;
        std::cout << "Telephone number: " << students[iter].getTelephoneNumber() << std::endl;

        switch (students[iter].getFaculty()){
            case FRT:
                std::cout << "Faculty of Radio Engineering and Telecommunications. " << std::endl;
            break;
            case FEL:
                std::cout << "Faculty of Electronics. " << std::endl;
            break;
            case FKTI:
                std::cout << "Faculty of Computer Technology and Informatics. " << std::endl;
            break;
            case FEA:
                std::cout << "Faculty of Electrical Engineering and Automation. " << std::endl;
            break;
            case FIBS:
                std::cout << "Faculty of Information-Measuring and Biotechnical Systems. " << std::endl;
            break;
            case GF:
                std::cout << "Faculty of Humanities. " << std::endl;
            break;
            default:
                std::cout << "Most likely that you made a mistake. " << std::endl;
                break;
            }
            switch (students[iter].getYearInUniversity()) {
            case 1:
                std::cout << students[iter].getName() << " is studying in the "
                          << students[iter].getYearInUniversity()
                          << "st year. " << students[iter].getName()
                          << " He is a bachelor. " << std::endl;
            break;
            case 2:
                std::cout << students[iter].getName() << " is studying in the "
                          << students[iter].getYearInUniversity()
                          << "nd year. " << students[iter].getName()
                          << " is a bachelor. " << std::endl;
            break;
            case 3:
                std::cout << students[iter].getName() << " is studying in the "
                          << students[iter].getYearInUniversity()
                           << "rd year. " << students[iter].getName()
                           << " is a bachelor. " << std::endl;
            break;
            case 4:
                std::cout << students[iter].getName() << " is studying in the "
                          << students[iter].getYearInUniversity()
                          << "th year. " << students[iter].getName()
                          << " is a bachelor. " << std::endl;
            break;
            case 5:
                std::cout << students[iter].getName() << " is studying in the "
                          << students[iter].getYearInUniversity()
                          << "th year. " << students[iter].getName()
                          << " has a master's degree. " << std::endl;
            break;
            case 6:
                std::cout << students[iter].getName() << " is studying in the "
                          << students[iter].getYearInUniversity()
                          << "th year. " << students[iter].getName()
                          << " has a master's degree. " << std::endl;
            break;
            default:
                std::cout << "Most likely this student has already graduated or "
                             "you made a mistake when specifying the year of study." << std::endl;
            break;
        }

        std::cout << "==== ==== ==== ==== ==== ==== " << std::endl << std::endl;
    }

    inline bool checkAllocatedMemory(const char* str){
        if(returnsCountOfElementsInCharArray(str) > 0) return true;
        else return false;
    }

    inline const char* getLastName() { return this->lastname; }
    void setLastName(const char* newLastName){
        if(checkAllocatedMemory(newLastName)){
            this->lastname = new char[returnsCountOfElementsInCharArray(newLastName)];

            for(size_t i = 0; i < returnsCountOfElementsInCharArray(newLastName); i++)
                *(this->lastname + i) = *(newLastName + i);
        }
    }

    inline const char* getName() { return this->name; }
    void setName(const char* newName){
        if(checkAllocatedMemory(newName)){
            this->name = new char[returnsCountOfElementsInCharArray(newName)];

            for(size_t i = 0; i < returnsCountOfElementsInCharArray(newName); i++)
                *(this->name + i) = *(newName + i);
        }
    }

    inline const char* getPatronymic() { return this->patronymic; }
    void setPatronymic(const char* newPatronymic){
        if(checkAllocatedMemory(newPatronymic)){
            this->patronymic = new char[returnsCountOfElementsInCharArray(newPatronymic)];

            for(size_t i = 0; i < returnsCountOfElementsInCharArray(newPatronymic); i++)
                *(this->patronymic + i) = *(newPatronymic + i);
        }
    }

    short int charPtrToShortInt(const char* str){
        short int result {};

        for(size_t i = 0; *(str + i) != NUL; i++)
            result = (result * 10) + ((*(str + i)) - '0');

        return result;
    }

    short int getDayFromDateOfBirth(const char* dateOfBirthStr){
        char* str = new char[3];
        *str = *dateOfBirthStr;
        *(str + 1) = *(dateOfBirthStr + 1);
        *(str + 2) = NUL;

        short int day = charPtrToShortInt(str);

        delete[] str;
        str = nullptr;

        return day;
    }

    short int getYearFromDateOfBirth(const char* dateOfBirthStr){
        char* str = new char[5];
        *str = *(dateOfBirthStr + 6);
        *(str + 1) = *(dateOfBirthStr + 7);
        *(str + 2) = *(dateOfBirthStr + 8);
        *(str + 3) = *(dateOfBirthStr + 9);
        *(str + 4) = NUL;

        short int year = charPtrToShortInt(str);

        if(year >= YEAR_OF_BIRTH_MIN && year <= YEAR_OF_BIRTH_MAX)
            return year;
        else{
            std::cout << ERR_MSG << "year of birth can be: " << YEAR_OF_BIRTH_MIN
                      << " < year < " << YEAR_OF_BIRTH_MAX << ". " << std::endl;
            return 0;
        }
        delete[] str;
        str = nullptr;
    }

    inline const char* getDateOfBirth() { return this->dateOfBirth; }
    void setDateOfBirth(const char* newDateofBirth){
        if(returnsCountOfElementsInCharArray(newDateofBirth) == 10){
            if(*(newDateofBirth + 2) == '.' &&
                    *(newDateofBirth + 5) == '.' &&
                    std::isdigit(*newDateofBirth) && std::isdigit(*(newDateofBirth + 1)) &&
                    std::isdigit(*(newDateofBirth + 3)) && std::isdigit(*(newDateofBirth + 4)) &&
                    std::isdigit(*(newDateofBirth + 6)) && std::isdigit(*(newDateofBirth + 7)) &&
                    std::isdigit(*(newDateofBirth + 8)) && std::isdigit(*(newDateofBirth + 9)) &&
                    *(newDateofBirth + 10) == NUL){

                if(((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '1')) ||
                        ((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '3')) ||
                        ((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '5')) ||
                        ((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '7')) ||
                        ((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '8')) ||
                        ((*(newDateofBirth + 3) == '1') && (*(newDateofBirth + 4) == '0')) ||
                        ((*(newDateofBirth + 3) == '1') && (*(newDateofBirth + 4) == '2'))){

                    short int day { getDayFromDateOfBirth(newDateofBirth) };
                    if(day > 0 && day <= 31){
                        for(size_t i = 0; i < returnsCountOfElementsInCharArray(newDateofBirth); i++)
                            *(this->dateOfBirth + i) = *(newDateofBirth + i);
                    }
                    else{
                        std::cout << ERR_MSG << "Jan, Mar, May, Jul, Aug, Oct, Dec have 31 days."
                                  << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
                else if(((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '4')) ||
                        ((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '6')) ||
                        ((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '9')) ||
                        ((*(newDateofBirth + 3) == '1') && (*(newDateofBirth + 4) == '1'))){

                    short int day = getDayFromDateOfBirth(newDateofBirth);
                    if(day > 0 && day <= 30){
                        for(size_t i = 0; i < returnsCountOfElementsInCharArray(newDateofBirth); i++)
                            *(this->dateOfBirth + i) = *(newDateofBirth + i);
                    }
                    else{
                        std::cout << ERR_MSG << "Apr, Jun, Sep, Nov have 30 days."
                                  << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
                else if(((*(newDateofBirth + 3) == '0') && (*(newDateofBirth + 4) == '2'))){
                    short int year { getYearFromDateOfBirth(newDateofBirth) };

                    if(year != 0){
                        short int day { getDayFromDateOfBirth(newDateofBirth) };

                        if(year % 4 == 0){
                            if(day > 0 && day <= 29){
                                for(size_t i = 0;
                                    i < returnsCountOfElementsInCharArray(newDateofBirth); i++)
                                    *(this->dateOfBirth + i) = *(newDateofBirth + i);
                            }
                            else{
                                std::cout << ERR_MSG << "in a leap year, there are 29 days in february."
                                          << std::endl;
                                exit(EXIT_FAILURE);
                            }
                        }
                        else {
                            if(day > 0 && day <= 28){
                                for(size_t i = 0;
                                    i < returnsCountOfElementsInCharArray(newDateofBirth); i++)
                                    *(this->dateOfBirth + i) = *(newDateofBirth + i);
                            }
                            else{
                                std::cout << ERR_MSG << "in a non-leap year, "
                                                        "there are 28 days in february. " << std::endl;
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }
        }
        else{
            std::cout << ERR_MSG << "incorrect birthday filling template. " << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    inline const char* getAddress() { return this->address; }
    void setAddress(const char* newAddress){
        if(checkAllocatedMemory(newAddress)){
            this->address = new char[returnsCountOfElementsInCharArray(newAddress)];

            for(size_t i = 0; i < returnsCountOfElementsInCharArray(newAddress); i++)
                *(this->address + i) = *(newAddress + i);
        }
    }

    inline unsigned long int getTelephoneNumber() { return this->telephoneNumber; }
    inline void setTelephoneNumber(unsigned long int newTelephoneNumber){
        if(newTelephoneNumber >= TPH_NUMBER_MIN && newTelephoneNumber <= TPH_NUMBER_MAX)
            this->telephoneNumber = newTelephoneNumber;
        else{
            std::cout << ERR_MSG << "invalid telephone number. " << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    inline Faculties getFaculty(){
        if(faculty == 0)
            return Faculties::FRT;
        else if(faculty == 1)
            return Faculties::FEL;
        else if(faculty == 2)
            return Faculties::FKTI;
        else if(faculty == 3)
            return Faculties::FEA;
        else if(faculty == 4)
            return Faculties::FIBS;
        else if(faculty == 5)
            return Faculties::GF;
        else{
            std::cout << ERR_MSG << "incorrect faculty. " << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    inline void setFaculty(short int newFaculty){
        if(newFaculty >= 0 && newFaculty <= 5)
            this->faculty = newFaculty;
        else{
            std::cout << ERR_MSG << "incorrect faculty. " << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    inline short int getYearInUniversity() { return this->yearInUniversity; }
    inline void setYearInUniversity(short int newYearInUniversity){
        if(newYearInUniversity > 0 && newYearInUniversity < 7)
            this->yearInUniversity = newYearInUniversity;
        else{
            std::cout << ERR_MSG << "Maybe you made a mistake year can be: 0 < year < 7 "
                                    "(Postgraduate and doctoral studies and others"
                                    " are not taken into account). " << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    void showAllInfoAboutStudentWithSpecificFaculty(Student* students, const short int sizeOfArr,
                                 const short int numberOfFaculty){
        unsigned short int isSearchResultIsEmpty {};

        for(short int i = 0; i < sizeOfArr; i++)
            if(students[i].getFaculty() == numberOfFaculty){
                showAllInfoAboutStudent(students, sizeOfArr, i);
                isSearchResultIsEmpty++;
            }

        if(isSearchResultIsEmpty == 0)
            std::cout << "No results found for your query. " << std::endl;
    }

    void showAllInfoAboutStudentWithSpecificYearOfBirth(Student* students, const short int sizeOfArr,
                                 const short int yearOfBirth){
        unsigned short int isSearchResultIsEmpty {};

        for(short int i = 0; i < sizeOfArr; i++)
            if(getYearFromDateOfBirth(students[i].getDateOfBirth()) > yearOfBirth){
                showAllInfoAboutStudent(students, sizeOfArr, i);
                isSearchResultIsEmpty++;
            }

        if(isSearchResultIsEmpty == 0)
            std::cout << "No results found for your query. " << std::endl;
    }

    void showAllInfoAboutStudentWithSpecificFacultyAndYearInUniversity(Student* students,
                                                                       const short int sizeOfArr,
                                 const short int numberOfFaculty, const short int yearInUniversityParam){
        unsigned short int isSearchResultIsEmpty {};

        for(short int i = 0; i < sizeOfArr; i++)
            if(students[i].getFaculty() == numberOfFaculty &&
                    students[i].getYearInUniversity() == yearInUniversityParam){
                showAllInfoAboutStudent(students, sizeOfArr, i);
                isSearchResultIsEmpty++;
            }

        if(isSearchResultIsEmpty == 0)
            std::cout << "No results found for your query. " << std::endl;
    }

    inline void clearCharPtrMem(char* ptr){     //method just for clear memory (anti-cumbersome code)
        delete[] ptr;
        ptr = nullptr;
        ptr = new char[BUFF_SIZE];
    }

    void fillStudent(Student* students, const short int sizeOfArr){  //method of filling the Student obj
        char* tmpStr = new char[BUFF_SIZE];
        char* dobStr = new char[11];
        unsigned long int tlphNum {};
        unsigned short int tmpFaculty {};
        short int yearInUn {};

        char clsBuffer {};

        for(short int studentIter = 0; studentIter < sizeOfArr; studentIter++){
            std::cout << "Enter lastname: ";
            scanf("%[^\n]", tmpStr);
            students[studentIter].setLastName(tmpStr);

            clearCharPtrMem(tmpStr);

            std::cout << "Enter name: ";
            scanf("%c", &clsBuffer); // this scanf just for do not let program skip next scanf -
                                     // smth like clear the buffer
            scanf("%[^\n]", tmpStr);

            size_t nameSize { returnsCountOfElementsInCharArray(tmpStr) };
            for(size_t i = 0; i < nameSize; i++) //this loop is for remove \n symbol
                if(*(tmpStr + i) == '\n')        // for a beautiful display of info
                    *(tmpStr + i) = NUL;         // in switch -> line 110

            students[studentIter].setName(tmpStr); //setting name
            clearCharPtrMem(tmpStr);    // clearing earlier allocated memory and reallocating new memory

            std::cout << "Enter patronymic: ";
            scanf("%c", &clsBuffer);
            scanf("%[^\n]", tmpStr);
            students[studentIter].setPatronymic(tmpStr);

            clearCharPtrMem(tmpStr);

            std::cout << "Enter date of birth (dd.mm.yyyy): ";
            scanf("%11s", dobStr); // %11s is available for only 11 symbols
            students[studentIter].setDateOfBirth(dobStr);

            std::cout << "Enter address: ";
            scanf("%c", &clsBuffer);
            scanf("%[^\n]", tmpStr);
            students[studentIter].setAddress(tmpStr);

            clearCharPtrMem(tmpStr);

            std::cout << "Enter telephone number (8XXX-XXX-XX-XX -> without symbol \'-\'): ";
            std::cin >> tlphNum;
            students[studentIter].setTelephoneNumber(tlphNum);

            std::cout << "Faculties: \n0. Faculty of Radio Engineering and Telecommunications."
                         "\n1. Faculty of Electronics. "
                         "\n2. Faculty of Computer Technology and Informatics. "
                         "\n3. Faculty of Electrical Engineering and Automation. "
                         "\n4. Faculty of Information-Measuring and Biotechnical Systems. "
                         "\n5. Faculty of Humanities. "
                         "\nEnter number of faculty: ";
            std::cin >> tmpFaculty;
            students[studentIter].setFaculty(tmpFaculty);

            std::cout << "Enter year (1 <= year <= 7): ";
            std::cin >> yearInUn;
            students[studentIter].setYearInUniversity(yearInUn);
        }

        delete[] dobStr;
        dobStr = nullptr;

        delete[] tmpStr;
        tmpStr = nullptr;
    }
};
