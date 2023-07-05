#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>

using namespace std;

class book {
private:
    string name;
    string author;
    double cost;
public:

    book() {
        name = "";
        author = "";
        cost = 0;
    }

    ~book() {
        name = "";
        author = "";
        cost = 0;
    }

    int get_cost() { return cost; }
    string get_name() { return name; }
    string get_author() { return author; }

    void set_cost(int val) { cost = val; }
    void set_name(string str) { name = str; }
    void set_author(string str) { author = str; }

    friend ostream& operator<<(ostream&, const book&);
    friend istream& operator>>(istream&, book&);

    bool operator ==(const book& book);
    bool operator >(const book& book);
    bool operator <(const book& book);
    bool operator >=(const book& book);
    bool operator <=(const book& book);
    void operator =(const book& book);
};

inline ostream& operator<<(ostream& output, const  book& book) {
    output << book.name << ' ';
    cout << "Автор: ";
    output << book.author << ' ';
    cout << "Стоимость: ";
    output << book.cost << ' ';
    return output;
}

inline istream& operator>>(istream& input, book& book) {
    //cout << "Название книги: " << "\n";
    input >> book.name;
    //cout << "Автор: " << "\n";
    input >> book.author;
    //cout << "Стоимость: " << "\n";
    input >> book.cost;
    return input;
}

inline bool book::operator ==(const book& book) {
    if (name == book.name)
        return true;
    return false;
}

inline bool book::operator >(const book& book) {
    if (name > book.name)
        return true;
    return false;
}

inline bool book::operator <(const book& book) {
    if (name < book.name)
        return true;
    return false;
}

inline bool book::operator >=(const book& book) {
    if (name >= book.name)
        return true;
    return false;
}

inline bool book::operator <=(const book& book) {
    if (name >= book.name)
        return true;
    return false;
}

inline void book::operator =(const book& book) {
    name = book.name;
    author = book.author;
    cost = book.cost;
}


#endif //BOOK_H