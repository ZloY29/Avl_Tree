#include "avl_tree.h"
#include "marsh.h"
#include "correct_input.h"
#include "correct_input.cpp"
#include <algorithm>
#include <fstream>

using namespace std;

// Вывод маршрутов следующего в пункт К
void print_curr_marsh(node<marsh>* pos, string end_point, bool& flag) {
    if (pos == 0)
        return;
    print_curr_marsh(pos->get_left(), end_point, flag);
    if (pos->data.get_end_point() == end_point) {
        cout << pos->data << "\n";
        flag = false;
    }
    print_curr_marsh(pos->get_right(), end_point, flag);
}

// Вывод маршрутов с временем отправления после времени К и следующих из пункта М
void print_remaining_marsh(node<marsh>* pos, string departure_time, string start_point, bool& flag) {
    if (pos == 0)
        return;
    else {
        int time_in_sec;
        string hour = "";
        string minute = "";
        hour += departure_time[0];
        hour += departure_time[1];
        minute += departure_time[3];
        minute += departure_time[4];
        time_in_sec = (stoi(hour)*3600 + stoi(minute)*60);
        print_remaining_marsh(pos->get_left(), departure_time, start_point, flag);
        if ((pos->data.get_depart_in_sec() > time_in_sec) && (pos->data.get_start_point() == start_point)) {
            cout << pos->data << "\n";
            flag = false;
        }
        print_remaining_marsh(pos->get_right(), departure_time, start_point, flag);
    }
}

// Поиск маршрута по номеру
void find_marsh_to_number(node<marsh>* pos, int number, marsh& my_marsh) {
    if (pos == 0)
        return;
    find_marsh_to_number(pos->get_left(), number, my_marsh);
    if (pos->data.get_route_number() == number)
        my_marsh = pos->data;
    find_marsh_to_number(pos->get_right(), number, my_marsh);
}

//изменение данных о книге
void change_data(marsh& my_marsh) {
    cout << "1.Изменить номер маршрута\n";
    cout << "2.Изменить название начального пункта маршрута\n";
    cout << "3.Изменить название конечного пункта маршрута\n";
    cout << "4.Изменить время отправления\n";
    unsigned int num;
    cin >> num;
    switch (num)
    {
        case 1:
        {
            cout << "Введите новый номер маршрута:\n";
            int new_num;
            cin >> new_num;
            my_marsh.set_route_number(new_num);
            return;
        }
        case 2:
        {
            cout << "Введите новое название начального пункта маршрута:\n";
            string new_start;
            cin >> new_start;
            my_marsh.set_start_point(new_start);
            return;
        }
        case 3:
        {
            cout << "Введите новую название конечного пункта маршрута:\n";
            string new_end;
            cin >> new_end;
            my_marsh.set_end_point(new_end);
            return;
        }
        case 4:
        {
            cout << "Введите новое время отправления:\n";
            string new_time;
            cin >> new_time;
            my_marsh.set_departure_time(new_time);
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
    cout << "8.Вывод маршрутов следующих в пункт К.\n";
    cout << "9.Вывод маршрутов с временем отправления после времени К и следующих из пункта М.\n";
    cout << "10.Выход.\n";
    cout << "Выберите действие.\n";
}


int main() {
    setlocale(0, "RUS");
    ifstream in("marsh.txt");
    balanced_tree <marsh> marshruts;
    marsh my_marsh;
    string start_point;
    string end_point;
    string departure_time;
    int route_number;
    int num_marsh;
    int cmp;
    do
    {
        print_menu();
        correct_input_cmp(cmp);
        switch (cmp)
        {
            case 1:
            {
                cout << "Введите кол-во маршрутов:\n";
                correct_input_N(num_marsh);
                cout << "Введите маршруты:\n";
                for (int i = 0; i < num_marsh; i++) {
                    cout << "Введите номер, откуда двигаемся, куда двигаемся и время отправления!\n";
                    cin >> my_marsh;
                    marshruts.insert(my_marsh);
                }
                break;
            }
            case 2:
            {
                in >> num_marsh;
                for (int i = 0; i < num_marsh; i++) {
                    in >> my_marsh;
                    marshruts.insert(my_marsh);
                }
                in.close();
                cout << "Данные из файла успешно загружены!\n";
                break;
            }
            case 3:
            {
                if (marshruts.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    system("pause");
                    break;
                }
                marshruts.print();
                break;
            }
            case 4:
            {
                cout << "Введите данные о маршруте:\n";
                cout << "Введите номер, откуда двигаемся, куда двигаемся и время отправления!\n";
                cin >> my_marsh;
                marshruts.insert(my_marsh);
                cout << "Маршрут успешно добавлен!\n";
                break;
            }
            case 5:
            {
                if (marshruts.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    system("pause");
                    break;
                }
                cout << "Введите номер маршрута, который требуется удалить:\n";
                cin >> route_number;
                my_marsh = marsh();
                find_marsh_to_number(marshruts.get_root(), route_number, my_marsh);
                if (marshruts.find(my_marsh) == 0) {
                    cout << "Маршрут отсутствует!\n";
                    system("pause");
                    break;
                }
                marshruts.remove(my_marsh);
                cout << "Маршрут успешно удален!\n";
                break;
            }
            case 6:
            {
                if (marshruts.is_empty()) {
                    cout << "В дереве нет элементов!";
                    system("pause");
                    break;
                }
                cout << "Введите номер, откуда двигаемся, куда двигаемся и время отправления!\n";
                cin >> my_marsh;
                marshruts.insert(my_marsh);
                if (marshruts.find(my_marsh) == 0)
                    cout << "Маршрут отсутствует!\n";
                else
                    cout << "Маршрут найден!\n";
                break;
            }
            case 7:
            {
                if (marshruts.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    system("pause");
                    break;
                }
                cout << "Введите номер маршрута, который хотите изменить:\n";
                cin >> route_number;
                my_marsh = marsh();
                find_marsh_to_number(marshruts.get_root(), route_number, my_marsh);
                if (marshruts.find(my_marsh) == 0) {
                    cout << "Маршрут отсутствует!\n";
                    break;
                }
                else {
                    marsh temp = my_marsh;
                    marshruts.remove(my_marsh);
                    change_data(temp);
                    marshruts.insert(temp);
                }
                break;
            }
            case 8:
            {
                if (marshruts.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    break;
                }
                cout << "Введите пункт назначения, и мы выведем всю информацию о поездах следующих в него:\n";
                bool is_empty = true;
                cin >> end_point;
                print_curr_marsh(marshruts.get_root(), end_point, is_empty);
                if (is_empty)
                    cout << "Маршрутов следующих в данный пункт не найдено!";
                break;
            }
            case 9:
            {
                if (marshruts.is_empty()) {
                    cout << "В дереве нет элементов!\n";
                    break;
                }
                cout << "Введите время отправления:\n";
                bool is_empty = true;
                cin >> departure_time;
                cout << "Введите пункт отправления:\n";
                cin >> start_point;
                print_remaining_marsh(marshruts.get_root(), departure_time, start_point, is_empty);
                if (is_empty)
                    cout << "Маршрутов по вашему запросу не найдено!";
                break;
            }
        }
    } while (cmp != 10);
    return 0;
}