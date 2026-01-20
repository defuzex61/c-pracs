// Компиляция и запуск: clang++ -std=c++17 main.cpp -o main
//./main
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Базовый класс книги
class book {
protected:
    string title;
    vector<string> authors;
    unsigned int year;
    string publisher;
    unsigned int pages;

public:
    book() {}

    book(string t, vector<string> a, unsigned int y, string p, unsigned int pg) {
        title = t;
        authors = a;
        year = y;
        publisher = p;
        pages = pg;
    }

    string getTitle() const { return title; }
    vector<string> getAuthors() const { return authors; }

    virtual void show() const {
        cout << "Название: " << title << endl;
        cout << "Авторы: ";
        for (auto& a : authors) cout << a << " ";
        cout << endl;
        cout << "Год издания: " << year << endl;
        cout << "Издательство: " << publisher << endl;
        cout << "Страниц: " << pages << endl;
    }
};

// Структура читателя
struct reader {
    string name;
    string date;
};

// Класс книги каталога наследуемый от базового класса книги
class catalog_book : public book {
private:
    unsigned int id;
    unsigned int quantity;
    unsigned int instances;
    vector<reader> picked;

public:
    catalog_book(unsigned int _id, string t, vector<string> a,
        unsigned int y, string p, unsigned int pg,
        unsigned int q)
        : book(t, a, y, p, pg) {

        id = _id;
        quantity = q;
        instances = q;
    }

    unsigned int getID() const { return id; }

    void showFull() const {
        show();
        cout << "ID: " << id << endl;
        cout << "Всего экземпляров: " << quantity << endl;
        cout << "В наличии: " << instances << endl;

        if (!picked.empty()) {
            cout << "Взяли книгу:" << endl;
            for (auto& r : picked) {
                cout << "  " << r.name << " | дата: " << r.date << endl;
            }
        }
        else {
            cout << "Книгу никто не взял." << endl;
        }
    }

    // Выдача книги
    bool giveBook(string name, string date) {
        if (instances == 0) return false;

        reader r;
        r.name = name;
        r.date = date;
        picked.push_back(r);
        instances--;
        return true;
    }

    // Возврат книги
    bool returnBook(string name) {
        for (size_t i = 0; i < picked.size(); i++) {
            if (picked[i].name == name) {
                picked.erase(picked.begin() + i);
                instances++;
                return true;
            }
        }
        return false;
    }

    // Проверка авторов
    bool hasAuthor(string a) const {
        for (auto& x : authors)
            if (x == a) return true;
        return false;
    }

    vector<reader> getReaders() const {
        return picked;
    }
};

// Меню
void menu() {
    cout << "\n===== БИБЛИОТЕЧНЫЙ КАТАЛОГ =====\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Удалить книгу\n";
    cout << "3. Показать книгу по ID\n";
    cout << "4. Поиск книги по названию\n";
    cout << "5. Поиск книги по автору\n";
    cout << "6. Выдать книгу читателю\n";
    cout << "7. Вернуть книгу читателем\n";
    cout << "8. Список читателей, не вернувших книги более года\n";
    cout << "0. Выход\n";
}


//Входная точка программы
int main() {
    vector<catalog_book> catalog;
    int choice;

    do {
        menu();
        cout << "Выберите пункт: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) { // Добавить книгу
            unsigned int id, year, pages, qty;
            string title, publisher;
            int countAuthors;

            cout << "ID: ";
            cin >> id;
            cin.ignore();

            cout << "Название: ";
            getline(cin, title);

            cout << "Количество авторов: ";
            cin >> countAuthors;
            cin.ignore();

            vector<string> authors;
            for (int i = 0; i < countAuthors; i++) {
                string a;
                cout << "Автор " << i + 1 << ": ";
                getline(cin, a);
                authors.push_back(a);
            }

            cout << "Год издания: ";
            cin >> year;
            cin.ignore();

            cout << "Издательство: ";
            getline(cin, publisher);

            cout << "Количество страниц: ";
            cin >> pages;

            cout << "Количество экземпляров: ";
            cin >> qty;

            catalog.emplace_back(id, title, authors, year, publisher, pages, qty);
            cout << "Книга добавлена.\n";
        }

        else if (choice == 2) { // Удалить книгу
            unsigned int id;
            cout << "Введите ID: ";
            cin >> id;

            auto it = remove_if(catalog.begin(), catalog.end(),
                [id](catalog_book& b) { return b.getID() == id; });

            if (it != catalog.end()) {
                catalog.erase(it, catalog.end());
                cout << "Книга удалена.\n";
            }
            else {
                cout << "Книга не найдена.\n";
            }
        }

        else if (choice == 3) { // Показать по ID
            unsigned int id;
            cout << "Введите ID: ";
            cin >> id;

            bool found = false;
            for (auto& b : catalog) {
                if (b.getID() == id) {
                    b.showFull();
                    found = true;
                }
            }
            if (!found) cout << "Книга не найдена.\n";
        }

        else if (choice == 4) { // Поиск по названию
            string name;
            cin.ignore();
            cout << "Введите название: ";
            getline(cin, name);

            for (auto& b : catalog) {
                if (b.getTitle() == name) {
                    cout << "Найдена книга, ID = " << b.getID() << endl;
                }
            }
        }

        else if (choice == 5) { // Поиск по автору
            string author;
            cin.ignore();
            cout << "Введите автора: ";
            getline(cin, author);

            for (auto& b : catalog) {
                if (b.hasAuthor(author)) {
                    cout << "Найдена книга, ID = " << b.getID() << endl;
                }
            }
        }

        else if (choice == 6) { // Выдать книгу
            unsigned int id;
            string name, date;

            cout << "ID книги: ";
            cin >> id;
            cin.ignore();

            cout << "Имя читателя: ";
            getline(cin, name);

            cout << "Дата выдачи (дд.мм.гггг): ";
            getline(cin, date);

            bool done = false;
            for (auto& b : catalog) {
                if (b.getID() == id) {
                    if (b.giveBook(name, date))
                        cout << "Книга выдана.\n";
                    else
                        cout << "Нет экземпляров в наличии.\n";
                    done = true;
                }
            }
            if (!done) cout << "Книга не найдена.\n";
        }

        else if (choice == 7) { // Вернуть книгу
            unsigned int id;
            string name;

            cout << "ID книги: ";
            cin >> id;
            cin.ignore();

            cout << "Имя читателя: ";
            getline(cin, name);

            bool done = false;
            for (auto& b : catalog) {
                if (b.getID() == id) {
                    if (b.returnBook(name))
                        cout << "Книга возвращена.\n";
                    else
                        cout << "Этот читатель не найден.\n";
                    done = true;
                }
            }
            if (!done) cout << "Книга не найдена.\n";
        }

        else if (choice == 8) { // Должники (Все взявшие) 
            cout << "Читатели, не вернувшие книги (список всех взявших):\n";

            for (auto& b : catalog) {
                auto r = b.getReaders();
                for (auto& x : r) {
                    cout << x.name << " | дата: " << x.date << endl;
                }
            }
        }

    } while (choice != 0);

    return 0;
}
