#pragma once

#include <iostream>
#include <string>

using namespace std;

class marsh {
private:
    string start_point;
    string end_point;
    string departure_time;
    int route_number;
public:

    marsh() {
        start_point = "";
        end_point = "";
        departure_time = "";
        route_number = 0;
    }

    ~marsh() {
        start_point = "";
        end_point = "";
        departure_time = "";
        route_number = 0;
    }

    int get_route_number() { return route_number; }
    string get_start_point() { return start_point; }
    string get_end_point() { return end_point; }
    string get_departure_time() { return departure_time; }
    int get_depart_in_sec() {
        int time_in_sec;
        string hour = "";
        string minute = "";
        hour += this->departure_time[0];
        hour += this->departure_time[1];
        minute += this->departure_time[3];
        minute += this->departure_time[4];
        time_in_sec = (stoi(hour)*3600 + stoi(minute)*60);
        return time_in_sec;
    }

    void set_route_number(int val) { route_number = val; }
    void set_start_point(string str) { start_point = str; }
    void set_end_point(string str) { end_point = str; }
    void set_departure_time(string str) { departure_time = str; }

    friend ostream& operator<<(ostream&, const marsh&);
    friend istream& operator>>(istream&, marsh&);

    bool operator ==(const marsh& marsh);
    bool operator >(const marsh& marsh);
    bool operator <(const marsh& marsh);
    bool operator >=(const marsh& marsh);
    bool operator <=(const marsh& marsh);
    void operator =(const marsh& marsh);
};

inline ostream& operator<<(ostream& output, const  marsh& marsh) {
    cout << "Номер маршрута: ";
    output << marsh.route_number;
    cout << " Название начального пункта маршрута: ";
    output << marsh.start_point;
    cout << " Название конечного пункта маршрута: ";
    output << marsh.end_point;
    cout << " Время отправления: ";
    output << marsh.departure_time << '\n';
    return output;
}

inline istream& operator>>(istream& input, marsh& marsh) {
    //cout << "Введите номер маршрута: ";
    input >> marsh.route_number;
    //cout << "Введите название начального пункта маршрута: ";
    input >> marsh.start_point;
    //cout << "Введите название конечного пункта маршрута: ";
    input >> marsh.end_point;
    //cout << "Время отправления: ";
    input >> marsh.departure_time;
    return input;
}

inline bool marsh::operator ==(const marsh& marsh) {
    if (route_number == marsh.route_number)
        return true;
    return false;
}

inline bool marsh::operator >(const marsh& marsh) {
    if (route_number > marsh.route_number)
        return true;
    return false;
}

inline bool marsh::operator <(const marsh& marsh) {
    if (route_number < marsh.route_number)
        return true;
    return false;
}

inline bool marsh::operator >=(const marsh& marsh) {
    if (route_number >= marsh.route_number)
        return true;
    return false;
}

inline bool marsh::operator <=(const marsh& marsh) {
    if (route_number <= marsh.route_number)
        return true;
    return false;
}

inline void marsh::operator =(const marsh& marsh) {
    route_number = marsh.route_number;
    start_point = marsh.start_point;
    end_point = marsh.end_point;
    departure_time = marsh.departure_time;
}