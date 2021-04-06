#pragma once
#include <ostream>
class Ask {
public:
	Ask(const size_t size, const double value);

	size_t size;
	double value;
	
	friend std::ostream& operator<<(std::ostream& os, const Ask& ask);
};

std::ostream& operator<<(std::ostream& os, const Ask& ask) {
	std::cout << ask.size << " " << ask.value;
}
