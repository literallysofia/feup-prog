#include "Product.h"

Product::Product(const string prod, const float price)
{
	this->prod = prod;
	this->price = price;
}

string Product::GetProd()
{
	return prod;
}

float Product::GetPrice()
{
	return price;
}

Product::~Product()
{
}
