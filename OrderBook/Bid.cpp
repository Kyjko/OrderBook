#include "Bid.h"

Bid::Bid(const double size, const double value) : size(size), value(value) {}

std::ostream& operator<<(std::ostream& os, const Bid& bid) {
	os << bid.size << " " << bid.value;
	return os;
}