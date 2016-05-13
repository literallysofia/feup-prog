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

// booleano que verifica se existe o ficheiro com um determinado nome
bool FicheiroDisponivel(string file) {
	ifstream f(file);
	if (f.is_open())
	{
		f.close();
		return true;
	}
	else return false;
}

// funcao que retorna a string com o nome do ficheiro, caso exista
void FicheiroClientes() {
	Utilities u;
	string clienttxt;
	cout << endl;
	cout << "Ficheiro dos clientes: "; u.setcolor(3);  cout << "{ ";  u.setcolor(15); cin >> clienttxt;
	while (cin.fail() || FicheiroDisponivel(clienttxt) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> Ficheiro nao encontrado, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> clienttxt;
	}

	Store::instance()->setClientsFileName(clienttxt);
}

void FicheiroProdutos() {
	Utilities u;
	string producttxt;
	cout << endl;
	cout << "Ficheiro dos produtos: "; u.setcolor(3);  cout << "{ "; u.setcolor(15); cin >> producttxt;
	while (cin.fail() || FicheiroDisponivel(producttxt) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> Ficheiro nao encontrado, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> producttxt;
	}
	Store::instance()->setProductsFileName(producttxt);
}

void FicheiroTransacoes()
{
	Utilities u;
	string transactiontxt;
	cout << endl;
	cout << "Ficheiro das transacoes: "; u.setcolor(3);  cout << "{ ";  u.setcolor(15); cin >> transactiontxt;
	while (cin.fail() || FicheiroDisponivel(transactiontxt) == false)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(4); cout << "> Ficheiro nao encontrado, volte a indicar o nome." << endl;
		u.setcolor(3);  cout << "  { "; u.setcolor(15); cin >> transactiontxt;
	}
	Store::instance()->setTransFileName(transactiontxt);
}

int main()
{
	//Janela//
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 310, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	Utilities u;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               "; u.setcolor(3); cout << "Supermercado  Vende++"; u.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                      ";  u.setcolor(7); cout << "BEM   VINDO !";  u.setcolor(15); cout << "                      |" << endl;
	u.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	u.setcolor(15); cout << setw(56) << "Indique o nome dos ficheiros com os dados, incluindo" << endl << setw(40) << "tambem a sua extensao." << endl << endl;
	u.setcolor(7); cout << setw(13) << "Exemplo: ";  u.setcolor(15); cout << "     NOMEDOFICHEIRO.txt" << endl;
	u.setcolor(3);  cout << "-----------------------------------------------------------" << endl;
	u.setcolor(15);

	// MANDAR STRING DO FICHEIRO //
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