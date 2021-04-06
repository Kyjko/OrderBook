#include "OrderBook.h"

OrderBook::OrderBook() {}

OrderBook::~OrderBook() {
	bids = std::vector<Bid>();
	asks = std::vector<Ask>();
}

void OrderBook::AddAsk(const Ask& ask) noexcept {
	if (ask.value <= 0 || ask.size <= 0) {
		return;
	}
	if (asks.empty()) {
		asks.push_back(ask);
		return;
	}

	int pos = 0;
	while (pos < asks.size()) {
		if (asks[pos].value >= ask.value) {
			break;
		}
		pos++;
	}
	if (pos == asks.size()) {
		asks.push_back(ask);
	}
	else {
		asks.insert(asks.begin() + pos, ask);
	}
}

void OrderBook::AddBid(const Bid& bid) noexcept {
	if (bid.value <= 0 || bid.size <= 0) {
		return;
	}
	if (bids.empty()) {
		bids.push_back(bid);
		return;
	}
	int pos = 0;
	while (pos < bids.size()) {
		if (bids[pos].value <= bid.value) {
			break;
		}
		pos++;
	}
	if (pos == bids.size()) {
		bids.push_back(bid);
	}
	else {
		bids.insert(bids.begin() + pos, bid);
	}
	
}

void OrderBook::Print() noexcept {
	std::cout << "Bid\n-----|-----\nSize \tPrice\n---- \t-----" << std::endl;
	for (auto i = bids.begin(); i != bids.end(); i++) {
		std::cout << i->size << " \t" << i->value << std::endl;
	}
	std::cout << "----------------" << std::endl;
	std::cout << "Ask\n-----|-----\nPrice \tSize\n----- \t----" << std::endl;
	for (auto i = asks.begin(); i != asks.end(); i++) {
		std::cout << i->value << " \t" << i->size << std::endl;
	}
	std::cout << "----------------" << std::endl;
}

const double OrderBook::GetMidprice() noexcept {
	if (!asks.empty() && !bids.empty()) {
		return (asks[0].value + bids[0].value) / 2;
	}
	else {
		return 0.0;
	}
}

const double OrderBook::GetSpread() noexcept {
	if (!asks.empty() && !bids.empty()) {
		return (asks[0].value + bids[0].value) / GetMidprice();
	}
	else {
		return 0.0;
	}
}

const double OrderBook::GetAskPrice() noexcept {
	if (!asks.empty()) {
		return asks[0].value;
	}

	return 0.0;
}

const double OrderBook::GetBidPrice() noexcept {
	if (!bids.empty()) {
		return bids[0].value;
	}

	return 0.0;
}

void OrderBook::MarketOrder(const double size, const OrderType& type) noexcept {
	switch (type) {
	case OrderType::Buy: {
		if (asks.empty()) {
			return;
		}
		Ask& ask = asks[0];
		double remaining = ask.size - size;
		if(remaining > 0) {
			ask.size -= size;
		}
		else {
			AddBid(Bid(size - ask.size, asks[0].value));
			asks.pop_back();
		}
		break;
	}
	case OrderType::Sell: {
		if (bids.empty()) {
			return;
		}
		Bid& bid = bids[0];
		double remaining = bid.size - size;
		if (remaining > 0) {
			bid.size -= size;
		}
		else {
			AddAsk(Ask(size - bid.size, bids[0].value));
			bids.pop_back();
		}
		break;
	}
	default: {break; }
	}
}

void OrderBook::LimitOrder(const double size, const double price, const OrderType& type) noexcept {
	switch (type) {
	case OrderType::Buy: {
		if (asks.empty()) {
			return;
		}
		Ask& ask = asks[0];
		if (price >= ask.value) {
			double remaining = ask.size - size;
			if (remaining > 0) {
				ask.size -= size;
			}
			else {
				AddBid(Bid(size - ask.size, asks[0].value));
				asks.pop_back();
			}
		}
		else {
			AddBid(Bid(size, price));
		}
		break;
	}
	case OrderType::Sell: {
		if (bids.empty()) {
			return;
		}
		Bid& bid = bids[0];
		if (price <= bid.value) {
			double remaining = bid.size - size;
			if (remaining > 0) {
				bid.size -= size;
			}
			else {
				AddAsk(Ask(size - bid.size, asks[0].value));
				bids.pop_back();
			}
		}
		else {
			AddAsk(Ask(size, price));
		}
		break;
	}
	default: {break; }
	}
}