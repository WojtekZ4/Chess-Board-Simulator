//
// Created by wojte on 27-Dec-22.
//
#ifndef COORDINATES_CPP
#define COORDINATES_CPP


#include <string>

struct Coordinates {
public:

	int x;
	int y;

	Coordinates() {
		this->x = 0;
		this->y = 0;
	};

	Coordinates(int x, int y) {
		this->x = x;
		this->y = y;
	};

	Coordinates(std::string name) {
		char first = name[0];
		char second = name[1];
		this->x = 0;
		this->y = 0;
		x += first - 'a' + 1;
		y += second - '1' + 1;
	};

	Coordinates(const Coordinates& other) {
		this->x = other.x;
		this->y = other.y;
	};

	Coordinates(std::pair<int, int> other) {
		this->x = other.first;
		this->y = other.second;
	};

	Coordinates operator+=(Coordinates const& c2) {
		x += c2.x;
		y += c2.y;
		return *this;
	}

	Coordinates operator-=(Coordinates const& c2) {
		x -= c2.x;
		y -= c2.y;
		return *this;
	}

	Coordinates operator+(Coordinates const& c2) const {
		Coordinates c3(*this);
		c3 += c2;
		return c3;
	}

	Coordinates operator-(Coordinates const& c2) const {
		Coordinates c3(*this);
		c3 -= c2;
		return c3;
	}



	bool operator == (Coordinates const& c2) const {
		return this->x == c2.x && this->y == c2.y;
	}

	bool operator>(Coordinates const& c2) const {
		return this->x == c2.x ? this->y > c2.y : this->x > c2.x;
	}

	bool operator<(Coordinates const& c2) const {
		return this->x == c2.x ? this->y < c2.y : this->x < c2.x;
	}

	bool operator>=(Coordinates const& c2) const {
		return *this > c2 || *this == c2;
	}

	bool operator<=(Coordinates const& c2) const {
		return *this < c2 || *this == c2;
	}

	Coordinates up() { return Coordinates(x, y + 1); }

	Coordinates down() { return Coordinates(x, y - 1); }

	Coordinates right() { return Coordinates(x + 1, y); }

	Coordinates left() { return Coordinates(x - 1, y); }

	std::pair<int, int> value() {
		return std::pair<int, int>(x, y);
	}

	std::string toString() {
		std::string out = "";
		out += 'a' + x - 1;
		out += '1' + y - 1;
		return out;
	}

};

#endif