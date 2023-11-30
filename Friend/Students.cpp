#include "Students.hpp"

//#define __test_with_static_variables__
//#define __test_with_user_variables

int main(int argc, char* argv[]){
    const short int size { 1 };
    Student* students = new Student[size];

    /*students[0].setLastName("Baranov");
    students[0].setName("Yan");
    students[0].setPatronymic("Semenovich");
    students[0].setDateOfBirth("20.12.1982");
    students[0].setAddress("Penza region, Odintsovo, Gagarin Ave., 29");
    students[0].setYearInUniversity(1);
    students[0].setTelephoneNumber(84953563092);
    students[0].setFaculty(0);

    students[1].setLastName("Orlov");
    students[1].setName("Vilen");
    students[1].setPatronymic("Kupriyanovich");
    students[1].setDateOfBirth("15.04.2001");
    students[1].setAddress("Lipetsk region, Orekhovo-Zuyevo, Gagarin highway, 58");
    students[1].setYearInUniversity(2);
    students[1].setTelephoneNumber(84955341143);
    students[1].setFaculty(1);

    students[2].setLastName("Trofimov");
    students[2].setName("Arseniy");
    students[2].setPatronymic("Danilovich");
    students[2].setDateOfBirth("17.02.2001");
    students[2].setAddress("Orenburg region, Sergiev Posad city, nab. Kosiora, 82");
    students[2].setYearInUniversity(3);
    students[2].setTelephoneNumber(89298011002);
    students[2].setFaculty(2);

    students[3].setLastName("Kotov");
    students[3].setName("Vladimir");
    students[3].setPatronymic("Anatolevich");
    students[3].setDateOfBirth("13.01.2003");
    students[3].setAddress("Nizhny Novgorod region, the city of Noginsk, Bukharestskaya Ave., 60");
    students[3].setYearInUniversity(4);
    students[3].setTelephoneNumber(89290143229);
    students[3].setFaculty(3);

    students[4].setLastName("Sitnikov");
    students[4].setName("Valeriy");
    students[4].setPatronymic("Arkadievich");
    students[4].setDateOfBirth("01.07.2000");
    students[4].setAddress("Bryansk region, the city of Mytishchi, Balkan highway, 80");
    students[4].setYearInUniversity(5);
    students[4].setTelephoneNumber(89111887033);
    students[4].setFaculty(4);

    students[5].setLastName("Vishnyakova");
    students[5].setName("Anastasia");
    students[5].setPatronymic("Alexeevna");
    students[5].setDateOfBirth("11.09.1999");
    students[5].setAddress("Tomsk region, Shakhovskaya city, 1905 lane, 85");
    students[5].setYearInUniversity(6);
    students[5].setTelephoneNumber(89112758974);
    students[5].setFaculty(5);

    students[6].setLastName("Voronova");
    students[6].setName("Mariya");
    students[6].setPatronymic("Nikolaevna");
    students[6].setDateOfBirth("11.09.2004");
    students[6].setAddress("Oryol region, Lotoshino city, lane. Budapest, 91");
    students[6].setYearInUniversity(4);
    students[6].setTelephoneNumber(84954337107);
    students[6].setFaculty(0);

    students[7].setLastName("Ponomareva");
    students[7].setName("Irina");
    students[7].setPatronymic("Olegovna");
    students[7].setDateOfBirth("08.08.2003");
    students[7].setAddress("Oryol region, the city of Vidnoye, Gagarin's entrance, 11");
    students[7].setYearInUniversity(3);
    students[7].setTelephoneNumber(84951723702);
    students[7].setFaculty(2);

    students[8].setLastName("Krylova");
    students[8].setName("Yulia");
    students[8].setPatronymic("Vasilyevna");
    students[8].setDateOfBirth("14.11.2004");
    students[8].setAddress("Nizhny Novgorod region, the city of Dorokhovo, lane. Bucharest, 35");
    students[8].setYearInUniversity(2);
    students[8].setTelephoneNumber(89296618912);
    students[8].setFaculty(0);

    students[9].setLastName("Evseev");
    students[9].setName("Michail");
    students[9].setPatronymic("Pavlovich");
    students[9].setDateOfBirth("11.01.1997");
    students[9].setAddress("Tomsk region, Shchelkovo city, Lenin Square, 72");
    students[9].setYearInUniversity(6);
    students[9].setTelephoneNumber(89602402578);
    students[9].setFaculty(4);
    */

#ifdef __test_with_static_variables__
    students->showAllInfoAboutStudentWithSpecificFaculty(students, size, 0);
    students->showAllInfoAboutStudentWithSpecificYearOfBirth(students, size, 2002);
    students->showAllInfoAboutStudentWithSpecificFacultyAndYearInUniversity(students, size, 5, 6);
#endif

#ifdef __test_with_user_variables
    short int var1 {}, var2 {};

    std::cout << "Faculties: \n0. Faculty of Radio Engineering and Telecommunications."
                 "\n1. Faculty of Electronics. "
                 "\n2. Faculty of Computer Technology and Informatics. "
                 "\n3. Faculty of Electrical Engineering and Automation. "
                 "\n4. Faculty of Information-Measuring and Biotechnical Systems. "
                 "\n5. Faculty of Humanities. "
                 "\nEnter number of faculty: ";
    std::cin >> var1;
    students->showAllInfoAboutStudentWithSpecificFaculty(students, size, var1);

    std::cout << "Enter year (" << YEAR_OF_BIRTH_MIN << " <= year <= " <<
                 YEAR_OF_BIRTH_MAX << "): ";
    std::cin >> var1;
    students->showAllInfoAboutStudentWithSpecificYearOfBirth(students, size, var1);

    for(short int i = 0; i < size; i++)
        students->showAllInfoAboutStudent(students, size, i);


    std::cout << "Faculties: \n0. Faculty of Radio Engineering and Telecommunications."
                 "\n1. Faculty of Electronics. "
                 "\n2. Faculty of Computer Technology and Informatics. "
                 "\n3. Faculty of Electrical Engineering and Automation. "
                 "\n4. Faculty of Information-Measuring and Biotechnical Systems. "
                 "\n5. Faculty of Humanities. "
                 "\nEnter number of faculty: ";
    std::cin >> var1;
    std::cout << "Enter number of year in university (0 < year < 7): ";
    std::cin >> var2;
    students->showAllInfoAboutStudentWithSpecificFacultyAndYearInUniversity(students, size, var1, var2);
#endif
    students->fillStudent(students, size);

    for(short int iter = 0; iter < size; iter++)
        students->showAllInfoAboutStudent(students, size, iter);

    delete[] students;
    students = nullptr;

    return EXIT_SUCCESS;
}
