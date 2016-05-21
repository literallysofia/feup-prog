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
	map<unsigned int, unsigned int> Client_IdIx; //map<id_cliente, posicao_cliente>
	map<unsigned int, unsigned int> ClientNB10_IdIx; //map<id_clienteNB10, posicao_VNB10>
	map<string, unsigned int> Prod_Ix; //map<nome_produto, posicao_produto>

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
	string dataAtual();
	bool anoBissexto(int ano);
	int totalDias(int mes, int ano);
	bool dataValida(int Dia, int Mes, int Ano);

	//Menus
	int visualizarInformacao();
	void opcoesVisualizarInformacao();
	int listaTransacoes();
	void opcoesListaTransacoes();
	int produtosDisponiveis();
	void opcoesProdutosDisponiveis();
	int gerirClientes();
	void opcoesGerirClientes();
	int listaClientes();
	void opcoesListaClientes();
	int saida();
	int menuInicial();
	void opcoesMenuInicial();
	int publicidadePersonalizada();
	void opcoesPublicidadePersonalizada();

	//Clientes
	void extrairClientes();
	int escreverCliente();
	bool clienteExiste(string output);
	int criarCliente();
	int removerCliente();
	int alterarCliente();
	int informacaoIndividual();
	string formatarNome(string nome);
	int ordenarCNome();
	int bottom10();
	int mostrarClientes();

	//Produtos
	void extrairProdutos();
	int mostrarProdutos();
	int efetuarCompras();

	//Transacoes
	void extrairTransacoes();
	int escreverTrans();
	int transEntreDatas();
	int transDia();
	bool transExisteID(unsigned int id);
	int transIndividual();
	bool transExisteData(int dataint1);
	int mostrarTransacoes();
	void criarTrans(int id, string produtos);

	//Publicidade
	int pubIndividual();
	int pubBottom10();
};

