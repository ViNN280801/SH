#include <iostream>
#include <cctype>
#include <fstream>

#include "student.hpp"

struct StudentList::Student
{
    std::string m_FIO; // ФИО
    int m_groupID;     // Номер группы
    unsigned m_est[5]; // Набор из 5 оценок, представленный в виде массива беззнаковых int
    double m_grant;    // Размер стипендии
    Student *m_next;   // Указатель на следующего студента

    // Обнуляет все переменные указанного объекта
    void clearObj(Student &);

    // Копирует содержимое указанного объекта в текущий
    void copyObj(const Student &);

    // Функция-помощник. Проверяет является ли ФИО правильно написанным
    // Т.е. переданная строка 's' содержит только два пробела в качестве
    // разделителя между фамилией и именем и именем и отчеством
    // А также не содержит цифр или иных символов, не являющиеся буквами
    // Квалификатор 'const' после объявления функции гласит о том, что
    // эта функция не изменяет внутренние свойства класса
    bool isFIOcorrect(const std::string &) const;

    // Функция-помощник. Выполняет валидацию ФИО
    // Проверяет введенную строку ФИО на правильность. Использует 'isFIOcorrect()'
    std::string usersInputToFIO() const;

    // Функция-помощник. Выполняет валидацию числа. Проверяет введение числа,
    // т.е. если вводят не целое число, то возвращает "false"
    bool isInputIsNumber(const std::string &) const;

    // Функция-помощник. Возвращает число из введенной пользователем строки
    // Внутри выполняет проверку, что введенная строка действительно является
    // целым числом без знака. Использует 'isInputIsNumber()'
    unsigned userInputToInt() const;

    // Функция-помощник. Проверяет, что переданная строка является оценкой, т.е.
    // одной цифрой не меньше 2 и не больше 5
    bool isInputIsEstimation(const std::string &) const;

    // Функция-помощник. Возвращает оценку - число от 2 до 5
    // Внутри выполняются соответствующие проверки. Использует 'isInputIsEstimation()'
    unsigned userInputToGrade() const;

    // Функция-помощник. Проверяет является ли переданная строка
    // неотрицательным целым числом или неотрицательным действительным числом
    bool isInputIsGrant(const std::string &) const;

    // Функция-помощник. Возвращает действительное неотрицательное число в качестве
    // размера стипендии. Использует 'isInputToGrade()'
    double userInputToGrant() const;

    // Конструктор без параметров. Обнуляет внутренние свойства
    explicit Student();

    // Копирующий конструктор. Позволяет инициализировать новый объект класса другим
    explicit Student(const Student &);

    // Специальный конструктор, использующийся для вставки элемента в определенное место списка
    explicit Student(Student *next, const Student &st) : m_next(next) { *this = st; }

    // Конструктор, инициализирующий каждый атрибут
    explicit Student(const std::string &, int, unsigned[5], double);

    // Оператор копирующего присваивания. Позволяет применить оператор = между
    // двумя объяектами типа 'Student'. Копирует содержимое из
    // одной переменной типа 'Student 'в другую этого же типа
    Student &operator=(const Student &);

    // Деструктор. Обнуляет все содержимое во время выхода из области видимости
    virtual ~Student();

    /* --- Блок геттеров и сеттеров для всех свойств класса --- */
    std::string getFIO() const;
    int getGroupID() const;
    unsigned *getGrades() const;
    double getGrant() const;

    void setFIO(const std::string &);
    void setGroupID(int);
    // заменяет определенную оценку. первый параметр - новая оценка
    // второй - индекс оценки, которую необходимо заменить
    void setGrade(int, short);
    void setGrades(unsigned[5]);
    void setGrant(double);
    /* --- Конец геттеров и сеттеров --- */

    // Проверяет является ли пустыми все значения текущего объекта. Если является, то возвращает "true"
    bool emptyStudent() const;

    // Проверяет является ли студент отличником, если да, то возвращает "true"
    bool isExcellentStudent() const;

    // Создает нового студента в текующий объект. Пользователь сам вводит все необходимые параметры
    void createUsersStudent();

    // Выводит в консоль все данные о текущем студенте
    void printStudentInfo() const;

    // Считывает определенное свойство студента, указанное в качестве строки и возвращает его
    std::string getStudentPropertyFromDB(const std::string &, const std::string &) const;
};

void StudentList::Student::clearObj(Student &st)
{
    st.m_next = nullptr;
    st.m_FIO.clear();
    st.m_groupID = 0;
    for (short i = 0; i < 5; i++)
        st.m_est[i] = 0;
    st.m_grant = 0;
}

void StudentList::Student::copyObj(const Student &st)
{
    m_next = st.m_next;
    m_FIO = st.m_FIO;
    m_groupID = st.m_groupID;
    for (short i = 0; i < 5; i++)
        m_est[i] = st.m_est[i];
    m_grant = st.m_grant;
}

bool StudentList::Student::isFIOcorrect(const std::string &s) const
{
    // Если переданная строка пустая - возвращаем "false"
    if (s.empty())
        return false;

    // Инициализируем строку, содержащую все символы, не являющиеся буквами
    std::string unnecessaryChars("01234567890~`!@#$%^&*()-_=+[]{}\\;:\"\'/?,.<>");
    // Инициализация счетчика пробелов
    // так как необходимо, чтобы их количество должно быть равным 2
    unsigned counter = 0;

    // Пробегаемся по переданной строке и выполняем соответствующие проверки
    for (size_t i = 0; i < s.length(); i++)
    {
        // Пробегаемся по строке с символами, являющимися не буквами, для сравнения с символов строки
        for (size_t j = 0; j < unnecessaryChars.length(); j++)
            if (s[i] == unnecessaryChars[j])
                return false;

        // Если символ является пробелом, инкрементируем счетчиком
        if (s[i] == ' ')
            counter++;
    }
    // Используя тернарный оператор, проверяем количество пробелов
    // Если их меньше двух или больше двух - возвращается "false", иначе - "true"
    return (counter < 2 || counter > 2) ? false : true;
}

std::string StudentList::Student::usersInputToFIO() const
{
    // Инициализируем строку символом, отличным от буквы
    std::string s(".");

    // Строки кода в теле цикла "while" будут выполняться до тех пор,
    // пока введенная строка не буде являться беззнаковым целым числом
    while (!isFIOcorrect(s))
    {
        std::getline(std::cin, s, '\n');
        if (!isFIOcorrect(s))
            std::cerr << "ФИО введено неверно, попробуйте еще раз: ";
    }

    return s;
}

bool StudentList::Student::isInputIsNumber(const std::string &s) const
{
    if (s.empty())
        return false;

    // Пробегаемся по всем символам строки и проверяем все ли из них являются цифрой
    for (size_t i = 0; i < s.length(); i++)
        // Если символ не цифра - возвращаем "false"
        if (!isdigit(s[i]))
            return false;
    return true;
}

unsigned StudentList::Student::userInputToInt() const
{
    // Инициализируем строку символом, отличным от цифры
    std::string s(".");
    while (!isInputIsNumber(s))
    {
        std::getline(std::cin, s, '\n');
        if (!isInputIsNumber(s))
            std::cerr << "Вы ввели не число, попробуйте еще раз: ";
    }

    // Возвращаем результат функции "stoi". stoi означает string to int,
    // т.е. она конвертирует строку в число типа int
    return std::stoi(s);
}

bool StudentList::Student::isInputIsEstimation(const std::string &s) const
{
    if (s.empty() || s.length() != 1)
        return false;
    if (isdigit(s[0]))
        return (std::stoi(s) >= 2 && std::stoi(s) <= 5) ? true : false;
    else
        return false;
}

unsigned StudentList::Student::userInputToGrade() const
{
    std::string s(".");
    while (!isInputIsEstimation(s))
    {
        std::getline(std::cin, s, '\n');
        if (!isInputIsEstimation(s))
            std::cerr << "Вы ввели не оценку, попробуйте еще раз: ";
    }
    return std::stoi(s);
}

bool StudentList::Student::isInputIsGrant(const std::string &s) const
{
    // Проверяем является ли строка не пустой и
    // точка не является первым или последним символом строки
    if (s.empty() || s[0] == '.' || s[s.length() - 1] == '.')
        return false;
    // Инициализация счетчика для точки, как разделителя дробной части от целой
    unsigned counter = 0;
    // Проверка по разделителю дробной и целой части
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
            counter++;
        if (counter > 1)
            return false;
    }

    // Проверка символов
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
            continue;
        else
        {
            if (!isdigit(s[i]))
                return false;
        }
    }

    return true;
}

double StudentList::Student::userInputToGrant() const
{
    std::string s;
    while (!isInputIsGrant(s))
    {
        std::getline(std::cin, s, '\n');
        if (!isInputIsGrant(s))
            std::cerr << "Вы ввели неверный размер стипендии, попробуйте еще раз: ";
    }
    return std::stod(s);
}

StudentList::Student::Student() { clearObj(*this); }

StudentList::Student::Student(const Student &st) { copyObj(st); }

StudentList::Student::Student(const std::string &fio, int groupID, unsigned grades[5], double grant)
    : m_FIO(fio), m_groupID(groupID), m_grant(grant), m_next(nullptr)
{
    for (short i = 0; i < 5; i++)
        m_est[i] = grades[i];
}

StudentList::Student &StudentList::Student::operator=(const Student &st)
{
    // Проверка не является ли передаваемый объект тем же самым
    // Если является, то вернуть его же
    if (&st == this)
        return *this;
    // Если нет, то выполнить операцию копирования всего
    // содержимого из переданного объекта в текущий
    copyObj(st);
    return *this;
}

StudentList::Student::~Student() { clearObj(*this); }

std::string StudentList::Student::getFIO() const { return m_FIO; }

int StudentList::Student::getGroupID() const { return m_groupID; }

unsigned *StudentList::Student::getGrades() const { return const_cast<unsigned *>(&m_est[0]); }

double StudentList::Student::getGrant() const { return m_grant; }

void StudentList::Student::setFIO(const std::string &s)
{
    if (isFIOcorrect(s))
        m_FIO = s;
    else
        std::cerr << "Замена ФИО не была произведена, т.к. переданное ФИО содержит недопустимые символы\n";
}

void StudentList::Student::setGroupID(int id) { m_groupID = id; }

void StudentList::Student::setGrade(int est, short index)
{
    if (!(est >= 2 && est <= 5))
    {
        std::cerr << "Введена неверная оценка. Оценка должна быть: [2; 5]. Оценка аннулируется\n";
        est = 0;
    }
    if (!(index >= 0 && index < 5))
    {
        std::cerr << "Введен неверный порядковый номер оценки. Должен быть: [0; 5). Первая оценка аннулируется\n";
        est = 0;
        index = 0;
    }

    for (short i = 0; i < 5; i++)
        if (i == index)
            m_est[i] = est;
}

void StudentList::Student::setGrades(unsigned est[5])
{
    for (short i = 0; i < 5; i++)
    {
        if (!(est[i] >= 2 && est[i] <= 5))
        {
            std::cerr << "Введена неверная оценка. Оценка должна быть: [2; 5]. " << i << " оценка аннулируется\n";
            est[i] = 0;
        }
        m_est[i] = est[i];
    }
}

void StudentList::Student::setGrant(double grant) { m_grant = grant; }

void StudentList::Student::createUsersStudent()
{
    std::cout << "Введите фамилию, имя и отчество студента через пробел: ";
    // Запись из потока ввода в свойство класса 'm_FIO'
    m_FIO = usersInputToFIO();
    std::cout << "Введите номер группы: ";
    m_groupID = userInputToInt();

    for (short i = 0; i < 5; i++)
    {
        std::cout << "Введите " << i + 1 << " оценку: ";
        m_est[i] = userInputToGrade();
    }
    std::cout << "Введите размер стипендии: ";
    m_grant = userInputToGrant();
}

bool StudentList::Student::emptyStudent() const { return (m_FIO.empty() && m_groupID == 0 && m_grant == 0) ? true : false; }

bool StudentList::Student::isExcellentStudent() const { return (m_est[0] == 5 && m_est[1] == 5 &&
                                                                m_est[2] == 5 && m_est[3] == 5 &&
                                                                m_est[4] == 5); }

void StudentList::Student::printStudentInfo() const
{
    std::cout << "ФИО: " << m_FIO << "\nНомер группы: " << m_groupID << '\n';
    std::cout << "Оценки за сессию: ";
    for (short i = 0; i < 5; i++)
        std::cout << m_est[i] << ' ';
    std::cout << "\nРазмер стипендии: " << m_grant << " руб.\n";
}

std::string StudentList::readFile(const std::string &fname) const
{
    // Инициализация входного/вводного (input) файлового потока
    std::ifstream ifs(fname);

    // Проверка состояния потока
    if (!ifs.good())
    {
        std::cerr << "readFile(): ifs.good(): Ошибка: Невозможно считать данные из файла " << fname
                  << ". Возвращается пустая строка\n";
        return "";
    }

    // Построчное чтение из файла
    std::string fileContent, line;
    while (std::getline(ifs, line, '\n'))
        fileContent += line + '\n';
    // Закрываем файловый поток ввода
    ifs.close();
    return fileContent;
}

bool StudentList::isFileContainsStudent(const std::string &fname, const Student &st) const
{
    std::string fileContent(readFile(fname));

    // Проверка, что метод "find()" класса "std::string" вернет не "std::string::npos", т.е.
    // максимальное значение размера строки, который возвращается в случае неудачного поиска
    return (fileContent.find(st.m_FIO) != std::string::npos &&
            fileContent.find("Номер группы: " + std::to_string(st.m_groupID)) != std::string::npos);
}

std::string StudentList::getStudentPropertyFromDB(const std::string &dbContent,
                                                  const std::string &prop,
                                                  const std::string &nextProp = "\n") const
{
    // Находим позиции начала и конца определенного свойства студента
    size_t pos1 = dbContent.find(prop) + prop.length(), pos2 = dbContent.find(nextProp);

    // Возвращаем подстроку
    return dbContent.substr(pos1, pos2 - pos1);
}

StudentList::StudentList() : m_head(nullptr), m_size(0) {}

StudentList::StudentList(const Student &st) : m_size(1) { m_head = new Student(st); }

StudentList::~StudentList()
{
    // Если переменная 'm_head' не равна "nullptr", то освобождаем выделенную память
    // и обнуляем указатель
    if (m_head)
    {
        delete m_head;
        m_head = nullptr;
    }
}

void StudentList::push_front()
{
    // Инициализация пользовательского студента
    Student newSt;
    newSt.createUsersStudent();

    // Инициализируем новый первый элемент списка пользователььским студентом
    Student *newHead = new Student(newSt);

    // Присваиваем указателю на следующий элемент первый элемент прошлого списка
    newHead->m_next = m_head;

    // Присваиваем указателю на первый элемент указатель на новый список элементов
    m_head = newHead;

    // Увеличиваем размер списка
    m_size++;
}

void StudentList::push_front(const Student &st)
{
    Student *newHead = new Student(st);
    newHead->m_next = m_head;
    m_head = newHead;
    m_size++;
}

void StudentList::push_back()
{
    Student newSt;
    newSt.createUsersStudent();

    // Если первый элемент нулевой - выделяем под него память и заполняем переданным объектом 'st',
    // используя копирующий конструктор внутренней структуры 'Student'
    if (!m_head)
        m_head = new Student(newSt);
    else
    {
        // Инициализируем новый указатель на текущего студента первым элементом списка студентов
        Student *curStudent = m_head;

        // До тех пор пока следующий элемент инициализированного
        // указателя не будет ссылаться на нулевой указатель
        while (curStudent->m_next)
            // Приравниваем указатель на следующий элемент к текущему
            curStudent = curStudent->m_next;
        // Используем копирующий конструктор для записи в элемент, ссылающийся на нулевой указатель
        curStudent->m_next = new Student(newSt);
    }
    // Инкрементируем размер списка после добавления
    m_size++;
}

void StudentList::push_back(const Student &st)
{
    if (!m_head)
        m_head = new Student(st);
    else
    {
        Student *curStudent = m_head;
        while (curStudent->m_next)
            curStudent = curStudent->m_next;
        curStudent->m_next = new Student(st);
    }
    m_size++;
}

void StudentList::push_back(const std::string &fio, int groupID, unsigned grades[5], double grant)
{
    Student newSt(fio, groupID, grades, grant);
    push_back(newSt);
}

void StudentList::insert(size_t index)
{
    if (index == 0)
        push_front();
    else
    {
        Student newSt;
        newSt.createUsersStudent();
        Student *pcur = m_head;
        for (size_t i = 0; i < index - 1; i++)
            pcur = pcur->m_next;
        pcur->m_next = new Student(pcur->m_next, newSt);
        m_size++;
    }
}

void StudentList::insert(const Student &st, size_t index)
{
    if (index == 0)
        push_front(st);
    else
    {
        Student *pcur = m_head;
        for (size_t i = 0; i < index - 1; i++)
            pcur = pcur->m_next;
        pcur->m_next = new Student(pcur->m_next, st);
        m_size++;
    }
}

void StudentList::remove(size_t index)
{
    // Если переданный индекс это 0 - удаляем первый элемент списка
    if (index == 0)
        pop_front();
    else
    {
        Student *pcur = m_head;
        // Итерация по элемента списка
        for (size_t i = 0; i < index - 1; i++)
            pcur = pcur->m_next;
        Student *pDel = pcur->m_next;
        pcur->m_next = pDel->m_next;

        delete pDel;
        pDel = nullptr;
        // Уменьшение размера списка после удаления элемента
        m_size--;
    }
}

void StudentList::removeByGroup(int groupID)
{
    size_t index = 0;
    // Не выходим за размеры списка
    while (index < m_size)
    {
        // Если нашли соответствие - удаляем
        if (at(index).m_groupID == groupID)
        {
            remove(index);
            // Обнуляем индекс после удаления, так как структура списка поменялась
            index = 0;
        }
        // В ином случае, идем дальше по списку
        else
            index++;
    }
}

void StudentList::pop_front()
{
    if (m_head)
    {
        Student *pcur = m_head;
        m_head = m_head->m_next;
        delete pcur;
        pcur = nullptr;
        m_size--;
    }
}

void StudentList::pop_back() { remove(m_size - 1); }

void StudentList::clear()
{
    // До тех пор пока переменная 'm_size' не станет равна 0
    while (m_size)
        remove(m_size - 1);
}

bool StudentList::empty() const { return (!m_head) ? true : false; }

size_t StudentList::size() const { return m_size; }

StudentList::Student &StudentList::at(size_t index)
{
    size_t counter = 0;
    Student *pcur = m_head;
    // Ищем до тех пор, пока указатель 'pcur' не станет указывать на "nullptr"
    while (pcur)
    {
        // Если нашли студента с таким индексом - возвращаем его
        if (counter == index)
            return *pcur;

        // Перемещаемся по списку студентов
        pcur = pcur->m_next;
        counter++;
    }
    throw std::out_of_range("out_of_range: at(): Вы ввели недоступный индекс студента. Такого студента нет\n");
}

const StudentList::Student &StudentList::at(size_t index) const
{
    size_t counter = 0;
    Student *pcur = m_head;
    // Ищем до тех пор, пока указатель 'pcur' не станет указывать на "nullptr"
    while (pcur)
    {
        // Если нашли студента с таким индексом - возвращаем его
        if (counter == index)
            return *pcur;

        // Перемещаемся по списку студентов
        pcur = pcur->m_next;
        counter++;
    }
    throw std::out_of_range("out_of_range: at(): Вы ввели недоступный индекс студента. Такого студента нет\n");
}

StudentList::Student &StudentList::operator[](size_t index) { return at(index); }

const StudentList::Student &StudentList::operator[](size_t index) const { return at(index); }

StudentList::Student &StudentList::front() const { return *m_head; }

StudentList::Student &StudentList::back() const { return m_head[m_size - 1]; }

void StudentList::change(size_t index)
{
    Student newSt;
    newSt.createUsersStudent();
    remove(index);
    insert(newSt, index);
}

void StudentList::change(size_t index, const Student &st)
{
    remove(index);
    insert(st, index);
}

std::ostream &operator<<(std::ostream &os, const StudentList::Student &st)
{
    os << "ФИО: " << st.m_FIO << "\nНомер группы: " << st.m_groupID << '\n';
    os << "Оценки за сессию: ";
    for (short i = 0; i < 5; i++)
        os << st.m_est[i] << ' ';
    os << "\nРазмер стипендии: " << st.m_grant << " руб.\n\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const StudentList &stList)
{
    for (size_t i = 0; i < stList.size(); i++)
    {
        os << "ФИО: " << stList[i].m_FIO << "\nНомер группы: " << stList[i].m_groupID << '\n';
        os << "Оценки за сессию: ";
        for (short j = 0; j < 5; j++)
            os << stList[i].m_est[j] << ' ';
        os << "\nРазмер стипендии: " << stList[i].m_grant << " руб.\n\n";
    }
    return os;
}

bool operator==(const StudentList::Student &st1, const StudentList::Student &st2)
{
    bool flag = (st1.m_FIO == st2.m_FIO && st1.m_groupID == st2.m_groupID &&
                 st1.m_grant == st2.m_grant);
    bool gradesFlag = true;
    for (short i = 0; i < 5; i++)
        if (st1.m_est[i] != st2.m_est[i])
        {
            gradesFlag = false;
            break;
        }
    return flag && gradesFlag;
}

void StudentList::print() const
{
    // Если первый элемент списка ссылается на "nullptr" - значит список пуст
    if (!m_head)
    {
        std::cout << "Список студентов пуст\n";
        return;
    }
    else
    {
        // Вывод в консоль всех элементов, начиная с первого
        Student *pcur = m_head;
        while (pcur)
        {
            pcur->printStudentInfo();
            pcur = pcur->m_next;
            std::cout << '\n';
        }
    }
}

void StudentList::print(size_t index) const
{
    if (index > m_size - 1)
    {
        std::cerr << "print(size_t): Вы ввели недопустимый индекс студента. Такого студента нет\n";
        return;
    }
    m_head[index].printStudentInfo();
}

void StudentList::writeStudentToFile(const Student &st, const std::string &fname) const
{
    if (isFileContainsStudent(fname, st))
    {
        std::cout << "Запись не произведена. Причина: Студент из группы " << st.m_groupID
                  << " с ФИО \"" << st.m_FIO << "\" уже есть в базе данных\n";
    }
    else
    {
        // Инициализация файлового потока вывода с режимом добавления - "std::ios_base::app" - append
        std::ofstream ofs(fname, std::ios_base::app);

        if (!ofs.good())
        {
            std::cerr << "writeStudentToFile(): ofs.good(): Ошибка: Невозможно записать данные в файл " << fname << '\n';
            return;
        }

        ofs << "ФИО: " << st.m_FIO << "\nНомер группы: " << st.m_groupID << '\n';
        ofs << "Оценки за сессию: ";
        for (short i = 0; i < 5; i++)
            ofs << st.m_est[i] << ' ';
        ofs << "\nРазмер стипендии: " << st.m_grant << " руб.\n\n";
        std::cout << "Данные о студенте из группы " << st.m_groupID << " с ФИО \""
                  << st.m_FIO << "\" были успешно записаны в файл " << fname << '\n';
        ofs.close();
    }
}

void StudentList::writeStudentsListToFile(const std::string &fname) const
{
    // Инициализация указателя первым элементом списка студентов
    Student *pcur = m_head;
    while (pcur)
    {
        // Производим запись
        writeStudentToFile(*pcur, fname);

        // Перемещаемся к следующему студенту для последующей записи
        pcur = pcur->m_next;
    }
}

void StudentList::readStudentsDB(const std::string &fname) const
{
    if (readFile(fname).empty())
        std::cout << "Файл базы данных пуст\n";
    else
        std::cout << readFile(fname);
}

int StudentList::countOfGroups() const
{
    int counter = 0;
    for (size_t i = 0; i < m_size; i++)
    {
        size_t j = 0;
        for (; j < i; j++)
            if (at(i).m_groupID == at(j).m_groupID)
                break;

        if (i == j)
            counter++;
    }
    return counter;
}

int StudentList::countOfStudentInGroup(int groupID) const
{
    // Если список студентов пуст, то и групп в нем нет
    if (empty())
        return 0;

    int count = 0;
    for (size_t i = 0; i < m_size; i++)
    {
        if (at(i).m_groupID == groupID)
            count++;
    }
    return count;
}

int StudentList::countOfExcellentStudentInGroup(int groupID) const
{
    // Если список студентов пуст, то и групп в нем нет
    if (empty())
        return 0;

    int count = 0;
    for (size_t i = 0; i < m_size; i++)
    {
        if (at(i).m_groupID == groupID && at(i).isExcellentStudent())
            count++;
    }
    return count;
}

void StudentList::calcExcellentStudentsPercent() const
{
    for (size_t i = 0; i < m_size; i++)
    {
        size_t j = 0;
        for (; j < i; j++)
            if (at(i).m_groupID == at(j).m_groupID)
                break;

        if (i == j)
            std::cout << "Процент отличников в группе " << at(i).m_groupID
                      << " = "
                      << static_cast<double>(countOfExcellentStudentInGroup(at(i).m_groupID)) /
                             countOfStudentInGroup(at(i).m_groupID) * 100
                      << "%\n";
    }
}

void StudentList::removeStudentFromDB(const std::string &fname, const Student &st)
{
    // Считываем все из файла базы данных в строку
    std::string dbContent(readFile(fname));

    std::string grades;
    for (short i = 0; i < 5; i++)
        grades += std::to_string(st.m_est[i]) + ' ';

    // Удаляем завершеющие нули у стипендии
    std::string grant = std::to_string(st.m_grant);
    grant.erase(grant.find_last_not_of('0') + 1, std::string::npos);
    grant.erase(grant.find_last_not_of('.') + 1, std::string::npos);

    // Инициализируем строку, содержащую информацию об определенном студенте
    std::string toDelete("ФИО: " + st.m_FIO + "\nНомер группы: " +
                         std::to_string(st.m_groupID) +
                         "\nОценки за сессию: " +
                         grades +
                         "\nРазмер стипендии: " + grant +
                         " руб.\n\n");
    // Проверка, что метод "find()" не возвращает "std::string::pos",
    // чтобы удалить ее из 'dbContent'
    if (dbContent.find(toDelete) != std::string::npos)
        dbContent.erase(dbContent.find(toDelete), toDelete.length());

    std::ofstream ofs(fname);
    if (!ofs.good())
    {
        std::cerr << "removeStudentFromDB(): ofs.good(): Ошибка: Невозможно считать данные из файла " << fname << '\n';
        return;
    }
    ofs << dbContent;
    ofs.close();
}

void StudentList::readDBToThisObj(const std::string &fname)
{
    // Считываем все из файла в строку
    std::string dbContent(readFile(fname));

    // До тех пор, пока не опустошим строку
    while (!dbContent.empty())
    {
        // Инициализируем объект студента и записываем в него все необходимые данные
        Student st;
        st.m_FIO = getStudentPropertyFromDB(dbContent, "ФИО: ");
        st.m_groupID = std::stoi(getStudentPropertyFromDB(dbContent, "Номер группы: ", "\nОценки за сессию: "));
        for (short i = 0; i < 5; i++)
        {
            st.m_est[i] = std::stoul(
                getStudentPropertyFromDB(dbContent, "Оценки за сессию: ", "\nРазмер стипендии: ").substr(i * 2, 1));
        }
        st.m_grant = std::stod(getStudentPropertyFromDB(dbContent, "Размер стипендии: ", " руб."));

        // Записываем полученные данные в конец списка
        this->push_back(st);

        // Инициализируем строку, содержащую информацию об определенном студенте
        std::string toDelete("ФИО: " + getStudentPropertyFromDB(dbContent, "ФИО: ") + "\nНомер группы: " +
                             getStudentPropertyFromDB(dbContent, "Номер группы: ", "\nОценки за сессию: ") +
                             "\nОценки за сессию: " +
                             getStudentPropertyFromDB(dbContent, "Оценки за сессию: ", "\nРазмер стипендии: ") +
                             "\nРазмер стипендии: " + getStudentPropertyFromDB(dbContent, "Размер стипендии: ", " руб.") +
                             " руб.\n\n");
        // Проверка, что метод "find()" не возвращает "std::string::pos",
        // чтобы удалить ее из 'dbContent'
        if (dbContent.find(toDelete) != std::string::npos)
            dbContent.erase(dbContent.find(toDelete), toDelete.length());
    }
}
