#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <Windows.h>
#include <algorithm>
#include "Client.h"
#include "Product.h"
#include "Transaction.h"
#include "Utilities.h"
using namespace std;

class Store
{
private:
	static Store* singleton_instance;

	//Nomes dos ficheiros
	string FClient;
	string FProd;
	string FTrans;

	//Vetores
	vector<Client> VClients;
	vector<Product> VProducts;
	vector<Transaction> VTrans;

	//Maps
	map<unsigned int, unsigned int> Client_IdIx;   //map<id_cliente, posicao_cliente>
	map<string, unsigned int> Prod_Ix;				//map<nome_produto, posicao_produto>
	vector<unsigned int> Trans_pos;
	multimap<unsigned int, unsigned int> Trans_IdIx;    //map<id_cliente, vetor de posicoes das transacoes>

public:
	Store();
	~Store();

	static Store* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Store;

		return singleton_instance;
	}

	//Nome dos Ficheiros
	void setClientsFileName(string clienttxt);
	void setProductsFileName(string producttxt);
	void setTransFileName(string transactiontxt);

	//Datas
	string DataAtual();
	bool Bisexto(int ano);
	int Dias(int mes, int ano);
	bool DataValida(int Dia, int Mes, int Ano);

	//Utilidades

	void setcolor(int ForgC);

	int PublicidadePersonalizada();

	void OpcoesPublicidadePersonalizada();

	//Menus
	int VisualizarInformacao();
	void OpcoesVisualizarInformacao();
	int ListaTransacoes();
	void OpcoesListaTransacoes();
	int ProdutosDisponiveis();
	void OpcoesProdutosDisponiveis();
	int GerirClientes();
	void OpcoesGerirClientes();
	int ListaClientes();
	void OpcoesListaClientes();
	int Saida();
	int MenuIniciar();
	void OpcoesMenuIniciar();

	//Clientes
	void ExtrairClientes();
	int EscreverCliente();
	bool ClienteExiste(string output);
	int CriarCliente();
	int RemoverCliente();
	int AlterarCliente();
	int InfoInd();
	string formatarNome(string nome);
	int ordenarCNome();
	int Bottom10();
	int MostrarClientes();

	//Produtos
	void ExtrairProdutos();
	int EscreverProduto();
	int MostrarProdutos();
	int Compras();

	//Transacoes
	void ExtrairTransacoes();
	int EscreverTrans();
	int TransEntre();
	int TransDia();
	bool TransExiste(unsigned int id);
	int TransInd();
	bool TransData(int dataint1);
	int MostrarTransacoes();
	void AdicionarTrans(int id, string produtos);

	//Publicidade
	int PubIndividual();
};

