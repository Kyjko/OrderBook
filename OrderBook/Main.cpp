#include <iostream>
#include "OrderBook.h"

void InsertDummyEntries(std::unique_ptr<OrderBook>& Book) {
	Book->AddAsk(Ask(1500, 70));
	Book->AddAsk(Ask(560, 35));
	Book->AddAsk(Ask(1650, 90));

	Book->AddBid(Bid(960, 40));
	Book->AddBid(Bid(870, 24));
	Book->AddBid(Bid(1700, 66));
}

void TestMarketOrder(std::unique_ptr<OrderBook>& Book, const double size, const OrderBook::OrderType& type) {
	std::string stype;
	switch (type) {
	case OrderBook::OrderType::Buy: {
		stype = std::string("Buy");
		break;
	}
	case OrderBook::OrderType::Sell: {
		stype = std::string("Sell");
		break;
	}
	default: {
		stype = std::string("unknown");
		break;
	}
	}
	std::cout << "----------Market order test (size: " << size << ", type: " << stype << ")" << "----------" << std::endl;
	Book->MarketOrder(size, type);
	Book->Print();
	std::cout << "current askprice: " << Book->GetAskPrice() << std::endl;
	std::cout << "current bidprice: " << Book->GetBidPrice() << std::endl;
	std::cout << "current spread: " << Book->GetSpread() << std::endl;
}

void TestLimitOrder(std::unique_ptr<OrderBook>& Book, const double size, const double price, const OrderBook::OrderType& type) {
	std::string stype;
	switch (type) {
	case OrderBook::OrderType::Buy: {
		stype = std::string("Buy");
		break;
	}
	case OrderBook::OrderType::Sell: {
		stype = std::string("Sell");
		break;
	}
	default: {
		stype = std::string("unknown");
		break;
	}
	}
	std::cout << "-----------Limit order test (size: " << size << ", price: " << price << ", type: " << stype << ")" << "----------" << std::endl;
	Book->LimitOrder(size, price, type);
	Book->Print();
	std::cout << "current askprice: " << Book->GetAskPrice() << std::endl;
	std::cout << "current bidprice: " << Book->GetBidPrice() << std::endl;
	std::cout << "current spread: " << Book->GetSpread() << std::endl;
}

int main(int argc, char** argv) {

	std::unique_ptr<OrderBook> Book = std::make_unique<OrderBook>();

	// test

	InsertDummyEntries(Book);
	Book->Print();
	std::cout << "--------------------------" << std::endl;

	TestLimitOrder(Book, 550, 1300, OrderBook::OrderType::Sell);
	TestMarketOrder(Book, 250, OrderBook::OrderType::Buy);

	

	return 0;
}