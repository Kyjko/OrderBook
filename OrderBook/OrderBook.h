#pragma once
#include <vector>
#include <iostream>
#include "Bid.h"
#include "Ask.h"

class OrderBook {
public:

	enum class OrderType {
		Sell,
		Buy
	};

	struct Order {
		std::string order;
		double size; 
		double price;
		OrderType type;
	};

	OrderBook();
	~OrderBook();

	void AddBid(const Bid& bid) noexcept;
	void AddAsk(const Ask& ask) noexcept;
	void Print() noexcept;
	
	const double GetMidprice() noexcept;
	const double GetSpread() noexcept;
	const double GetAskPrice() noexcept;
	const double GetBidPrice() noexcept;

	void DisplayOrders() noexcept;

	void MarketOrder(const double size, const OrderType& type) noexcept;
	void LimitOrder(const double size, const double price, const OrderType& type) noexcept;

	std::vector<Bid> bids;
	std::vector<Ask> asks;
	std::vector<Order> orders;

};

