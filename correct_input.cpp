#include "correct_input.h"
#include <iostream>
using namespace std;


void correct_input_cmp(int& num) {
    cin >> num;
    while (cin.fail() || num < 1 || num > 10) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Выберите пунк меню!\n";
        cin >> num;
    }
}

void correct_input_N(int& num) {
    cin >> num;
    while (cin.fail() || num <= 0) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Введите натуральное значение!\n";
        cin >> num;
    }
}

void correct_input_R(double& num) {
    cin >> num;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Введите вещественное значение!\n";
        cin >> num;
    }
}