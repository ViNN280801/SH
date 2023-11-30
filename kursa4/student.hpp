#ifndef STUDENT_HPP // -> header guard, позволяет избежать вторичного подключения
#define STUDENT_HPP // данного заголовочного файла

#include <string>

// Класс 'StudentList' - это обертка для внутренней структуры 'Student' функционирует как
// динамический массив с возможностью добавлять в начало и конец массива, производить поиск
// с помощью оператора[], удалять элементы, осуществять проверку на пустой массив и прочее.
// Существует возможность создания базы данных, используя встроенные функции работы с файлами
class StudentList
{
private:
    // Структура характеризует объект студента со скрытой реализацией. Имеет свойства:
    // ФИО, номер группы, 5 оценок за сессию и размер стипендии
    // Использует правило трех: https://en.cppreference.com/w/cpp/language/rule_of_three
    struct Student;

    Student *m_head; // Указатель на первый элемент списка
    size_t m_size;   // Размер списка

    // Считывает файл в строку и возвращает ее
    std::string readFile(const std::string &) const;

    // Проверяет существует ли уже в файле указанный студент
    bool isFileContainsStudent(const std::string &, const Student &) const;

    // Считывает определенное свойство студента, указанное в качестве строки и возвращает его
    std::string getStudentPropertyFromDB(const std::string &, const std::string &, const std::string &) const;

public:
    // Конструктор по умолчанию
    explicit StudentList();

    // Конструктор, инициализирующий первый элемент указателя 'm_students' переданным объектом
    explicit StudentList(const Student &);

    // Деструктор
    virtual ~StudentList();

    // Добавляет пользовательского студента (данные вводит пользователь) в начало списка
    void push_front();

    // Добавляет переданного в качестве параметра студента в начало списка
    void push_front(const Student &);

    // Добавляет пользовательского студента (данные вводит пользователь) в конец списка
    void push_back();

    // Добавляет переданного в качестве параметра студента в конец списка
    void push_back(const Student &);

    // Добавляет в конец вручную созданного пользователя (для тестов)
    void push_back(const std::string &, int, unsigned[5], double);

    // Добавляет пользовательского студента (данные вводит пользователь) в указанную позицию
    void insert(size_t);

    // Добавляет указанного студента в указанную позицию
    void insert(const Student &st, size_t index);

    // Удаляет указанный элемент списка
    void remove(size_t);

    // Удаляет всех студентов с указанной группой
    void removeByGroup(int);

    // Удаляет первый элемент списка
    void pop_front();

    // Удаляет последний элемент списка
    void pop_back();

    // Полностью очищает список элементов
    void clear();

    // Проверяет является ли пустым список студентов. Если является, то возвращает "true"
    bool empty() const;

    // Возвращает размер списка студентов
    size_t size() const;

    // Ищет и возвращает данные о студенте с указанным индексом. В случае неудачи выбрасывает исключение
    Student &at(size_t);

    // Ищет и возвращает данные о студенте с указанным индексом. В случае неудачи выбрасывает исключение
    const Student &at(size_t) const;

    // Перегрузка оператора индексации. Возвращает студента под определенным индексом
    // Выбрасывает исключение, если индекс неверный
    Student &operator[](size_t);

    // Перегрузка оператора индексации. Возвращает студента под определенным индексом
    // Выбрасывает исключение, если индекс неверный
    const Student &operator[](size_t) const;

    // Возвращает первый элемент списка
    Student &front() const;

    // Возвращает последний элемент списка
    Student &back() const;

    // Изменяет данные об указанном студенте пользовательскими данными
    void change(size_t);

    // Изменяет данные об указанном студенте переданными данными
    void change(size_t, const Student &);

    // Перегруженный оператор вывода. Выводит определенного студента
    friend std::ostream &operator<<(std::ostream &, const Student &);

    // Перегруженный оператор вывода. Выводит всех студентов
    friend std::ostream &operator<<(std::ostream &, const StudentList &);

    // Перегруженный оператор сравнения
    friend bool operator==(const Student &, const Student &);

    // Выводит весь список студентов
    void print() const;

    // Выводит информацию о конкретном студенте
    void print(size_t) const;

    // Записывает информацию об указанном студенте в указанный файл. Встроена проверка на наличие студентов в файле
    void writeStudentToFile(const Student &, const std::string &) const;

    // Записывает информацию о всех студентах в указанный файл. Встроена проверка на наличие студентов в файле
    void writeStudentsListToFile(const std::string &) const;

    // Выводит базу данных из указанного файла
    void readStudentsDB(const std::string &) const;

    // Считает и возвращает количество разных групп
    int countOfGroups() const;

    // Считает и возвращает количество студентов в указанной группе
    int countOfStudentInGroup(int groupID) const;

    // Считает и возвращает количество отличников в указанной группе
    int countOfExcellentStudentInGroup(int groupID) const;

    // Рассчитывает процент отличников для каждой из групп
    void calcExcellentStudentsPercent() const;

    // Удаляет студента из базы данных
    void removeStudentFromDB(const std::string &, const Student &);

    // Считывает данные из указанного файла базы данных в конец текующего объекта
    void readDBToThisObj(const std::string &);
};

#endif // STUDENT_HPP
