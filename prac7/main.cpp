//Компиляция и запуск: clang++ -std=c++17 main.cpp -o main
//./main

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Родительский класс: Animal
class Animal {
protected:                 // инкапсуляция
    string name;
    int age;

public:
    Animal(string n, int a) : name(n), age(a) {}
    virtual ~Animal() {}

    // геттеры и сеттеры
    string getName() const { return name; }
    int getAge() const { return age; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }

    // абстрактные (виртуальные) методы
    virtual void makeSound() const = 0;
    virtual void displayInfo() const = 0;
    virtual string getType() const = 0;
};


class Dog : public Animal {//Наследник: Dog
    string breed;

public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {}

    void makeSound() const override {
        cout << name << " говорит: Гав-гав!" << endl;
    }

    void displayInfo() const override {
        cout << "Тип: Собака | Имя: " << name << " | Возраст: " << age
             << " | Порода: " << breed << endl;
    }

    string getType() const override { return "Dog"; }
};


class Cat : public Animal {//Наследник: Cat
    string color;

public:
    Cat(string n, int a, string c) : Animal(n, a), color(c) {}

    void makeSound() const override {
        cout << name << " говорит: Мяу!" << endl;
    }

    void displayInfo() const override {
        cout << "Тип: Кошка | Имя: " << name << " | Возраст: " << age
             << " | Окрас: " << color << endl;
    }

    string getType() const override { return "Cat"; }
};


class Bird : public Animal {//Наследник: Bird
    bool canFly;

public:
    Bird(string n, int a, bool f) : Animal(n, a), canFly(f) {}

    void makeSound() const override {
        cout << name << " говорит: Чирик-чирик!" << endl;
    }

    void displayInfo() const override {
        cout << "Тип: Птица | Имя: " << name << " | Возраст: " << age
             << " | Умеет летать: " << (canFly ? "Да" : "Нет") << endl;
    }

    string getType() const override { return "Bird"; }
};


void showMenu() { // Меню
    cout << "\n - МЕНЮ ПИТОМЦЕВ - \n";
    cout << "1. Добавить питомца\n";
    cout << "2. Показать всех питомцев\n";
    cout << "3. Заставить всех говорить\n";
    cout << "4. Найти питомца по имени\n";
    cout << "5. Показать статистику по типам\n";
    cout << "0. Выход\n";
    cout << "Выбор: ";
}

int main() {
    vector<Animal*> pets;   // реализуем полиморфизм: храним разных животных через Animal*

    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            int type;
            cout << "Выберите тип (1-Собака, 2-Кошка, 3-Птица): ";
            cin >> type;

            string name;
            int age;
            cout << "Имя: ";
            cin >> name;
            cout << "Возраст: ";
            cin >> age;

            if (type == 1) {
                string breed;
                cout << "Порода: ";
                cin >> breed;
                pets.push_back(new Dog(name, age, breed));
            }
            else if (type == 2) {
                string color;
                cout << "Окрас: ";
                cin >> color;
                pets.push_back(new Cat(name, age, color));
            }
            else if (type == 3) {
                int f;
                cout << "Умеет летать? (1-да, 0-нет): ";
                cin >> f;
                pets.push_back(new Bird(name, age, f));
            }

            cout << "Питомец добавлен!\n";
        }

        else if (choice == 2) {
            cout << "\n - ВСЕ ПИТОМЦЫ - \n";
            for (auto p : pets)
                p->displayInfo();
        }

        else if (choice == 3) {
            cout << "\n - ПИТОМЦЫ ГОВОРЯТ - \n";
            for (auto p : pets)
                p->makeSound();
        }

        else if (choice == 4) {
            string search;
            cout << "Введите имя для поиска: ";
            cin >> search;

            bool found = false;
            for (auto p : pets) {
                if (p->getName() == search) {
                    p->displayInfo();
                    found = true;
                }
            }

            if (!found)
                cout << "Питомец не найден.\n";
        }

        else if (choice == 5) {
            int dogs = 0, cats = 0, birds = 0;

            for (auto p : pets) {
                if (p->getType() == "Dog") dogs++;
                else if (p->getType() == "Cat") cats++;
                else if (p->getType() == "Bird") birds++;
            }

            cout << "\- СТАТИСТИКА - \n";
            cout << "Собак: " << dogs << endl;
            cout << "Кошек: " << cats << endl;
            cout << "Птиц: " << birds << endl;
        }

    } while (choice != 0);

    // очистка памяти
    for (auto p : pets)
        delete p;

    return 0;
}
