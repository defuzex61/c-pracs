// Компиляция и запуск: clang++ main.cpp -o main
//./main


#include <iostream>
#include <string>

using namespace std;

class Employee {// Сотрудник
private:
    // Информационные свойства
    string organization;
    string position;
    double experience;

    // Личные данные
    string name;
    char gender;   // Пол, 'M' или 'F'
    int age;

    double salary;   // накопленная зарплата

    // Статическое свойство
    static int count;

public:
    // Конструктор
    Employee(string org, string pos, double exp,
             string n, char g, int a, double s = 0.0)
        : organization(org), position(pos), experience(exp),
          name(n), gender(g), age(a), salary(s)
    {
        count++;   // увеличиваем количество сотрудников
    }

    // Конструктор копирования
    Employee(const Employee& other)
        : organization(other.organization),
          position(other.position),
          experience(other.experience),
          name(other.name),
          gender(other.gender),
          age(other.age),
          salary(other.salary)
    {
        count++;
    }

    // Деструктор
    ~Employee() {
        count--;   // уменьшаем количество сотрудников
    }

    // Получение информации
    string getOrganization() const { return organization; }
    string getPosition() const { return position; }
    double getExperience() const { return experience; }
    double getSalary() const { return salary; }

    // Изменение должности
    void changePosition(const string& newPos) {
        position = newPos;
    }

    // Начисление зарплаты
    void addSalary(double amount) {
        if (amount > 0)
            salary += amount;
    }

    // Вывод личных данных
    void showPersonalData() const {
        cout << "ФИО: " << name << endl;
        cout << "Пол: " << (gender == 'M' ? "М" : "Ж") << endl;
        cout << "Возраст: " << age << endl;
    }

    // Вывод всей информации о сотруднике
    void showInfo() const {
        cout << "-------------------------" << endl;
        showPersonalData();
        cout << "Место работы: " << organization << endl;
        cout << "Должность: " << position << endl;
        cout << "Стаж: " << experience << " лет" << endl;
        cout << "Зарплата (накоплено): " << salary << endl;
    }

    // Перегрузка оператора присваивания
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            organization = other.organization;
            position = other.position;
            experience = other.experience;
            name = other.name;
            gender = other.gender;
            age = other.age;
            salary = other.salary;
        }
        return *this;
    }

    // Перегрузка оператора сравнения (по зарплате)
    bool operator>(const Employee& other) const {
        return salary > other.salary;
    }

    bool operator<(const Employee& other) const {
        return salary < other.salary;
    }

    bool operator==(const Employee& other) const {
        return salary == other.salary;
    }

    // Статический метод
    static int getCount() {
        return count;
    }
};

// Инициализация статического свойства
int Employee::count = 0;

int main() {
    cout << "Количество сотрудников в начале: "
         << Employee::getCount() << endl;

    // Создаем массив сотрудников (3 человека)
    Employee staff[3] = {
        Employee("Google", "Programmer", 3.5, "Иванов Иван", 'M', 25),
        Employee("Apple", "Designer", 5.0, "Петрова Анна", 'F', 30),
        Employee("Microsoft", "Manager", 7.2, "Сидоров Олег", 'M', 40)
    };

    cout << "\nКоличество сотрудников после создания массива: "
         << Employee::getCount() << endl;

    // Начисляем зарплату
    staff[0].addSalary(50000);
    staff[1].addSalary(70000);
    staff[2].addSalary(60000);

    // Меняем должность первому сотруднику
    staff[0].changePosition("Senior Programmer");

    // Вывод информации о каждом сотруднике
    for (int i = 0; i < 3; i++) {
        staff[i].showInfo();
    }

    // Пример сравнения сотрудников
    cout << "\nСравнение зарплат:\n";
    if (staff[1] > staff[0])
        cout << "У второго сотрудника зарплата больше, чем у первого\n";

    if (staff[2] < staff[1])
        cout << "У третьего сотрудника зарплата меньше, чем у второго\n";

    cout << "\nТекущее количество сотрудников: "
         << Employee::getCount() << endl;

    return 0;
}
