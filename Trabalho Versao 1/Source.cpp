#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Utilities.h"
#include "Store.h"
using namespace std;

Store* Store::singleton_instance = 0;
Utilities u;

//Abre janela de controlo no meio do ecra
HWND hwnd = GetConsoleWindow();
RECT desktop;
const HWND hDesktop = GetDesktopWindow();
HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
COORD max_size = GetLargestConsoleWindowSize(screen);

bool ficheiroValidoC(string FClient) {
	ifstream f;
	string line, subLine;
	unsigned int index = 0, fileLineCount, lineCount = 0;

	//Verificacao do numero de clientes
	f.open(FClient);
	getline(f, line);
	while (index != line.length()) {
		if (!isdigit(line[index])) {
			cerr << "> A primeira linha com o total de clientes, contem caracteres invalidos.\n";
			return false;
		}
		++index;
	}
	index = 0;

	//Verificacao da correspondencia do total de clientes
	fileLineCount = atoi(line.c_str());

	while (getline(f, line)) {
		++lineCount;
	}
	if (fileLineCount != lineCount) {
		u.setcolor(4); cerr << "> O total de clientes nao esta de correto.\n"; u.setcolor(15);
		return false;
	}
	f.close();

	//Verificacao de cada linha do ficheiro
	f.open(FClient);
	getline(f, line); //Discarda a linha do ficheiro

	while (getline(f, line)) {

		index = 0;

		//Verificacao do ID
		subLine = line.substr(0, line.find(" ; "));

		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> ID invalido.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find(" ; ") + 3);

		//Verificacao do Nome
		subLine = line.substr(0, line.find(" ; "));
		while (index != subLine.length()) {
			if (!isalpha(subLine[index]) && subLine[index] != ' ') {
				u.setcolor(4); cerr << "> Nome invalido.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find(" ; ") + 3);

		//Verificacao do dia da data
		subLine = line.substr(0, line.find("/"));
		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> Data invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find("/") + 1);

		//Verificacao do mes da data
		subLine = line.substr(0, line.find("/"));
		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> Data invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find("/") + 1);

		//Verificacao do ano da data
		subLine = line.substr(0, line.find(" ; "));
		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> Data invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find(" ; ") + 3);

		//Verificacao da montante
		subLine = line;
		while (index != subLine.length()) {
			if (!isdigit(subLine[index]) && subLine[index] != '.') {
				u.setcolor(4); cerr << "> Montante invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
	}
	f.close();
	return true;
}

//Verifica se o ficheiro de produtos esta corrompido
bool ficheiroValidoP(string FProd) {
	ifstream f;
	string line, subLine;
	unsigned int index = 0, fileLineCount, lineCount = 0;

	//Verificacao do numero de produtos
	f.open(FProd);
	getline(f, line);
	while (index != line.length()) {
		if (!isdigit(line[index])) {
			cerr << "> A primeira linha com o total de produtos, contem caracteres invalidos.\n";
			return false;
		}
		++index;
	}
	index = 0;

	//Verificacao da correspondencia do total de clientes
	fileLineCount = atoi(line.c_str());

	while (getline(f, line)) {
		++lineCount;
	}
	if (fileLineCount != lineCount) {
		u.setcolor(4); cerr << "> O total de produtos nao esta de correto.\n"; u.setcolor(15);
		return false;
	}
	f.close();

	//Verificacao de cada linha do ficheiro
	f.open(FProd);
	getline(f, line); //Discarda a linha do ficheiro

	while (getline(f, line)) {

		index = 0;
		//Verificacao do Nome
		subLine = line.substr(0, line.find(" ; "));
		while (index != subLine.length()) {
			if (!isalpha(subLine[index]) && subLine[index] != ' ') {
				u.setcolor(4); cerr << "> Nome invalido.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find(" ; ") + 3);

		//Verificacao do preco
		subLine = line;
		while (index != subLine.length()) {
			if (!isdigit(subLine[index]) && subLine[index] != '.') {
				u.setcolor(4); cerr << "> Preco invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
	}
	f.close();
	return true;
}

//Verifica se o ficheiro de transacoes esta corrompido
bool ficheiroValidoT(string FTrans) {
	ifstream f;
	string line, subLine;
	unsigned int index = 0, fileLineCount, lineCount = 0;

	//Verificacao do numero de transacoes
	f.open(FTrans);
	getline(f, line);
	while (index != line.length()) {
		if (!isdigit(line[index])) {
			cerr << "> A primeira linha com o total de transacoes, contem caracteres invalidos.\n";
			return false;
		}
		++index;
	}
	index = 0;

	//Verificacao da correspondencia do total de transacoes
	fileLineCount = atoi(line.c_str());

	while (getline(f, line)) {
		++lineCount;
	}
	if (fileLineCount != lineCount) {
		u.setcolor(4); cerr << "> O total de transacoes nao esta de correto.\n"; u.setcolor(15);
		return false;
	}
	f.close();

	//Verificacao de cada linha do ficheiro
	f.open(FTrans);
	getline(f, line); //Discarda a linha do ficheiro

	while (getline(f, line)) {

		index = 0;

		//Verificacao do ID
		subLine = line.substr(0, line.find(" ; "));

		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> ID invalido.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find(" ; ") + 3);

		//Verificacao do dia da data
		subLine = line.substr(0, line.find("/"));
		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> Data invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find("/") + 1);

		//Verificacao do mes da data
		subLine = line.substr(0, line.find("/"));
		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> Data invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find("/") + 1);

		//Verificacao do ano da data
		subLine = line.substr(0, line.find(" ; "));
		while (index != subLine.length()) {
			if (!isdigit(subLine[index])) {
				u.setcolor(4); cerr << "> Data invalida.\n"; u.setcolor(15);
				return false;
			}
			++index;
		}
		index = 0;
		line.erase(0, line.find(" ; ") + 3);

		//Verificacao dos produtos
		subLine = line;
		subLine.append(", ");
		string produto;

		while (!(subLine.empty()))
		{
			produto = subLine.substr(0, subLine.find_first_of(","));
			while (index != produto.length()) {
				if (!isalpha(produto[index]) && produto[index] != ' ') {
					u.setcolor(4); cerr << "> Nome invalido.\n"; u.setcolor(15);
					return false;
				}
				++index;
			}
			index = 0;
			subLine.erase(0, subLine.find_first_of(",") + 2);
		}
	}
	f.close();
	return true;
}

//Verifica se existe o ficheiro com um determinado nome
bool ficheiroDisponivel(string file) {
	ifstream f(file);
	if (f.is_open())
	{
		f.close();
		return true;
	}
	else return false;
}

//Obtem a string com o nome do ficheiro dos clientes
void ficheiroClientes() {
	string FClient;
	cout << endl;
	cout << "Ficheiro dos clientes: "; u.setcolor(3);  cout << "{ ";  u.setcolor(15); cin >> FClient;
	while (cin.fail() || ficheiroDisponivel(FClient) == false)
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
void ficheiroProdutos() {
	string FProd;
	cout << endl;
	cout << "Ficheiro dos produtos: "; u.setcolor(3);  cout << "{ "; u.setcolor(15); cin >> FProd;
	while (cin.fail() || ficheiroDisponivel(FProd) == false)
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
void ficheiroTransacoes()
{
	string FTrans;
	cout << endl;
	cout << "Ficheiro das transacoes: "; u.setcolor(3);  cout << "{ ";  u.setcolor(15); cin >> FTrans;
	while (cin.fail() || ficheiroDisponivel(FTrans) == false)
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

	ficheiroClientes();
	ficheiroProdutos();
	ficheiroTransacoes();

	u.setcolor(3);
	cout << endl;
	Sleep(500);  cout << "."; Sleep(500);  cout << "."; Sleep(500);  cout << "." << endl;  u.setcolor(15);

	Store::instance()->extrairClientes();
	Store::instance()->extrairProdutos();
	Store::instance()->extrairTransacoes();

	Store::instance()->opcoesMenuInicial();
	
	return 0;
}