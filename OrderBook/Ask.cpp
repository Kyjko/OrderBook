#include "Ask.h"

Ask::Ask(const double size, const double value) : size(size), value(value) {}

std::ostream& operator<<(std::ostream& os, const Ask& ask) {
	os << ask.size << " " << ask.value;
	return os;
}
