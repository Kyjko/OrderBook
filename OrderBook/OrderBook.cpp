#include "OrderBook.h"

OrderBook::OrderBook() {}

OrderBook::~OrderBook() {
	bids = std::vector<Bid>();
	asks = std::vector<Ask>();
	orders = std::vector<Order>();
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

void OrderBook::Print() const noexcept {
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

const double OrderBook::GetMidprice() const noexcept {
	if (!asks.empty() && !bids.empty()) {
		return (asks[0].value + bids[0].value) / 2;
	}
	else {
		return 0.0;
	}
}

const double OrderBook::GetSpread() const noexcept {
	if (!asks.empty() && !bids.empty()) {
		return (asks[0].value + bids[0].value) / GetMidprice();
	}
	else {
		return 0.0;
	}
}

const double OrderBook::GetAskPrice() const noexcept {
	if (!asks.empty()) {
		return asks[0].value;
	}

	return 0.0;
}

const double OrderBook::GetBidPrice() const noexcept {
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
		orders.push_back({ "marketorder", size, asks[0].value, type });
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
		orders.push_back({ "marketorder", size, bids[0].value, type });
		break;
	}
	default: {break; }
	}
}

_NO_META void OrderBook::SortOrdersByPrice() noexcept {
	std::sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) -> bool {
		return a.price > b.price;
	});
}

_NO_META void OrderBook::SortOrdersBySize() noexcept {
	std::sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) -> bool {
		return a.size > b.size;
		});
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
		orders.push_back({"limitorder", size, price, type });
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
		orders.push_back({"limitorder", size, price, type });
		break;
	}
	default: {break; }
	}
}

void OrderBook::DisplayOrders() const noexcept {
	std::cout << "Orders: " << std::endl;
	for (auto i = orders.begin(); i != orders.end(); i++) {
		std::string stype;
		switch (i->type) {
		case OrderType::Buy:
			stype = "Buy";
			break;
		case OrderType::Sell:
			stype = "Sell";
			break;
		default:
			stype = "unknown";
			break;
		}
		std::cout << i->order << " - " << i->size << " - " << i->price << " - " << stype << std::endl;
	}
}