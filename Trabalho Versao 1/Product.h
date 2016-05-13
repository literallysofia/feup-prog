#pragma once
#include <string>
#include <vector>
using namespace std;

class Product
{
private:
	string prod;
	float price;
public:
	Product(const string prod, const float price);

	string GetProd();

	float GetPrice();

	~Product();
};

