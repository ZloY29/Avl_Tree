#include "avl_tree.h"
#include "book.h"
#include "marsh.h"
#include "correct_input.h"
#include "correct_input.cpp"
#include <algorithm>
#include <fstream>

//вывод книг с заданным именем автора
void print_name_author(node<book>* pos, std::string autr, bool& flag) {
    if (pos == 0)
        return;
    print_name_author(pos->get_left(), autr, flag);
    if (pos->data.get_author() == autr) {
        cout << pos->data << "\n";
        flag = false;
    }
    print_name_author(pos->get_right(), autr, flag);
}

//общая стоимость всех книг
void sum_price(node<book>* pos, double& cost) {
    if (pos == 0)
        return;
    sum_price(pos->get_left(), cost);
    cost += pos->data.get_cost();
    sum_price(pos->get_right(), cost);
}

//вывод книг с ценой выше средней
void print_above_avg_price(node<book>* pos, double avg) {
    if (pos == 0)
        return;
    print_above_avg_price(pos->get_left(), avg);
    if (pos->data.get_cost() > avg)
        cout << pos->data << "\n";
    print_above_avg_price(pos->get_right(), avg);
}

//поиск книги по названию
void find_book_to_name(node<book>* pos, string name, book& my_book) {
    if (pos == 0)
        return;
    find_book_to_name(pos->get_left(), name, my_book);
    if (pos->data.get_name() == name)
        my_book = pos->data;
    find_book_to_name(pos->get_right(), name, my_book);
}

//изменение данных о книге
void change_data(book& my_book) {
    cout << "1.Изменить название.\n";
    cout << "2.Изменить автора.\n";
    cout << "3.Изменть стоимость.\n";
    unsigned int num;
    cin >> num;
    switch (num)
    {
        case 1:
        {
            cout << "Введите новое название книги:\n";
            string new_name;
            cin >> new_name;
            my_book.set_name(new_name);
            return;
        }
        case 2:
        {
            cout << "Введите новое имя автора книги:\n";
            string new_author;
            cin >> new_author;
            my_book.set_author(new_author);
            return;
        }
        case 3:
        {
            cout << "Введите новую стоимость книги:\n";
            double new_cost;
            cin >> new_cost;
            my_book.set_cost(new_cost);
            return;
        }
    }
}


void print_menu() {
    cout << "1.Построение дерева поиска по данным, введенным с клавиатуры (добавление в дерево списка вершин в указанном порядке).\n";
    cout << "2.Построение дерева поиска по данным из файла.\n";
    cout << "3.Печать дерева.\n";
    cout << "4.Добавление еще одного узла к дереву.\n";
    cout << "5.Удаление узла.\n";
    cout << "6.Поиск узла.\n";
    cout << "7.Изменение информации о выбранном объекте.\n";
    cout << "8.Вывод на экран информации о книгах автора К.\n";
    cout << "9.Вывод на экран информации о книгах, с ценой выше средней.\n";
    cout << "10.Выход.\n";
    cout << "Выберите действие.\n";
}


int main() {
    setlocale(0, "RUS");
    ifstream in("file.txt");
    balanced_tree<book> books;
    book my_book;
    string author, name;
    int num_books;
    double price = 0;
    int cmp;
    do
    {
        print_menu();
        correct_input_cmp(cmp);
        switch (cmp)
        {
            case 1:
            {
                cout << "Введите кол-во книг:\n";
                correct_input_N(num_books);
                cout << "Введите книги:\n";
                for (int i = 0; i < num_books; i++) {
                    cout << "Введите название, автора, стоимость!\n";
                    cin >> my_book;
                    books.insert(my_book);
                }
                break;
            }
            case 2:
            {
                in >> num_books;
                for (int i = 0; i < num_books; i++) {
                    in >> my_book;
                    books.insert(my_book);
                }
                in.close();
                cout << "Данные из файла успешно загружены!\n";
                break;
            }
            case 3:
            {
                if (books.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    system("pause");
                    break;
                }
                books.print();
                break;
            }
            case 4:
            {
                cout << "Введите данные о книге:\n";
                cout << "Введите название, автора, стоимость!\n";
                cin >> my_book;
                books.insert(my_book);
                cout << "Книга успешно добавлена!\n";
                break;
            }
            case 5:
            {
                if (books.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    system("pause");
                    break;
                }
                cout << "Введите название книги, которую требуется удалить:\n";
                cin >> name;
                my_book = book();
                find_book_to_name(books.get_root(), name, my_book);
                if (books.find(my_book) == 0) {
                    cout << "Книга отсутствует!\n";
                    system("pause");
                    break;
                }
                books.remove(my_book);
                cout << "Книга успешно удалена!\n";
                break;
            }
            case 6:
            {
                if (books.is_empty()) {
                    cout << "В дереве нет элементов!";
                    system("pause");
                    break;
                }
                cout << "Введите название, автора, стоимость!\n";
                cin >> my_book;
                books.insert(my_book);
                if (books.find(my_book) == 0)
                    cout << "Книга отсутствует!\n";
                else
                    cout << "Книга найдена!";
                break;
            }
            case 7:
            {
                if (books.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    system("pause");
                    break;
                }
                cout << "Введите название книги, которую хотите изменить:\n";
                cin >> name;
                my_book = book();
                find_book_to_name(books.get_root(), name, my_book);
                if (books.find(my_book) == 0) {
                    cout << "Книга отсутствует!\n";
                    break;
                }
                else {
                    book temp = my_book;
                    books.remove(my_book);
                    change_data(temp);
                    books.insert(temp);
                }
                break;
            }
            case 8:
            {
                if (books.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    break;
                }
                cout << "Введите автора, и мы выведем всю информацию о его книгах:\n";
                bool is_empty = true;
                cin >> author;
                print_name_author(books.get_root(), author, is_empty);
                if (is_empty)
                    cout << "Книг с таким автором не найдено!";
                break;
            }
            case 9:
            {
                if (books.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    break;
                }
                sum_price(books.get_root(), price);
                print_above_avg_price(books.get_root(), price / num_books);
                break;
            }
        }
    } while (cmp != 10);
    return 0;
}