//
// Created by wojte on 27-Dec-22.
//
#ifndef COORDINATES_CPP
#define COORDINATES_CPP


#include <string>

struct Coordinates {
public:
    int value;

    Coordinates() {
        this->value = 0;
    };

    Coordinates(int value) {
        this->value = value;
    };

    Coordinates(std::string name) {
        char first = name[0];
        char second = name[1];
        value = 0;
        value += (first - 'a' + 1) * 10;
        value += second - '1' + 1;
    };

    Coordinates(const Coordinates& other) {
        this->value = other.value;
    };

    int x() { return value / 10; }

    int y() { return value % 10; }

    Coordinates operator+=(Coordinates c2) {
        value += c2.value;
        return *this;
    }

    Coordinates operator-=(Coordinates c2) {
        value -= c2.value;
        return *this;
    }

    Coordinates operator+(Coordinates c2) {
        Coordinates c3(0);
        c3.value += value;
        c3.value += c2.value;
        return c3;
    }

    Coordinates operator-(Coordinates c2) {
        Coordinates c3(0);
        c3.value -= value;
        c3.value -= c2.value;
        return c3;
    }

    bool operator==(Coordinates c2) {
        return this->value == c2.value;
    }

    Coordinates up() { return Coordinates(value + 1); }

    Coordinates down() { return Coordinates(value - 1); }

    Coordinates right() { return Coordinates(value + 10); }

    Coordinates left() { return Coordinates(value - 10); }

    std::string toString() {
        std::string out = "";
        out += 'a' + value / 10 - 1;
        out += '1' + value % 10 - 1;
        return out;
    }

};

#endif