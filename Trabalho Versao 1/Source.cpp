#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Utilities.h"
#include "Store.h"
using namespace std;

Store* Store::singleton_instance = 0;

//Abre janela de controlo no meio do ecra
HWND hwnd = GetConsoleWindow();
RECT desktop;
const HWND hDesktop = GetDesktopWindow();
HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
COORD max_size = GetLargestConsoleWindowSize(screen);

//Verifica se o ficheiro de clientes esta corrompido
bool ficheiroValidoC(string FClient) {

	ifstream f;
	string line;
	int total;
	f.open(FClient);

	//Verifica o numero de clientes
	getline(f, line);
	total = stoi(line);

	if (total == 0) {
		return false;
	}
	while (getline(f, line)) {
		//Verifica o ID
		unsigned int id = atoi(line.substr(0, line.find(" ; ")).c_str());
		if (id == 0) {
			return false;
		}
		line.erase(0, line.find(" ; ") + 3);

		//Verifica o nome
		unsigned int nome = atoi(line.substr(0, line.find(" ; ")).c_str());
		if (nome != 0) {
			return false;
		}
		line.erase(0, line.find(" ; ") + 3);

		//Verifica o dia
		unsigned int dia = atoi(line.substr(0, line.find("/")).c_str());
		if (dia == 0) {
			return false;
		}
		line.erase(0, line.find("/") + 1);

		//verifica o mes
		unsigned int mes = atoi(line.substr(0, line.find("/")).c_str());
		if (mes == 0) {
			return false;
		}
		line.erase(0, line.find("/") + 1);

		//Verifica o ano
		unsigned int ano = atoi(line.substr(0, line.find(" ; ")).c_str());
		if (ano == 0) {
			return false;
		}
		line.erase(0, line.find(" ; ") + 3);
	}
	f.close();
	return true;
}

//Verifica se o ficheiro de produtos esta corrompido
bool ficheiroValidoP(string FProd) {

	ifstream f;
	string line;
	int total;
	f.open(FProd);

	//Verifica o numero de produtos
	getline(f, line);
	total = stoi(line);

	if (total == 0) {
		return false;
	}
	while (getline(f, line)) {
		//Verifica o produto
		unsigned int produto = atoi(line.substr(0, line.find(" ; ")).c_str());
		if (produto != 0) {
			return false;
		}
		line.erase(0, line.find(" ; ") + 3);
	}
	f.close();
	return true;
}

//Verifica se o ficheiro de transacoes esta corrompido
bool ficheiroValidoT(string FTrans) {

	ifstream f;
	string line;
	int total;
	f.open(FTrans);

	//Verifica o numero de transacoes
	getline(f, line);
	total = stoi(line);

	if (total == 0) {
		return false;
	}
	while (getline(f, line)) {
		//Verifica o ID
		unsigned int id = atoi(line.substr(0, line.find(" ; ")).c_str());
		if (id == 0) {
			return false;
		}
		line.erase(0, line.find(" ; ") + 3);

		//Verifica o dia
		unsigned int dia = atoi(line.substr(0, line.find("/")).c_str());
		if (dia == 0) {
			return false;
		}
		line.erase(0, line.find("/") + 1);

		//verifica o mes
		unsigned int mes = atoi(line.substr(0, line.find("/")).c_str());
		if (mes == 0) {
			return false;
		}
		line.erase(0, line.find("/") + 1);

		//Verifica o ano
		unsigned int ano = atoi(line.substr(0, line.find(" ; ")).c_str());
		if (ano == 0) {
			return false;
		}
		line.erase(0, line.find(" ; ") + 3);
	}
	f.close();
	return true;
}

//Verifica se existe o ficheiro com um determinado nome
bool FicheiroDisponivel(string file) {
	ifstream f(file);
	if (f.is_open())
	{
		f.close();
		return true;
	}
	else return false;
}

//Obtem a string com o nome do ficheiro dos clientes
void FicheiroClientes() {
	Utilities u;
	string FClient;
	cout << endl;
	cout << "Ficheiro dos clientes: "; u.setcolor(3);  cout << "{ ";  u.setcolor(15); cin >> FClient;
	while (cin.fail() || FicheiroDisponivel(FClient) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> Ficheiro nao encontrado, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> FClient;
	}
	while (ficheiroValidoC(FClient) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> O ficheiro incorreto, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> FClient;
	}
	Store::instance()->setClientsFileName(FClient);
}

//Obtem a string com o nome do ficheiro dos produtos
void FicheiroProdutos() {
	Utilities u;
	string FProd;
	cout << endl;
	cout << "Ficheiro dos produtos: "; u.setcolor(3);  cout << "{ "; u.setcolor(15); cin >> FProd;
	while (cin.fail() || FicheiroDisponivel(FProd) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> Ficheiro nao encontrado, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> FProd;
	}
	while (ficheiroValidoP(FProd) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> O ficheiro incorreto, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> FProd;
	}
	Store::instance()->setProductsFileName(FProd);
}

//Obtem a string com o nome do ficheiro das transacoes
void FicheiroTransacoes()
{
	Utilities u;
	string FTrans;
	cout << endl;
	cout << "Ficheiro das transacoes: "; u.setcolor(3);  cout << "{ ";  u.setcolor(15); cin >> FTrans;
	while (cin.fail() || FicheiroDisponivel(FTrans) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> Ficheiro nao encontrado, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> FTrans;
	}
	while (ficheiroValidoT(FTrans) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> O ficheiro incorreto, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> FTrans;
	}
	Store::instance()->setTransFileName(FTrans);
}

int main()
{
	//Janela//
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 310, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	Utilities u;

	//Menu de boas vindas
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               "; u.setcolor(3); cout << "Supermercado  Vende++"; u.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                      ";  u.setcolor(7); cout << "BEM   VINDO !";  u.setcolor(15); cout << "                      |" << endl;
	u.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	u.setcolor(15); cout << setw(56) << "Indique o nome dos ficheiros com os dados, incluindo" << endl << setw(40) << "tambem a sua extensao." << endl << endl;
	u.setcolor(7); cout << setw(13) << "Exemplo: ";  u.setcolor(15); cout << "     NOMEDOFICHEIRO.txt" << endl;
	u.setcolor(3);  cout << "-----------------------------------------------------------" << endl;
	u.setcolor(15);

	FicheiroClientes();
	FicheiroProdutos();
	FicheiroTransacoes();

	u.setcolor(3);
	cout << endl;
	Sleep(500);  cout << "."; Sleep(500);  cout << "."; Sleep(500);  cout << "." << endl;  u.setcolor(15);

	Store::instance()->ExtrairClientes();
	Store::instance()->ExtrairProdutos();
	Store::instance()->ExtrairTransacoes();

	Store::instance()->OpcoesMenuIniciar();
	
	return 0;
}