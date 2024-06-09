#ifndef DATE_H
#define DATE_H
#pragma once

#include <string>
#include <iostream>
#include <map>

using namespace std;

map<int, int> month_length = {{1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31}, {6, 30}, {7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31}};

bool is_digit(char ch)
{
    int shift = int(ch) - int('0');
    return (0 <= shift) && (shift <= 9);
}

bool odd_year(int year) {
    return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

struct Date {
    int day;
    int month;
    int year;

    Date() {
        this->day = 0;
        this->month = 0;
        this->year = 0;
    }

    Date(const string& time) {
        try {
            string buff = "";
            int pos = 0;
            while (is_digit(time[pos])) {
                buff += time[pos];
                ++pos;
            }
            ++pos;

            this->day = stoi(buff);
            buff.clear();

            while (is_digit(time[pos])) {
                buff += time[pos];
                ++pos;
            }
            ++pos;

            this->month = stoi(buff);
            buff.clear();

            while (is_digit(time[pos])) {
                buff += time[pos];
                ++pos;
            }

            this->year = stoi(buff);
        }
        catch (invalid_argument e) {
            cout << "Ошибка конвертации времени" << endl;
        }
    }

    Date(const Date& t) {
        this->day = t.day;
        this->month = t.month;
        this->year = t.year;
    }

    int to_int()
    {
        int res = 0;

        for (int month = 1; month < this->month; ++month) {
            res += month_length[month];
            if (month == 2 && odd_year(this->year))
                res += 1;
        }

        res += this->day;

        return res;
    }

    Date to_date(int n, int current_year) {
        Date res;
        res.year = current_year;

        if (n <= month_length[1]) {
            res.month = 1;
            res.day = n;
            return res;
        }

        int m = 1;
        while (n > 0) {
            n -= month_length[m];
            if (m == 2  && odd_year(current_year))
                n -= 1;

            m += 1;
        }

        m -= 1;
        if (m == 2 && odd_year(current_year))
            n += 1;

        n += month_length[m];

        res.month = m;
        res.day = n;

        return res;
    }

    string to_str() {
        string res = "";
        res += to_string(this->day) + '.';
        res += to_string(this->month) + '.';
        res += to_string(this->year);
        return res;
    }
};

bool operator <=(const Date& t1, const Date& t2)
{
    if (t1.year < t2.year)
        return true;

    if (t1.year > t2.year)
        return false;

    if (t1.month < t2.month)
        return true;

    if (t1.month > t2.month)
        return false;

    return t1.day <= t2.day;
}

ostream& operator<<(ostream& out, const Date& t)
{
    out << t.day << '.' << t.month << '.' << t.year;

    return out;
}

Date operator +(Date& d, int n)
{
    Date res;
    res.year = d.year;

    int d_int = d.to_int() + n;
    if (d_int > 365 && !odd_year(d.year)) {
        res.year += 1;
        d_int -= 365;
    }
    if (d_int > 366 && odd_year(d.year)) {
        res.year += 1;
        d_int -= 366;
    }

    res = Date().to_date(d_int, res.year);

    return res;
}

#endif // DATE_H
