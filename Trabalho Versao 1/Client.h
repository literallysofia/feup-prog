#pragma once
#include <string>
#include <iostream>
using namespace std;

class Client
{
private:
	int id;
	string nome;
	string data;
	float montante;

public:
	Client(const unsigned int id, const string nome, const string data, const float montante);

	unsigned int GetId();

	string GetNome();

	string GetData();

	float GetMontante();

	void SetID(int NID);

	void SetNome(string NN);

	void SetData(string ND);

	void SetMontante(float NM);

	void SetNewMontante(float NM);

	~Client();
};