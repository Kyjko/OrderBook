#pragma once
class Bid {
public:
	Bid(const size_t size, const double value);
	//Bid();
	size_t size;
	double value;

	friend std::ostream& operator<<(std::ostream& os, const Bid& ask);
};

std::ostream& operator<<(std::ostream& os, const Bid& bid) {
	std::cout << bid.size << " " << bid.value;
}

