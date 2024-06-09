#ifndef STORAGE_H
#define STORAGE_H
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "date.h"

using namespace std;


struct Good {
    int id;
    string name;
    double price;
    Date exp;

    Good();
    Good(int id, const string& name, double price, const string& exp);
    Good(istream& in);

    void show(ostream& out);
};


class Storage {
protected:
    string _name;
    vector<Good> _goods;
    vector<double> _counts;
    map<int, int> _id_to_pos;

public:
    Storage() {};
    Storage(istream& in);

    pair<Good, double> get_good(int id);
    vector<int> get_ids();

    string name() {
        return this->_name;
    }

    bool check_id(int id);

    void add_good(const Good& g, double count);
    void delete_good(int id);

    void edit_id(int id, int id_new);
    void edit_name(int id, const string& name_new);
    void edit_price(int id, double price_new);
    void edit_exp(int id, const string& exp_new);
    void edit_count(int id, double count_new);

    void show(ostream& out);
};

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

Good::Good() {
    this->id = 0;
    this->name = "";
    this->price = 0.0;
}

Good::Good(int id, const string& name, double price, const string& exp)
{
    this->id = id;
    this->name = name;
    this->price = price;
    this->exp = Date(exp);
}

Good::Good(istream& in) {
    try {
        this->id = 0;
        this->name = "";
        this->price = 0.0;

        string buff;

        getline(in, buff);
        if (buff.size() > 0)
            this->id = stoi(buff);

        getline(in, buff);
        if (buff.size() > 0)
            this->name = buff;

        getline(in, buff);
        if (buff.size() > 0)
            this->price = stof(buff);

        getline(in, buff);
        if (buff.size() > 0)
            this->exp = Date(buff);
    }
    catch (invalid_argument e) {
        cout << "Ошибка чтения товара" << endl;
    }
}

void Good::show(ostream& out) {
    out << id << endl;
    out << name << endl;
    out << price << endl;
    out << exp << endl;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

Storage::Storage(istream& in) {
    try {
        string buff = "";
        while (buff.size() == 0)
            getline(in, buff);

        this->_name = buff;

        int n_goods = 0;
        getline(in, buff);
        if (buff.size() > 0)
            n_goods = stoi(buff);

        for (int i = 0; i < n_goods; ++i) {
            Good g(in);
            getline(in, buff);
            double count = stof(buff);
            this->add_good(g, count);
        }
    }
    catch (int& e) {
        cout << "Ошибка чтения склада" << endl;
    }
}

pair<Good, double> Storage::get_good(int id) {
    if (check_id(id)) {
        int pos = _id_to_pos[id];
        pair<Good, double> res = {this->_goods[pos], this->_counts[pos]};
        return res;
    }
    pair<Good, double> res = {Good(), 0};
    return res;
}

vector<int> Storage::get_ids() {
    vector<int> res;

    for (auto g: this->_goods)
        res.push_back(g.id);

    return res;
}

bool Storage::check_id(int id) {
    if (this->_id_to_pos.find(id) != this->_id_to_pos.end())
        return true;

    return false;
}

void Storage::add_good(const Good& g, double count) {
    this->_goods.push_back(g);
    this->_counts.push_back(count);
    this->_id_to_pos[g.id] = this->_goods.size() - 1;
}

void Storage::delete_good(int id)
{
    if (check_id(id)) {
        int pos = _id_to_pos[id];
        this->_goods.erase(this->_goods.begin() + pos);
    }
}

void Storage::edit_id(int id, int id_new) {
    if (check_id(id)) {
        int pos = _id_to_pos[id];
        this->_goods[pos].id = id_new;
    }
}

void Storage::edit_name(int id, const string& name_new) {
    if (check_id(id)) {
        int pos = _id_to_pos[id];
        this->_goods[pos].name = name_new;
    }
}

void Storage::edit_price(int id, double price_new) {
    if (check_id(id)) {
        int pos = _id_to_pos[id];
        this->_goods[pos].price = price_new;
    }
}

void Storage::edit_exp(int id, const string& exp_new) {
    if (check_id(id)) {
        int pos = _id_to_pos[id];
        this->_goods[pos].exp = exp_new;
    }
}

void Storage::edit_count(int id, double count_new) {
    if (check_id(id)) {
        int pos = _id_to_pos[id];
        this->_counts[pos] = count_new;
    }
}

void Storage::show(ostream& out) {
    out << this->_name << endl;
    out << this->_goods.size() << endl;
    for (auto e: this->_goods) {
        e.show(out);

        int pos = this->_id_to_pos[e.id];
        cout << this->_counts[pos] << endl;
    }
}

#endif // STORAGE_H
