#include "Client.h"

Client::Client(const unsigned int id, const string nome, const string data, const float montante)
{
	this->id = id;
	this->nome = nome;
	this->data = data;
	this->montante = montante;
}

unsigned int Client::GetId()
{
	return id;
}

string Client::GetNome()
{
	return nome;
}

string Client::GetData()
{
	return data;
}

float Client::GetMontante()
{
	return montante;
}

void Client::SetID(int NID)
{
	id = NID;
}

void Client::SetNome(string NN)
{
	nome = NN;
}

void Client::SetData(string ND)
{
	data = ND;
}

void Client::SetMontante(float NM)
{
	montante += NM;
}

Client::~Client()
{
}
