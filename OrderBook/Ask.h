#pragma once
#include <iostream>
class Ask {
public:
	Ask(const double size, const double value);
	Ask();

	double size;
	double value;
	
	friend std::ostream& operator<<(std::ostream& os, const Ask& ask);
};

