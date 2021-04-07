#pragma once
#include <vector>
#include <iostream>
#include "Bid.h"
#include "Ask.h"
#include <algorithm>

#define _NO_META

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
	void Print() const noexcept;

	_NO_META void SortOrdersByPrice() noexcept;
	_NO_META void SortOrdersBySize() noexcept;
	
	const double GetMidprice() const noexcept;
	const double GetSpread() const noexcept;
	const double GetAskPrice() const noexcept;
	const double GetBidPrice() const noexcept;

	void DisplayOrders() const noexcept;

	void MarketOrder(const double size, const OrderType& type) noexcept;
	void LimitOrder(const double size, const double price, const OrderType& type) noexcept;

	std::vector<Bid> bids;
	std::vector<Ask> asks;
	std::vector<Order> orders;

};

