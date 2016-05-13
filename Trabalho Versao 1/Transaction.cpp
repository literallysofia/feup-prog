#include "Transaction.h"

Transaction::Transaction(const unsigned int id, const string date, const vector<string> prods)
{
	this->id = id;
	this->date = date;
	this->prods = prods;
}

unsigned int Transaction::GetId()
{
	return id;
}

string Transaction::GetDate()
{
	return date;
}

vector<string> Transaction::GetProds()
{
	return prods;
}

Transaction::~Transaction()
{
}
