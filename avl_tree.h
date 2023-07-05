#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "book.h"

using namespace std;

template <class T>
struct node {
    T data;
    node<T>* left;
    node<T>* right;
    int height; //высота узла (сколько уровней под ним)
    node(T val = T()) : data(val), height(0), left(0), right(0) {};
    node<T>* get_left() { return left; }
    node<T>* get_right() { return right; }
};

template <class T>
class balanced_tree {
public:
    balanced_tree() { root = 0; }

    ~balanced_tree() { make_empty(root); }

    //вставка элемента с заданным значением
    void insert(T x) { root = insert(x, root); }

    //удаление элемента с заданным значением
    void remove(T x) { root = remove(x, root); }

    //печать дерева
    void print() { print(root, 0); }

    //печать дерева в порядке возрастания значений
    void print_raising() { print_raising(root); }

    //проверка пустоты
    bool is_empty() { return (root == 0) ? true : false; }

    //поиск узла по значению элемента (обёртка)
    node<T>* find(T val) { return find(root, val); }

    //геттер для узла (чтобы можно было ходить по дереву в мейне)
    node<T>* get_root() { return root; }
private:
    node<T>* root;

    //функция печати дерева
    void print(node<T>* pos, int space);

    //печать дерева по возрастанию
    void print_raising(node<T>* pos);

    //удаление дерева
    void make_empty(node<T>* pos);

    //поиск узла по значению элемента
    node<T>* find(node<T>* pos, T val);

    //добавление узла со значением элемента
    node<T>* insert(T x, node<T>* pos);

    //единичный поворот вправо
    node<T>* single_r_rotate(node<T>* &pos);

    //единичный поворот влево
    node<T>* single_l_rotate(node<T>* &pos);

    //двойной поворот влево
    node<T>* double_l_rotate(node<T>* &pos);

    //двойной поворот вправо
    node<T>* double_r_rotate(node<T>* &pos);

    //поиск узла минимального элемента
    node<T>* find_min(node<T>* pos);

    //поиск узла максимального элемента
    node<T>* find_max(node<T>* pos);

    //удаление узла со значением элемента
    node<T>* remove(T x, node<T>* pos);

    //высота узла
    int height(node<T>* pos);

    //функция идёт по уровням и ищет чётный минимум и его уровень
    void level_detour_for_even_min(node<T>* pos, int level, T &min, int &lvl, bool &f);

    //находим уровень, на котором лежит чётный минимум
    int find_level_even_min();

    //добавляем все элементы, находящиеся на выбраном уровне в вектор (обёртка)
    void level2vec(vector<int>&a) {
        if (find_level_even_min() != -1) {
            int lv = find_level_even_min();
            level2vec(root, lv, a);
        }
    }

    //добавляем все элементы, находящиеся на выбраном уровне в вектор
    void level2vec(node<T> *t, int level, vector<int>&a);

};

template <class T>
node<T>* balanced_tree<T>::find(node<T>* pos, T val) {
    if (!pos)
        return 0;
    if (pos->data == val)
        return pos;
    if (pos->data < val)
        return find(pos->right, val);
    return find(pos->left, val);
}

template <class T>
int balanced_tree<T>::height(node<T>* pos) {
    return (pos == NULL ? -1 : pos->height);
}

template <class T>
void balanced_tree<T>::print(node<T>* pos, int space) {
    if (pos == 0)
        return;
    print(pos->left, space + 1);
    for (int i = 0; i < space; i++)
        cout << "   ";
    cout << pos->data << '\n';
    print(pos->right, space + 1);
}

template <class T>
void balanced_tree<T>::print_raising(node<T>* pos) {
    if (pos == 0) return;
    print_raising(pos->left);
    cout << pos->data << '\n';
    print_raising(pos->right);
}

template <class T>
void balanced_tree<T>::make_empty(node<T>* pos) {
    if (pos == 0)
        return;
    make_empty(pos->left);
    make_empty(pos->right);
    delete pos;
}

template <class T>
node<T>* balanced_tree<T>::insert(T x, node<T>* pos) {
    if (pos == 0) {
        pos = new node<T>();
        pos->data = x;
        pos->height = 0;
        pos->left = pos->right = 0;
    }
    else if (x < pos->data) {
        pos->left = insert(x, pos->left);
        if (height(pos->left) - height(pos->right) == 2) {
            if (x < pos->left->data)
                pos = single_r_rotate(pos);
            else
                pos = double_r_rotate(pos);
        }
    }
    else if (x > pos->data) {
        pos->right = insert(x, pos->right);
        if (height(pos->right) - height(pos->left) == 2) {
            if (x > pos->right->data)
                pos = single_l_rotate(pos);
            else
                pos = double_l_rotate(pos);
        }
    }

    pos->height = max(height(pos->left), height(pos->right)) + 1;
    return pos;
}

template <class T>
node<T>* balanced_tree<T>::single_r_rotate(node<T>* &pos) {
    if (pos->left != 0) {
        node<T>* u = pos->left;
        pos->left = u->right;
        u->right = pos;
        pos->height = max(height(pos->left), height(pos->right)) + 1;
        u->height = max(height(u->left), pos->height) + 1;
        return u;
    }
    return pos;
}

template <class T>
node<T>* balanced_tree<T>::single_l_rotate(node<T>* &pos) {
    if (pos->right != 0) {
        node<T>* u = pos->right;
        pos->right = u->left;
        u->left = pos;
        pos->height = max(height(pos->left), height(pos->right)) + 1;
        u->height = max(height(pos->right), pos->height) + 1;
        return u;
    }
    return pos;
}

template <class T>
node<T>* balanced_tree<T>::double_l_rotate(node<T>* &pos) {
    pos->right = single_r_rotate(pos->right);
    return single_l_rotate(pos);
}

template <class T>
node<T>* balanced_tree<T>::double_r_rotate(node<T>* &pos) {
    pos->left = single_l_rotate(pos->left);
    return single_r_rotate(pos);
}

template <class T>
node<T>* balanced_tree<T>::find_min(node<T>* pos) {
    if (pos == 0)
        return 0;
    else if (pos->left == 0)
        return pos;
    else
        return find_min(pos->left);
}

template <class T>
node<T>* balanced_tree<T>::find_max(node<T>* pos) {
    if (pos == 0)
        return 0;
    else if (pos->right == 0)
        return pos;
    else
        return find_max(pos->right);
}

template <class T>
node<T>* balanced_tree<T>::remove(T x, node<T>* pos) {
    node<T>* temp;

    // элемент не найден
    if (pos == 0)
        return 0;

        // поиск элемента
    else if (x < pos->data)
        pos->left = remove(x, pos->left);
    else if (x > pos->data)
        pos->right = remove(x, pos->right);

        // найден элемент с 2 потомками
    else if (pos->left && pos->right) {
        temp = find_min(pos->right);
        pos->data = temp->data;
        pos->right = remove(pos->data, pos->right);
    }
        // найден элемент с одним потомком или лист
    else {
        temp = pos;
        if (pos->left == 0)
            pos = pos->right;
        else if (pos->right == 0)
            pos = pos->left;
        delete temp;
    }
    if (pos == 0)
        return pos;

    pos->height = max(height(pos->left), height(pos->right)) + 1;

    // если узел несбалансирован
    //если левый узел удален
    if (height(pos->left) - height(pos->right) == -2) {
        if (height(pos->right->right) - height(pos->right->left) == 1)
            return single_l_rotate(pos);
        else
            return double_l_rotate(pos);
    }
        // если правый узел удалён
    else if (height(pos->right) - height(pos->left) == 2) {
        if (height(pos->left->left) - height(pos->left->right) == 1)
            return single_r_rotate(pos);
        else
            return double_r_rotate(pos);
    }
    return pos;
}

template <class T>
void  balanced_tree<T>::level_detour_for_even_min(node<T>* pos, int level, T &min, int &minlvl, bool &f) {
    if (!f) //если не нашли минимум - запоминаем уровень
        minlvl = level - 1;
    if (pos == 0)
        return;
    level_detour_for_even_min(pos->left, level + 1, min, minlvl, f);
    if (pos->data % 2 == 0 && pos->data < min) {
        f = 1; //нашли минимум - сменили флаг
        min = pos->data; //меняем значение минимума
        minlvl = level; //меняем уровень на котором лежит минимум
    }
    level_detour_for_even_min(pos->right, level + 1, min, minlvl, f);
}

template <class T>
int balanced_tree<T>::find_level_even_min() {
    int level = 1;
    bool flag = 0;
    T min = find_max(root)->data;
    //пока уровень не последний
    level_detour_for_even_min(root, 0, min, level, flag);
    //если минимум не поменялся и начальное значение четное
    if (min == find_max(root)->data && find_max(root)->data % 2 != 0)
        return -1;
    return level;
}

template <class T>
void  balanced_tree<T>::level2vec(node<T> *t, int level, vector<int>&a) {
    if (t == 0)
        //если дерево пустое выходим
        return;
    level2vec(t->left, level - 1, a);
    if (level == 0)
        //level будет равен нулю на нужной глубине, так как при каждом рекурсивном вызове значение level уменьшается на один
        a.push_back(t->data);  //пушим элемент, если он на нужном нам уровне
    level2vec(t->right, level - 1, a);
}

#endif