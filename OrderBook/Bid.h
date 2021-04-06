#pragma once
#include <iostream>
class Bid {
public:
	Bid(const double size, const double value);
	Bid();

	double size;
	double value;

	friend std::ostream& operator<<(std::ostream& os, const Bid& ask);
};



