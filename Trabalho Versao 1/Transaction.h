#pragma once
#include <string>
#include <vector>
using namespace std;

class Transaction
{
private:
	int id;
	string date;
	vector<string> prods;
public:
	Transaction(const unsigned int id, const string date, const vector<string> prods);

	unsigned int GetId();

	string GetDate();

	vector<string> GetProds();

	~Transaction();
};

