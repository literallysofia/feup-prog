#include "Store.h"

Utilities ut;
Store::Store()
{
}

Store::~Store()
{
}

//Nomes dos ficheiros
void Store::setClientsFileName(string clienttxt)
{
	FClient = clienttxt;
}

void Store::setProductsFileName(string producttxt)
{
	FProd = producttxt;
}

void Store::setTransFileName(string transactiontxt)
{
	FTrans = transactiontxt;
}

//Datas

//Retorna a data atual em string
string Store::dataAtual() {
	string dia, mes, ano, Data;
	time_t timeNow = time(NULL);
	tm FTime;
	localtime_s(&FTime, &timeNow);

	dia = to_string(FTime.tm_mday);
	mes = to_string(FTime.tm_mon + 1);
	ano = to_string(FTime.tm_year + 1900);

	if (dia.size() == 1)
		dia.insert(0, "0");

	if (mes.size() == 1)
		mes.insert(0, "0");

	Data = dia;
	Data.append("/"); Data.append(mes); Data.append("/"); Data.append(ano);
	return Data;
}

//Verifica se o ano é Bissexto
bool Store::anoBissexto(int ano)
{
	if ((ano % 400 == 0) && (ano % 100 == 0))
		return true;
	else
		if ((ano % 4 == 0) && (ano % 100 != 0))
			return true;
		else return false;
}

//Retorna total de dias do mes de um determinado ano
int Store::totalDias(int mes, int ano)
{
	bool B = anoBissexto(ano);

	if ((mes == 1) || (mes == 3) || (mes == 5) || (mes == 7) || (mes == 8) || (mes == 10) || (mes == 12))
		return 31;
	else
		if (mes == 2)
			if (B)
				return 29;
			else
				return 28;
		else return 30;

		return 0;
}

//Verifica se a data é valida
bool Store::dataValida(int Dia, int Mes, int Ano)
{
	int DTotal;
	bool B = anoBissexto(Ano);

	if ((Mes > 0) && (Mes <= 12))
	{
		DTotal = totalDias(Mes, Ano);
		if ((Dia <= DTotal) && (Dia > 0))
			return true;
		else return false;
	}
	else return false;
}

//Menus

//MENU - Publicidade Personalizada
int Store::publicidadePersonalizada()
{
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                    ";  ut.setcolor(7); cout << "PUBLICIDADE";  ut.setcolor(15); cout << "                    ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7);
	cout << setw(20) << "1. Individual" << setw(31) << "2. Bottom 10" << endl;
	ut.setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Voltar >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 5))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 2))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}
	return 0;
}

void Store::opcoesPublicidadePersonalizada()
{
	unsigned short int opcao;

	while (opcao = publicidadePersonalizada())
		switch (opcao)
		{
		case 1:
			pubIndividual();
			break;
		case 2:
			pubBottom10();
			break;
		}
}

//MENU - Visualizar Informacao
int Store::visualizarInformacao()
{
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~                ";  ut.setcolor(7); cout << "VISUALIZAR INFORMACAO";  ut.setcolor(15); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7);
	cout << setw(13) << "1. Cliente" << setw(43) << "4. Clientes (ordem alfabetica)" << endl
		<< setw(23) << "2. Todos os clientes" << setw(16) << "5. Transacoes" << endl
		<< setw(15) << "3. Bottom 10" << endl;
	ut.setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Voltar >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 5))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 5))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}
	return 0;
}

void Store::opcoesVisualizarInformacao()
{
	unsigned short int opcao;

	while (opcao = visualizarInformacao())
		switch (opcao)
		{
		case 1:
			informacaoIndividual();
			break;
		case 2:
			opcoesListaClientes();
			break;
		case 3:
			bottom10();
			break;
		case 4:
			ordenarCNome();
			break;
		case 5:
			opcoesListaTransacoes();
			break;
		}
}

//MENU - Transacoes
int Store::listaTransacoes()
{
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                     ";  ut.setcolor(7); cout << "TRANSACOES";  ut.setcolor(15); cout << "                    ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  mostrarTransacoes();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(7); cout << setw(18) << "1. Por cliente" << setw(32) << "3. Por dia" << endl
		<< setw(23) << "2. Entre duas datas" << endl;  ut.setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Voltar >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 3))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 3))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}
	return 0;
}

void Store::opcoesListaTransacoes()
{
	unsigned short int opcao;

	while (opcao = listaTransacoes())
		switch (opcao)
		{
		case 1:
			transIndividual();
			break;
		case 2:
			transEntreDatas();
			break;
		case 3:
			transDia();
			break;
		}
}

//MENU - Produtos Disponiveis
int Store::produtosDisponiveis()
{
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~                ";  ut.setcolor(7); cout << "PRODUTOS DISPONIVEIS";  ut.setcolor(15); cout << "                ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(10) << "Ref" << setw(22) << "Produto" << setw(20) << "Preco" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
	ut.setcolor(15);  mostrarProdutos();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(7); cout << setw(22) << "1. Efetuar Compra" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Voltar >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 1))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 1))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}

	return 0;
}

void Store::opcoesProdutosDisponiveis()
{
	unsigned short int opcao;

	while (opcao = produtosDisponiveis())
		switch (opcao)
		{
		case 1:
			efetuarCompras();
			break;
		}
}

//MENU - Gerir Clientes
int Store::gerirClientes()
{
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                 ";  ut.setcolor(7); cout << "GESTOR DE CLIENTES";  ut.setcolor(15); cout << "                ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  mostrarClientes();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(7); cout << setw(20) << "1. Criar Cliente" << setw(32) << "3. Alterar Cliente" << endl
		<< setw(22) << "2. Remover Cliente" << endl;  ut.setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Voltar >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 3))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 3))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}
	return 0;
}

void Store::opcoesGerirClientes()
{
	unsigned short int opcao;

	while (opcao = gerirClientes())
		switch (opcao)
		{
		case 1:
			criarCliente();
			break;
		case 2:
			removerCliente();
			break;
		case 3:
			alterarCliente();
			break;
		}
}

//MENU - Lista de Clientes
int Store::listaClientes()
{
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                 ";  ut.setcolor(7); cout << "LISTA DE CLIENTES";  ut.setcolor(15); cout << "                 ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  mostrarClientes();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(7);
	cout << setw(32) << "1. Ir para gestor de clientes" << endl;  ut.setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Voltar >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 1))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 1))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}
	return 0;
}

void Store::opcoesListaClientes()
{
	unsigned short int opcao;

	while (opcao = listaClientes())
		switch (opcao)
		{
		case 1:
			opcoesGerirClientes();
			break;
		}
}

//MENU - Saida
int Store::saida()
{
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                          ";  ut.setcolor(7); cout << "SAIR";  ut.setcolor(15); cout << "                           |" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
	cout << endl << setw(48) << "Obrigado por utilizar este software!" << endl << endl;
	ut.setcolor(7); cout << setw(30) << "Desenvolvido por:  ";  ut.setcolor(15); cout << "Barbara Sofia Silva" << endl;
	cout << setw(43) << "Julieta Frade" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
	escreverCliente();
	escreverTrans();
	Sleep(5000);
	exit(0);
}

//MENU - Menu Inicial
int Store::menuInicial() {
	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  ut.setcolor(3); cout << "Supermercado  Vende++";  ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                        ";  ut.setcolor(7); cout << "MENU";  ut.setcolor(15); cout << "                       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(23) << "1. Lista de Clientes" << setw(17) << "4. Transacoes" << endl
		<< setw(24) << "2. Gestor de Clientes" << setw(27) << "5. Visualizar Informacao" << endl
		<< setw(20) << "3. Efetuar Compra" << setw(35) << "6. Publicidade Personalizada" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
	cout << "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Sair >";  ut.setcolor(15); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 6))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 6))
	{
		if (opcao == 0)
			saida();
		return opcao;
	}
	return 0;
}

void Store::opcoesMenuInicial()
{
	unsigned short int opcao;

	while (opcao = menuInicial())
		switch (opcao) {
		case 1:
			opcoesListaClientes();
			break;
		case 2:
			opcoesGerirClientes();
			break;
		case 3:
			opcoesProdutosDisponiveis();
			break;
		case 4:
			opcoesListaTransacoes();
			break;
		case 5:
			opcoesVisualizarInformacao();
			break;
		case 6:
			opcoesPublicidadePersonalizada();
			break;
		}

}

//Clientes

//Extrai informacao do ficheiro dos clientes para um vetor (VClient)
void Store::extrairClientes() {
	ifstream Clientfile(FClient);
	string line;


	if (Clientfile.is_open())
	{
		if (!VClients.empty()) VClients.clear();

		while (getline(Clientfile, line))
		{

			if (line.find(";") != -1) {

				size_t pos1 = line.find(" ;"); //posiçao 1º ;
				string str1 = line.substr(pos1 + 3); //nome+data+compras
				size_t pos2 = str1.find(" ;"); //posição 2º ;
				string str2 = str1.substr(pos2 + 3); //data+compras
				size_t pos3 = str2.find(" ;"); //posiçao 3º ;

				string ids = line.substr(0, pos1);
				string nome = str1.substr(0, pos2);
				string data = str2.substr(0, pos3);
				string comprass = str2.substr(pos3 + 3);

				size_t posd1 = data.find("/"); //posição 1º / na data
				string strd1 = data.substr(posd1 + 1); //mes+ano
				size_t posd2 = strd1.find("/"); //posiçao 2º / na data

				string dia = data.substr(0, posd1);
				string mes = strd1.substr(0, posd2);
				string ano = strd1.substr(posd2 + 1);

				//adiciona um 0 antes do mes ou do dia caso so tenho um digito
				if (dia.size() == 1)
					dia = "0" + dia;
				if (mes.size() == 1)
					mes = "0" + mes;

				string datafinal = dia + "/" + mes + "/" + ano; //data ja com 0s

				int idi = stoi(ids, nullptr, 10); //passa o id de string para int
				float comprasf = stof(comprass); //passa compras de string para float

				VClients.push_back(Client(idi, formatarNome(nome), datafinal, comprasf));

			}
		}
		Clientfile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}

//Escreve vetor VClient no ficheiro dos clientes
int Store::escreverCliente()
{
	ofstream Clientfile(FClient);
	if (Clientfile.is_open())
	{
		Clientfile << VClients.size() << endl; //adiciona nº de clientes no inicio do ficheiro
		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			Clientfile << VClients.at(i).GetId() << " ; " << VClients.at(i).GetNome() << " ; " << VClients.at(i).GetData() << " ; " << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
		}
		Clientfile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
	return 0;
}

//Verifica se o cliente existe
bool Store::clienteExiste(string output) //output pode ser nome ou id
{
	int id;
	int a = 0;
	if ((int)output.at(0) >= 48 && (int)output.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
	{
		id = stoi(output, nullptr, 10); // se a opcao for o ID passa de string para int

		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if (id == VClients.at(i).GetId())
				a++; //adiciona caso encontro um cliente com este id
		}
	}
	else {
		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if (output == VClients.at(i).GetNome())
				a++; //adiciona caso encontro um cliente com este nome
		}
	}
	if (a > 0)
		return true;
	else return false;
}

//Cria cliente
int Store::criarCliente()
{
	string nome;
	float montante = 0;

	cout << endl << "Introduza o nome do cliente: "; cin.ignore(); getline(cin >> setw(26), nome); cout << endl;

	while (cin.fail()) //caso existir algum erro com o input
	{
		if (cin.eof()) //caso queira voltar com ctrl-z
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> nome;
	}

	VClients.push_back(Client(VClients.back().GetId() + 1, formatarNome(nome), dataAtual(), montante));
	return 0;
}

//Remove cliente
int Store::removerCliente()
{
	int id, dig;
	string opcao;

	cout << endl << "Introduza o ID ou o NOME do cliente que pretende eliminar: ";  cin.ignore(); getline(cin, opcao); cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if (clienteExiste(opcao))
	{
		if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
			id = stoi(opcao, nullptr, 10); // se a opcao for o ID
		else id = 0;

		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
			{
				cout << "Tem acerteza que quer eliminar o cliente:" << endl;
				ut.setcolor(3); cout << "-----------------------------------------------------------" << endl; ut.setcolor(15);
				cout << VClients.at(i).GetId();
				cout << setw(20) << VClients.at(i).GetNome();
				cout << setw(14) << VClients.at(i).GetData();
				cout << setw(15) << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
				ut.setcolor(3); cout << "-----------------------------------------------------------" << endl; ut.setcolor(7);
				cout << "1. SIM" << "        " << "2. NAO" << endl << endl; ut.setcolor(15);
				cout << "Digite a sua opcao: ";  cin >> dig; cout << endl;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return 0;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					ut.setcolor(4); cout << "> Digito invalido!" << endl;
					ut.setcolor(15); cout << "Volte a indicar escolha: ";
					cin >> dig;
				}

				if (dig == 1)
				{
					VClients.erase(VClients.begin() + i);
					return 0;
				}
				else
					if (dig == 2)
						return 0;
			}
		}
	}
	else {
		ut.setcolor(4); cerr << "ERRO! Cliente nao encontrado." << endl; ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}

	return 0;
}

//Altera cliente
int Store::alterarCliente()
{
	int id, dig;
	float montante;
	string opcao, nome;

	cout << endl << "Introduza o ID ou o NOME do cliente que pretende alterar: ";  cin.ignore(); getline(cin, opcao); cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if (clienteExiste(opcao))
	{
		if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
			id = stoi(opcao, nullptr, 10); // se a opcao for o ID
		else id = 0;

		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
			{
				cout << "Tem acerteza que quer alterar o cliente:" << endl;
				ut.setcolor(3); cout << "-----------------------------------------------------------" << endl; ut.setcolor(15);
				cout << VClients.at(i).GetId();
				cout << setw(20) << VClients.at(i).GetNome();
				cout << setw(18) << VClients.at(i).GetData();
				cout << setw(16) << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
				ut.setcolor(3); cout << "-----------------------------------------------------------" << endl; ut.setcolor(7);
				cout << "1. SIM" << "        " << "2. NAO" << endl << endl; ut.setcolor(15);
				cout << "Digite a sua opcao: ";  cin >> dig; cout << endl;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return 0;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					ut.setcolor(4); cout << "> Digito invalido!" << endl;
					ut.setcolor(15); cout << "Volte a indicar escolha: ";
					cin >> dig;
				}

				if (dig == 1)
				{
					cout << endl << "Introduza o nome do cliente: "; cin.ignore(); getline(cin >> setw(26), nome); cout << endl;

					while (cin.fail())
					{
						if (cin.eof())
						{
							cin.clear();
							return 0;
						}

						cin.clear();
						cin.ignore(1000, '\n');
						ut.setcolor(4); cout << "> Input invalido!" << endl;
						ut.setcolor(15); cout << "Volte a indicar escolha: ";
						cin >> nome;
					}

					cout << "Introduza o montante gasto: "; cin >> montante; cout << endl;

					while (cin.fail())
					{
						if (cin.eof())
						{
							cin.clear();
							return 0;
						}

						cin.clear();
						cin.ignore(1000, '\n');
						ut.setcolor(4); cout << "> Input invalido!" << endl;
						ut.setcolor(15); cout << "Volte a indicar escolha: ";
						cin >> montante;
					}

					VClients.at(i).SetNome(formatarNome(nome));
					VClients.at(i).SetMontante(montante);
					return 0;
				}
				else
					if (dig == 2)
						return 0;
			}
		}
	}
	else {
		ut.setcolor(4); cerr << "ERRO! Cliente nao encontrado." << endl; ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}
	return 0;
}

//Mostra a informacao de um respetivo cliente
int Store::informacaoIndividual()
{
	int id;
	string opcao;

	cout << endl << "Introduza o ID ou o NOME do cliente que pretende visualizar: ";  cin.ignore(); getline(cin, opcao); cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if (clienteExiste(opcao))
	{
		if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
			id = stoi(opcao, nullptr, 10); // se a opcao for o ID
		else id = 0;

		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
			{
				ut.clearScreen();
				ut.setcolor(14); cout << "> "; ut.setcolor(15); cout << "Informacao do cliente: " << VClients.at(i).GetNome() << endl << endl;
				ut.setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
				ut.setcolor(3); cout << "-----------------------------------------------------------" << endl; ut.setcolor(15);
				cout << setw(5) << VClients.at(i).GetId();
				cout << setw(20) << VClients.at(i).GetNome();
				cout << setw(18) << VClients.at(i).GetData();
				cout << setw(12) << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
				ut.setcolor(3); cout << "-----------------------------------------------------------" << endl; ut.setcolor(15);
				ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
				return 0;
			}
		}
	}
	else {
		ut.setcolor(4); cerr << "> ERRO! Cliente nao encontrado." << endl; ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}
	return 0;
}

string Store::formatarNome(string nome) //muda a primeira letra de cada palavra de uma string para maiuscula e as restantes para minusculas - formata os nomes
{
	string NomeAlterado = nome;

	for (unsigned int i = 1; i < NomeAlterado.length(); i++)
	{
		NomeAlterado.at(i) = tolower(NomeAlterado.at(i)); //altera tudo para minusculas
	}

	if (!isupper(NomeAlterado.at(0)))
	{
		NomeAlterado.at(0) = toupper(NomeAlterado.at(0)); //altera a primeira letra da string para maiusculas
	}


	for (unsigned int i = 1; i < NomeAlterado.length(); i++)
	{
		if (NomeAlterado.at(i - 1) == ' ' && !isupper(NomeAlterado.at(i)))
		{
			NomeAlterado.at(i) = toupper(NomeAlterado.at(i)); //altera a letra depois de um espaço para maiusculas
		}
	}

	return NomeAlterado;
}

int Store::ordenarCNome() //mostra clientes por ordem alfabética
{
	vector <Client> VO = VClients; //VO é um vetor igual ao VClients que vai ser ordenado

	sort(VO.begin(), VO.end(), [](Client &a, Client &b) {return a.GetNome() < b.GetNome(); }); //ordena o vetor VO

	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               "; ut.setcolor(3); cout << "Supermercado  Vende++"; ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                 "; ut.setcolor(7); cout << "LISTA DE CLIENTES"; ut.setcolor(15); cout << "                 ~~~|" << endl
		<< "|~~~               por ordem  alfabetica               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);
	for (unsigned int i = 0; i < VO.size(); i++)
	{
		{
			cout << setw(5) << VO.at(i).GetId();
			cout << setw(20) << VO.at(i).GetNome();
			cout << setw(18) << VO.at(i).GetData();
			cout << setw(12) << setprecision(2) << fixed << VO.at(i).GetMontante() << endl;
		}
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar(); getchar();
	return 0;
}

// BOTTOM 10 //

int Store::bottom10() //mostra os piores 10 clientes
{
	vector<Client> VO = VClients; //VO é um vetor igual ao VClients que vai ser ordenado

	sort(VO.begin(), VO.end(), [](Client &a, Client &b) {return a.GetMontante() < b.GetMontante(); }); //ordena o vetor VO

	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               "; ut.setcolor(3); cout << "Supermercado  Vende++"; ut.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                    "; ut.setcolor(7); cout << "BOTTOM10"; ut.setcolor(15); cout << "                     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);


	for (unsigned int i = 0; i < VO.size(); i++)
	{
		if (i < 10) { //mostra só os 10 piores
			cout << setw(5) << VO.at(i).GetId();
			cout << setw(20) << VO.at(i).GetNome();
			cout << setw(18) << VO.at(i).GetData();
			cout << setw(12) << setprecision(2) << fixed << VO.at(i).GetMontante() << endl;
		}
	}
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl; ut.setcolor(7);
	if (VO.size() < 10)
	{
		cout << endl << "     ATENCAO: Existem menos de 10 clientes registados." << endl;
	}
	ut.setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15);
	getchar();
	getchar();
	return 0;
}

// funcao que mostra o ficheiro dos clientes
int Store::mostrarClientes() {
	for (unsigned int i = 0; i < VClients.size(); i++)
	{
		cout << setw(5) << VClients.at(i).GetId();
		cout << setw(20) << VClients.at(i).GetNome();
		cout << setw(18) << VClients.at(i).GetData();
		cout << setw(12) << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
	}
	return 0;
}

//Produtos

//Extrai informacao do ficheiro dos produtos para um vetor (VProd)
void Store::extrairProdutos()
{
	ifstream Prodfile(FProd);
	string line;

	if (Prodfile.is_open())
	{
		if (!VProducts.empty()) VProducts.clear();

		while (getline(Prodfile, line))
		{
			if (line.find(";") != -1) {
				VProducts.push_back(Product(line.substr(0, line.find_first_of(";") - 1), stof(line.substr(line.find_last_of(";") + 2, line.length() - line.find_last_of(";") - 2))));
			}
		}
		Prodfile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl;  ut.setcolor(15); }
}

//Mostra o ficheiro dos produtos
int Store::mostrarProdutos()
{
	for (unsigned int i = 0; i < VProducts.size(); i++)
	{
		cout << setw(10) << i + 1 << setw(22) << VProducts.at(i).GetProd() << setw(20) << setprecision(1) << fixed << VProducts.at(i).GetPrice() << endl;
	}
	return 0;
}

//Efetua compras, adiciona transacao, adiciona montante gasta ao total do cliente, e caso seja necessario, cria cliente
int Store::efetuarCompras()
{
	unsigned int ref, dig, op;
	string produtos;
	float total = 0;
	string opcao;
	unsigned int id;

	ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Tendo em conta os produtos disponiveis, qual deseja comprar?" << endl;
	ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Quando terminar, por favor digite ";  ut.setcolor(11); cout << " 0";  ut.setcolor(15); cout << ".\n\n";

	//selecao de produtos a comprar
	while (true)
	{
		cin >> ref;

		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			ut.setcolor(4); cout << "> Referencia Invalida!" << endl;
			ut.setcolor(15); cin >> ref;
		}

		if (ref == 0)
			break;
		else {
			if (ref <= VProducts.size())
			{
				produtos.append(VProducts.at(ref - 1).GetProd());
				produtos.append(", ");
				ut.setcolor(7); cout << "> Produto Adicionado!\n\n";  ut.setcolor(15);
				total += VProducts.at(ref - 1).GetPrice();
			}
			else { ut.setcolor(4); cout << "> Este produto nao existe!\n\n";  ut.setcolor(15); }
		}
	}

	//caso nao tenha inserido nenhum produto valido, ou apenas tenha desistido de comprar
	if (produtos.empty())
	{
		ut.setcolor(4); cout << "> Nao introduziu nenhum produto valido." << endl;  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}

	//caso tenha inserido produtos validos
	else
	{
		//confirmacao da compra
		ut.setcolor(14); cout << endl << "> ";  ut.setcolor(15); cout << "Quer comprar o(s) produto(s): ";  ut.setcolor(3); cout << "{ ";  ut.setcolor(15); cout << produtos.substr(0, produtos.size() - 2) << "." << endl;
		ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
		ut.setcolor(7); cout << "1. SIM" << "        " << "2. NAO" << endl << endl;  ut.setcolor(15);
		cout << "Digite a sua opcao: ";  cin >> dig; cout << endl;

		while ((dig != 1) && (dig != 2))
		{
			if (cin.eof())
			{
				cin.clear();
				return 0;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			ut.setcolor(4); cout << "> Digito invalido!" << endl;
			ut.setcolor(15); cout << "Volte a indicar escolha: ";
			cin >> dig;
		}
		if (dig == 1)
		{
			//selecao do cliente a efetuar a compra
			ut.setcolor(14); cout << endl << "> ";  ut.setcolor(15); cout << "Ja e cliente?" << endl;
			ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
			ut.setcolor(7); cout << "1. SIM" << "        " << "2. NAO" << endl << endl;  ut.setcolor(15);
			cout << "Digite a sua opcao: ";  cin >> op; cout << endl;

			while ((op != 1) && (op != 2))
			{
				if (cin.eof())
				{
					cin.clear();
					return 0;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				ut.setcolor(4); cout << "> Digito invalido!" << endl;
				ut.setcolor(15); cout << "Volte a indicar escolha: ";
				cin >> op;
			}

			if (op == 1)
			{
				cout << endl << "Introduza o ID ou Nome do cliente: ";  ut.setcolor(3); cout << "{ ";  ut.setcolor(15); cin.ignore(); getline(cin, opcao);

				while (((clienteExiste(opcao)) == false) || (cin.fail()))
				{
					if (cin.eof())
					{
						cin.clear();
						return 0;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					ut.setcolor(4); cout << "> Este id/nome nao existe!" << endl;
					ut.setcolor(15); cout << "Volte a indicar: ";
					cin >> opcao;
				}

				if (clienteExiste(opcao))
				{
					if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
						id = stoi(opcao, nullptr, 10); // se a opcao for o ID
					else id = 0;
				}
			}
			else if (op == 2)
			{
				criarCliente();
				id = VClients.back().GetId();
			}

			//Display da montante total a pagar
			cout << endl << "Total a pagar: ";  ut.setcolor(3); cout << "{ ";  ut.setcolor(15); cout << total << " euros." << endl;

			//Adicionar compra ao montante do cliente
			for (unsigned int i = 0; i < VClients.size(); i++)
			{
				if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
				{
					VClients.at(i).SetMontante(total);
					id = VClients.at(i).GetId();
				}
			}
			criarTrans(id, produtos);
			ut.setcolor(4); cout << "\n> Compra Efetuada!\n";  ut.setcolor(15);
			Sleep(3000);
			return 0;
		}
		else {
			if (dig == 2)
			{
				ut.setcolor(4); cout << "> Compra Apagada!\n";  ut.setcolor(15);
				ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
				return 0;
			}
			else
			{
				ut.setcolor(4); cerr << "ERRO!" << endl;  ut.setcolor(15);
				ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
				return 0;
			}
		}
	}
	return 0;
}

//Transacoes

//Extrai informacao do ficheiro das transacoes para um vetor (VTrans)
void Store::extrairTransacoes()
{
	ifstream transactionFile(FTrans);
	string line, produtos;
	unsigned int id;
	string data;
	int i = 0;

	if (transactionFile.is_open())
	{
		if (!VTrans.empty()) VTrans.clear();

		while (getline(transactionFile, line))
		{
			vector<string> products;

			if (line.find(";") != -1) {
				id = stoi(line.substr(0, line.find_first_of(";")), nullptr, 10); // define o id do elemento do vetor
				data = line.substr(line.find_first_of(";") + 2, line.find_last_of(";") - line.find_first_of(";") - 3); //define a data do elemento do vetor

				size_t posd1 = data.find("/");
				string strd1 = data.substr(posd1 + 1); //mes + ano
				size_t posd2 = strd1.find("/");

				string dia = data.substr(0, posd1);
				string mes = strd1.substr(0, posd2);
				string ano = strd1.substr(posd2 + 1);

				//adiciona um 0 antes do mes e do dia caso nao tenham so um digito
				if (dia.size() == 1)
					dia = "0" + dia;
				if (mes.size() == 1)
					mes = "0" + mes;

				string datafinal = dia + "/" + mes + "/" + ano;

				produtos = line.substr(line.find_last_of(";") + 2, line.length() - line.find_last_of(";") - 2); //define a string da lista de produtos
				produtos.append(", ");

				while (!(produtos.empty()))
				{
					products.push_back(produtos.substr(0, produtos.find_first_of(",")));
					produtos.erase(0, produtos.find_first_of(",") + 2);
				}
				VTrans.push_back(Transaction(id, datafinal, products)); //cria um novo elemento no vector
				i++;
			}
		}
		transactionFile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl;  ut.setcolor(15); }
}

//Escreve o vetor VTrans no ficheiro de transacoes
int Store::escreverTrans()
{
	ofstream TransFile(FTrans);
	string produtos;

	if (TransFile.is_open())
	{
		TransFile << VTrans.size() << endl; //numero de transacoes no inicio do ficheiro
		for (unsigned int i = 0; i < VTrans.size(); i++)
		{
			TransFile << VTrans.at(i).GetId() << " ; " << VTrans.at(i).GetDate() << " ; ";
			produtos = "";
			for (unsigned int j = 0; j < VTrans.at(i).GetProds().size(); j++)
			{
				produtos.append(VTrans.at(i).GetProds().at(j));
				produtos.append(", ");
			}
			produtos.erase(produtos.size() - 2, 2);
			TransFile << produtos << endl;
		}
		TransFile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl;  ut.setcolor(15); }
	return 0;
}

//Mostra as transacoes efetuadas num intervalo de datas
int Store::transEntreDatas()
{
	int dia1, mes1, ano1, dia2, mes2, ano2;
	string d1, m1, a1, d2, m2, a2;
	string data1, data2, datadig1, datadig2, produtos;
	int dataint1, dataint2, DataInteira;
	string DataDigitos, DataCompleta;
	int c = 0; //contador

	cout << endl;
	ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Tera que escolher duas datas para visualizar as transacoes efetuadas nesse intervalo." << endl;
	ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Introduza a primeira data:" << endl << endl;
	cout << "> Dia: "; cin >> dia1; cout << "> Mes: "; cin >> mes1; cout << "> Ano: "; cin >> ano1;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> dia1;
	}

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> mes1;
	}

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> ano1;
	}

	//Verifica se a primeira data é valida
	if (dataValida(dia1, mes1, ano1))
	{
		ut.setcolor(7); cout << "Data Valida!\n";  ut.setcolor(15);
	}
	else
	{
		ut.setcolor(4); cout << "Data Invalida.\n";  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}
	cout << endl;

	ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Introduza a segunda data: " << endl;
	cout << "> Dia: "; cin >> dia2; cout << "> Mes: "; cin >> mes2; cout << "> Ano: "; cin >> ano2;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> dia2;
	}

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> mes2;
	}

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> ano2;
	}

	//Verifica se a segunda data é valida
	if (dataValida(dia2, mes2, ano2))
	{
		ut.setcolor(7); cout << "Data Valida!\n";  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
	}
	else
	{
		ut.setcolor(4); cout << "Data Invalida.\n";  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}

	//Formata datas para DD/MM/AAAA
	d1 = to_string(dia1);
	m1 = to_string(mes1);
	a1 = to_string(ano1);
	d2 = to_string(dia2);
	m2 = to_string(mes2);
	a2 = to_string(ano2);

	if (d1.size() == 1)
		d1.insert(0, "0");
	if (d2.size() == 1)
		d2.insert(0, "0");

	if (m1.size() == 1)
		m1.insert(0, "0");
	if (m2.size() == 1)
		m2.insert(0, "0");

	data1.append(d1); data1.append("/"); data1.append(m1); data1.append("/"); data1.append(a1);
	data2.append(d2); data2.append("/"); data2.append(m2); data2.append("/"); data2.append(a2);

	//converte a primeira data para um numero inteiro, invertido
	datadig1 = data1.substr(data1.find_last_of("/") + 1, data1.size() - data1.find_last_of("/") - 1);  //ano
	datadig1.append(data1.substr(data1.find_first_of("/") + 1, data1.find_last_of("/") - data1.find_first_of("/") - 1));  //adiciona mes ao fim do ano
	datadig1.append(data1.substr(0, data1.find_first_of("/"))); //adiciona dia ao fim do ano|mes : ficando anomesdia
	dataint1 = stoi(datadig1, nullptr, 10); //converte a string data digitos para um inteiro

	//converte a segunda data para um numero inteiro, invertido
	datadig2 = data2.substr(data2.find_last_of("/") + 1, data2.size() - data2.find_last_of("/") - 1);  //ano
	datadig2.append(data2.substr(data2.find_first_of("/") + 1, data2.find_last_of("/") - data2.find_first_of("/") - 1));  //adiciona mes ao fim do ano
	datadig2.append(data2.substr(0, data2.find_first_of("/"))); //adiciona dia ao fim do ano|mes : ficando anomesdia
	dataint2 = stoi(datadig2, nullptr, 10); //converte a string data digitos para um inteiro

	ut.clearScreen();
	ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Transacoes entre: " << data1 << " e " << data2 << endl << endl;
	ut.setcolor(7);  cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);

	//Display das transacoes
	for (unsigned int i = 0; i < VTrans.size(); i++)
	{
		DataCompleta = VTrans.at(i).GetDate(); // data completa
		DataDigitos = DataCompleta.substr(DataCompleta.find_last_of("/") + 1, DataCompleta.size() - DataCompleta.find_last_of("/") - 1);  //ano
		DataDigitos.append(DataCompleta.substr(DataCompleta.find_first_of("/") + 1, DataCompleta.find_last_of("/") - DataCompleta.find_first_of("/") - 1));  //adiciona mes ao fim do ano
		DataDigitos.append(DataCompleta.substr(0, DataDigitos.find_first_of("/"))); //adiciona dia ao fim do ano|mes : ficando anomesdia
		DataInteira = stoi(DataDigitos, nullptr, 10); //converte a string data digitos para um inteiro

		if ((DataInteira >= dataint1) && (DataInteira <= dataint2))
		{
			c += 1;
			cout << setw(5) << VTrans.at(i).GetId();
			cout << setw(15) << VTrans.at(i).GetDate();
			produtos = "";

			for (unsigned int j = 0; j < VTrans.at(i).GetProds().size(); j++)
			{
				if (j == VTrans.at(i).GetProds().size() - 1)
				{
					produtos.append(VTrans.at(i).GetProds().at(j));
				}
				else
				{
					produtos.append(VTrans.at(i).GetProds().at(j));
					produtos.append(", ");
				}

			}
			cout << setw(34) << produtos << endl;
		}
	}
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
	if (c == 0)
	{
		ut.setcolor(7); cout << endl << "ATENCAO: "; ut.setcolor(15); cout << "Nao existe nenhuma transacao efetuada \n         entre estas datas.\n" << endl;
	}
	ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
	return 0;
}

//Mostra as transacoes efetuadas num determinado dia
int Store::transDia()
{
	int dia1, mes1, ano1;
	string d1, m1, a1;
	string data1, datadig1, produtos;
	int dataint1, DataInteira;
	string DataDigitos, DataCompleta;

	cout << endl;
	ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Introduza a data que pretende visualizar." << endl;
	cout << "> Dia: "; cin >> dia1; cout << "> Mes: "; cin >> mes1; cout << "> Ano: "; cin >> ano1;
	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> dia1;
	}

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> mes1;
	}

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> ano1;
	}

	if (dataValida(dia1, mes1, ano1))
	{
		ut.setcolor(7); cout << "Data Valida!\n";  ut.setcolor(15);
	}
	else
	{
		ut.setcolor(4); cout << "Data Invalida.\n";  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}

	d1 = to_string(dia1);
	m1 = to_string(mes1);
	a1 = to_string(ano1);

	if (d1.size() == 1)
		d1.insert(0, "0");
	if (m1.size() == 1)
		m1.insert(0, "0");

	data1.append(d1); data1.append("/"); data1.append(m1); data1.append("/"); data1.append(a1);

	//converte a data1 num inteiro
	datadig1 = data1.substr(data1.find_last_of("/") + 1, data1.size() - data1.find_last_of("/") - 1);  //ano
	datadig1.append(data1.substr(data1.find_first_of("/") + 1, data1.find_last_of("/") - data1.find_first_of("/") - 1));  //adiciona mes ao fim do ano
	datadig1.append(data1.substr(0, data1.find_first_of("/"))); //adiciona dia ao fim do ano|mes : ficando anomesdia
	dataint1 = stoi(datadig1, nullptr, 10); //converte a string data digitos para um inteiro

	bool DataExiste = transExisteData(dataint1);

	if (DataExiste)
	{
		cout << endl;
		ut.setcolor(7); cout << "Foi efetuada alguma transacao neste dia." << endl;  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		ut.clearScreen();
		ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Transacoes do dia: " << data1 << endl << endl;
		ut.setcolor(7); cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
		ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);

		for (unsigned int i = 0; i < VTrans.size(); i++)
		{
			DataCompleta = VTrans.at(i).GetDate(); // data completa
			DataDigitos = DataCompleta.substr(DataCompleta.find_last_of("/") + 1, DataCompleta.size() - DataCompleta.find_last_of("/") - 1);  //ano
			DataDigitos.append(DataCompleta.substr(DataCompleta.find_first_of("/") + 1, DataCompleta.find_last_of("/") - DataCompleta.find_first_of("/") - 1));  //adiciona mes ao fim do ano
			DataDigitos.append(DataCompleta.substr(0, DataDigitos.find_first_of("/"))); //adiciona dia ao fim do ano|mes : ficando anomesdia
			DataInteira = stoi(DataDigitos, nullptr, 10); //converte a string data digitos para um inteiro

			if (DataInteira == dataint1)
			{
				cout << setw(5) << VTrans.at(i).GetId();
				cout << setw(15) << VTrans.at(i).GetDate();
				produtos = "";

				for (unsigned int j = 0; j < VTrans.at(i).GetProds().size(); j++)
				{
					if (j == VTrans.at(i).GetProds().size() - 1)
					{
						produtos.append(VTrans.at(i).GetProds().at(j));
					}
					else
					{
						produtos.append(VTrans.at(i).GetProds().at(j));
						produtos.append(", ");
					}

				}
				cout << setw(34) << produtos << endl;
			}
		}
		ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}
	else
	{
		cout << endl;
		ut.setcolor(4); cout << "> Nao foi efetuada nenhuma transacao neste dia." << endl;  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
		return 0;
	}
	return 0;
}

//Verifica se a transacao com determinado ID existe
bool Store::transExisteID(unsigned int id)
{
	int a = 0;

	for (unsigned int i = 0; i < VTrans.size(); i++)
	{
		if (id == VTrans.at(i).GetId())
			a = a + 1;
	}
	if (a > 0)
		return true;
	else return false;
}

//Mostra as transacoes efetuadas por um determinado cliente
int Store::transIndividual()
{
	int id;
	string opcao, produtos;

	cout << endl << "Introduza o ID do cliente que pretende visualizar: ";  cin >> id; cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> id;
	}

	if (transExisteID(id))
	{
		if (clienteExiste(to_string(id)))
		{
			for (unsigned int i = 0; i < VClients.size(); i++)
			{
				if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
				{
					ut.clearScreen();
					ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Transacoes do cliente: " << VClients.at(i).GetNome() << endl << endl;
					ut.setcolor(7);  cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
					ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
				}
			}
		}
		else
		{
			ut.clearScreen();
			ut.setcolor(14); cout << "> ";  ut.setcolor(15); cout << "Transacoes de um cliente eliminado." << endl << endl;
			ut.setcolor(7);  cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
			ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
		}

		for (unsigned int w = 0; w < VTrans.size(); w++)
		{
			if (id == VTrans.at(w).GetId())
			{
				cout << setw(5) << VTrans.at(w).GetId();
				cout << setw(15) << VTrans.at(w).GetDate();
				produtos = "";

				for (unsigned int j = 0; j < VTrans.at(w).GetProds().size(); j++)
				{
					if (j == VTrans.at(w).GetProds().size() - 1)
					{
						produtos.append(VTrans.at(w).GetProds().at(j));
					}
					else
					{
						produtos.append(VTrans.at(w).GetProds().at(j));
						produtos.append(", ");
					}

				}
				cout << setw(34) << produtos << endl;
			}
		}
		ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
	}
	else {
		ut.setcolor(4); cout << "> Nao existe nenhuma transacao com este ID." << endl;  ut.setcolor(15);
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar."; ut.setcolor(15); getchar();
	}
	getchar();
	return 0;
}

//Verifica se existe alguma transacao efetuada com esta data
bool Store::transExisteData(int dataint1)
{
	string DataDigitos, DataCompleta;
	int DataInteira;
	int a = 0;
	for (unsigned int i = 0; i < VTrans.size(); i++)
	{
		DataCompleta = VTrans.at(i).GetDate(); // data completa
		DataDigitos = DataCompleta.substr(DataCompleta.find_last_of("/") + 1, DataCompleta.size() - DataCompleta.find_last_of("/") - 1);  //ano
		DataDigitos.append(DataCompleta.substr(DataCompleta.find_first_of("/") + 1, DataCompleta.find_last_of("/") - DataCompleta.find_first_of("/") - 1));  //adiciona mes ao fim do ano
		DataDigitos.append(DataCompleta.substr(0, DataDigitos.find_first_of("/"))); //adiciona dia ao fim do ano|mes : ficando anomesdia
		DataInteira = stoi(DataDigitos, nullptr, 10); //converte a string data digitos para um inteiro

		if (DataInteira == dataint1)
			a = a + 1;
	}

	if (a > 0)
		return true;
	else return false;
}

//Mostra o ficheiro das transacoes
int Store::mostrarTransacoes()
{
	string produtos;

	for (unsigned int i = 0; i < VTrans.size(); i++)
	{
		cout << setw(5) << VTrans.at(i).GetId();
		cout << setw(16) << VTrans.at(i).GetDate();
		produtos = "";

		for (unsigned int j = 0; j < VTrans.at(i).GetProds().size(); j++)
		{
			if (j == VTrans.at(i).GetProds().size() - 1)
			{
				produtos.append(VTrans.at(i).GetProds().at(j));
			}
			else
			{
				produtos.append(VTrans.at(i).GetProds().at(j));
				produtos.append(", ");
			}

		}
		cout << setw(34) << produtos << endl;
	}
	return 0;
}

//Cria transacao
void Store::criarTrans(int id, string produtos)
{
	vector<string> products;
	while (!(produtos.empty()))
	{
		products.push_back(produtos.substr(0, produtos.find_first_of(",")));
		produtos.erase(0, produtos.find_first_of(",") + 2);
	}

	VTrans.push_back(Transaction(id, dataAtual(), products));
	return;
}

//Publicidade

// estrutura para o vetor de produtos recomendados
struct ProdutosFrequencia
{
	string produto;
	int total;
};

// algoritmo que obtem o valor maximo de um vetor de inteiros
template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
{
	if (first == last) return last;
	ForwardIterator largest = first;

	while (++first != last)
		if (*largest < *first)    // or: if (comp(*largest,*first)) for version (2)
			largest = first;
	return largest;
}


// publicidade para um cliente alvo
int Store::pubIndividual()
{
	int id;
	cout << endl << "Introduza o ID do cliente: ";  cin >> id;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Input invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> id;
	}

	if (transExisteID(id)) //verifica se o cliente realizou transacoes
	{
		vector<unsigned int> all_Clients;    //vetor com os id clientes existentes nas transacoes

		for (unsigned int i = 0; i < VTrans.size(); i++) //percorre o vetor de transacoes
		{
			if (find(all_Clients.begin(), all_Clients.end(), VTrans[i].GetId()) == all_Clients.end()) //verifica se o id da transaçao na posiçao i ja existe no vetor all_clients
			{
				all_Clients.push_back(VTrans[i].GetId()); //adiciona se nao existir
			}
		}

		for (unsigned int i = 0; i < all_Clients.size(); i++)
		{
			Client_IdIx.insert(make_pair(all_Clients.at(i), i)); //preenche o map de clientes com os clientes existentes no vetor all_clients e a sua posiçao
		}

		for (unsigned int i = 0; i < VProducts.size(); i++)
		{
			Prod_Ix.insert(make_pair(VProducts.at(i).GetProd(), i)); //preenche o map de produtos com os produtos existentes no vetor e a sua posiçao
		}

		//criacao da matriz
		vector<vector<bool>> matrix_Target(all_Clients.size(), vector<bool>(VProducts.size(), false)); //inicia a matriz a false

		for (unsigned int i = 0; i < VTrans.size(); i++) //percorre o vetor produtos
		{
			for (unsigned int a = 0; a < VTrans.at(i).GetProds().size(); a++) //percorre o vetor de produtos em cada transacao
			{
				matrix_Target[Client_IdIx[VTrans[i].GetId()]][Prod_Ix[VTrans[i].GetProds().at(a)]] = true; // identifi  o cliente de cada transacao e na linha desse cliente na matriz coloque a true os produtos registados nessa transação
			}
		}

		//display matriz
		/*for (int i = 0; i < matrix_Target.size(); i++)
		{
			for (int a = 0; a < matrix_Target[i].size(); a++)
			{
				cout << matrix_Target[i][a];
			}
			cout << endl;
		}*/

		vector<unsigned int> bought_Products; // vetor com o indice dos produtos comprados pelo cliente alvo

		// preenche vetor bought_Products
		for (unsigned int i = 0; i < matrix_Target.at(Client_IdIx.at(id)).size(); i++)
			if (matrix_Target.at(Client_IdIx.at(id)).at(i))
				bought_Products.push_back(i);

		vector <unsigned int> client_Index; // vetor com os indices dos clientes que compraram o mesmo produto que o cliente alvo

		// percorre a matriz para preencher o vetor client_Index
		for (unsigned int i = 0; i < matrix_Target.size(); i++)
		{
			if (i == Client_IdIx.at(id)) // salta a linha que é igual ao cliente alvo
				continue;

			bool comprouOsMesmos = true;

			for (auto c : bought_Products)
			{
				if (matrix_Target.at(i).at(c) != matrix_Target.at(Client_IdIx.at(id)).at(c))
				{
					comprouOsMesmos = false;
					break;
				}
			}

			if (comprouOsMesmos)
				client_Index.push_back(i);
		}


		vector<string> products_Recommend; //vetor de potenciais produtos para recomendar

		for (unsigned int j = 0; j < client_Index.size(); j++)
		{
			for (unsigned int w = 0; w < matrix_Target.at(client_Index.at(j)).size(); w++) //percorre cada produto de cada cliente do vetor client_Index
			{
				if (matrix_Target.at(client_Index.at(j)).at(w)) // se tiver comprado produto da coluna w (true)
				{
					if (find(bought_Products.begin(), bought_Products.end(), w) == bought_Products.end())
					{
						products_Recommend.push_back(VProducts.at(w).GetProd());
					}
				}
			}
		}

		// caso nao haja nenhum produto a recomendar
		if (products_Recommend.size() == 0)
		{
			// vetor com todos os produtos comprados pelos clientes
			vector<string> todos_Produtos;

			for (unsigned int i = 0; i < VTrans.size(); i++)
			{
				for (unsigned int j = 0; j < VTrans.at(i).GetProds().size(); j++)
				{
					todos_Produtos.push_back(VTrans.at(i).GetProds().at(j));
				}
			}

			// vetor com os produtos comprados pelo cliente alvo
			vector<string> clienteAlvo_produtos;

			for (unsigned int i = 0; i < VTrans.size(); i++)
			{
				if (id == VTrans.at(i).GetId())
				{
					for (unsigned int j = 0; j < VTrans.at(i).GetProds().size(); j++)
					{
						clienteAlvo_produtos.push_back(VTrans.at(i).GetProds().at(j));
					}
				}
			}

			for (int i = 0; i < todos_Produtos.size(); i++)
			{
				if (find(clienteAlvo_produtos.begin(), clienteAlvo_produtos.end(), todos_Produtos.at(i)) != clienteAlvo_produtos.end())
				{
					todos_Produtos.erase(todos_Produtos.begin() + i);
					i--;
				}
			}

			// cria um vetor de todos os produtos com a estrutura (nome do produto, numero de vezes que aparece)
			vector<ProdutosFrequencia> vector_All;

			for (int i = 0; i < todos_Produtos.size(); i++)
			{
				int t = 0; //numero de vezes que cada produto repete
				for (int j = 0; j < todos_Produtos.size(); j++)
				{
					if (todos_Produtos.at(i) == todos_Produtos.at(j))
						t++;
				}
				ProdutosFrequencia novoelem; //criacao novo elemento
				novoelem.produto = todos_Produtos.at(i);
				novoelem.total = t;
				vector_All.push_back(novoelem);
			}

			// elimina os produtos repetidos, de maneira a ficar apenas uma vez cada produto
			if (vector_All.size() > 1)
			{
				for (int i = 0; i < vector_All.size(); i++)
				{
					for (int j = 1; j < vector_All.size(); j++)
					{
						if (vector_All.at(i).produto == vector_All.at(j).produto)
						{
							vector_All.erase(vector_All.begin() + j);
							j = i + 1;
						}
					}
				}

				if (vector_All.size() > 1)
				{
					// cria um vetor com todos os totais dos produtos, de maneira a calcular o total maximo, ou seja, o produto mais frequente
					vector<int> total_All;
					vector<int>::iterator result_All;
					int totalMaximo_All;
					for (int i = 0; i < vector_All.size(); i++)
					{
						total_All.push_back(vector_All.at(i).total);
					}
					result_All = std::max_element(total_All.begin(), total_All.end()); // retorna a posicao do maior elemento (comecando em 1)
					totalMaximo_All = total_All.at(std::distance(total_All.begin(), result_All));

					//display dos produtos recomendados, os mais frequentes
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < vector_All.size(); i++)
					{
						if (totalMaximo_All == vector_All.at(i).total)
						{
							ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << vector_All.at(i).produto << endl;
						}
					}
				}
				else
				{
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < vector_All.size(); i++)
					{
						ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << vector_All.at(i).produto << endl;
					}
				}
			}
			else
			{
				ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
				for (int i = 0; i < vector_All.size(); i++)
				{
					ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << vector_All.at(i).produto << endl;
				}
			}
		}

		else {
			// cria um vetor de produtos recomendados com a estrutura (nome do produto, numero de vezes que aparece)
			vector<ProdutosFrequencia> VPR;

			for (int i = 0; i < products_Recommend.size(); i++)
			{
				int t = 0; //numero de vezes que cada produto repete
				for (int j = 0; j < products_Recommend.size(); j++)
				{
					if (products_Recommend.at(i) == products_Recommend.at(j))
						t++;
				}
				ProdutosFrequencia novoelem; //criacao novo elemento
				novoelem.produto = products_Recommend.at(i);
				novoelem.total = t;
				VPR.push_back(novoelem);
			}


			// elimina os produtos repetidos, de maneira a ficar apenas uma vez cada produto
			if (VPR.size() > 1)
			{
				for (int i = 0; i < VPR.size(); i++)
				{
					for (int j = 1; j < VPR.size(); j++)
					{
						if (VPR.at(i).produto == VPR.at(j).produto)
						{
							VPR.erase(VPR.begin() + j);
							j = i + 1;
						}
					}
				}
				if (VPR.size() > 1)
				{
					// cria um vetor com todos os totais dos produtos, de maneira a calcular o total maximo, ou seja, o produto mais frequente
					vector<int> Totais;
					vector<int>::iterator result;
					int totalMaximo;
					for (int i = 0; i < VPR.size(); i++)
					{
						Totais.push_back(VPR.at(i).total);
					}
					result = std::max_element(Totais.begin(), Totais.end()); // retorna a posicao do maior elemento (comecando em 1)
					totalMaximo = Totais.at(std::distance(Totais.begin(), result));

					//display dos produtos recomendados, os mais frequentes
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < VPR.size(); i++)
					{
						if (totalMaximo == VPR.at(i).total)
						{
							ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << VPR.at(i).produto << endl;
						}
					}
				}
				else
				{
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < VPR.size(); i++)
					{
						ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << VPR.at(i).produto << endl;
					}
				}
			}
			else
			{
				ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
				for (int i = 0; i < VPR.size(); i++)
				{
					ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << VPR.at(i).produto << endl;
				}
			}
		}
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar.\n"; ut.setcolor(15); getchar();
	}
	else
	{
		ut.setcolor(4); cout << "\nEste cliente nao efetuou nenhuma transacao.\n";
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar.\n"; ut.setcolor(15); getchar();
	}

	getchar();
	return 0;
}

int Store::pubBottom10()
{
	vector<string> produtos_maisfrequentes; //vetor com o produto, ou produtos, mais frequentes do bottom 10

	vector <Client> VNB10; // vetor de clientes menos os do bottom 10 (Vector Not Bottom 10)
	vector <Client> VB10 = VClients; //VB10 é um vetor igual ao VClients que vai ser ordenado
	sort(VB10.begin(), VB10.end(), [](Client &a, Client &b) {return a.GetMontante() < b.GetMontante(); }); //ordena o vetor VB10

	if (VB10.size() < 10)
	{
		ut.setcolor(4); cout << "\nVisto que nao ha pelo menos 11 clientes, esta funcao nao pode ser efetuada.\n";
		ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar.\n"; ut.setcolor(15); getchar();
	}
	else
	{
		VB10.erase(VB10.begin() + 10, VB10.end()); //VB10 passa a ser um vetor com apenas os 10 primeiros elementos de VClients

		//vetor com os id's dos clientes presentes no bottom 10
		vector<unsigned int> VB10_id;
		for (unsigned int i = 0; i < VB10.size(); i++)
		{
			VB10_id.push_back(VB10.at(i).GetId());
		}


		//remocao dos vetores do bottom 10 ao vetor de todos os clientes, ficando estes em VNB10
		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if (find(VB10_id.begin(), VB10_id.end(), VClients.at(i).GetId()) == VB10_id.end())
				VNB10.push_back(Client(VClients.at(i).GetId(), VClients.at(i).GetNome(), VClients.at(i).GetData(), VClients.at(i).GetMontante()));
		}


		vector <Transaction> TB10; //vetor das transacoes do Bottom 10
		//retira as transacoes dos clientes presentes no bottom 10 e adiciona ao vetor TB10
		for (unsigned int i = 0; i < VB10.size(); i++)
		{
			for (unsigned int j = 0; j < VTrans.size(); j++)
			{
				if (VB10.at(i).GetId() == VTrans.at(j).GetId())
					TB10.push_back(Transaction(VTrans.at(j).GetId(), VTrans.at(j).GetDate(), VTrans.at(j).GetProds()));
			}
		}

		vector <Transaction> TNB10; //vetor das transacoes de todos os clientes, menos Bottom 10 (Transactions Not Bottom 10)
		//retira as transacoes de todos os clientes, menos bottom 10, e adiciona ao vetor TNB10
		for (unsigned int i = 0; i < VNB10.size(); i++)
		{
			for (unsigned int j = 0; j < VTrans.size(); j++)
			{
				if (VNB10.at(i).GetId() == VTrans.at(j).GetId())
					TNB10.push_back(Transaction(VTrans.at(j).GetId(), VTrans.at(j).GetDate(), VTrans.at(j).GetProds()));
			}
		}

		vector<string> produtos_TB10; //vetor com todos os produtos comprados pelo bottom 10
		//preenche vetor
		for (unsigned int i = 0; i < TB10.size(); i++)
		{
			for (unsigned int j = 0; j < TB10.at(i).GetProds().size(); j++)
			{
				produtos_TB10.push_back(TB10.at(i).GetProds().at(j));
			}
		}

		//PREENCHE VETOR DOS PRODUTOS MAIS FREQUENTES DO BOTTOM 10//
		if (produtos_TB10.size() > 1)
		{
			// cria um vetor com a estrutura (nome do produto, numero de vezes que aparece - frequencia)
			vector<ProdutosFrequencia> VPFreq;

			for (int i = 0; i < produtos_TB10.size(); i++)
			{
				int t = 0; //numero de vezes que cada produto repete
				for (int j = 0; j < produtos_TB10.size(); j++)
				{
					if (produtos_TB10.at(i) == produtos_TB10.at(j))
						t++;
				}
				ProdutosFrequencia novoelem; //criacao novo elemento
				novoelem.produto = produtos_TB10.at(i);
				novoelem.total = t;
				VPFreq.push_back(novoelem);
			}


			// elimina os produtos repetidos, de maneira a ficar apenas uma vez cada produto
			if (VPFreq.size() > 1)
			{
				for (int i = 0; i < VPFreq.size(); i++)
				{
					for (int j = 1; j < VPFreq.size(); j++)
					{
						if (VPFreq.at(i).produto == VPFreq.at(j).produto)
						{
							VPFreq.erase(VPFreq.begin() + j);
							j = i + 1;
						}
					}
				}

				if (VPFreq.size() > 1)
				{
					// cria um vetor com todos os totais dos produtos, de maneira a calcular o total maximo, ou seja, o produto mais frequente
					vector<int> Totais;
					vector<int>::iterator result;
					int totalMaximo;
					for (int i = 0; i < VPFreq.size(); i++)
					{
						Totais.push_back(VPFreq.at(i).total);
					}
					result = std::max_element(Totais.begin(), Totais.end()); // retorna a posicao do maior elemento (comecando em 1)
					totalMaximo = Totais.at(std::distance(Totais.begin(), result));

					for (int i = 0; i < VPFreq.size(); i++)
					{
						if (totalMaximo == VPFreq.at(i).total)
						{
							produtos_maisfrequentes.push_back(VPFreq.at(i).produto);
						}
					}
				}
				else
				{
					for (int i = 0; i < VPFreq.size(); i++)
					{
						produtos_maisfrequentes.push_back(VPFreq.at(i).produto);
					}
				}
			}
			else
			{
				for (int i = 0; i < VPFreq.size(); i++)
				{
					produtos_maisfrequentes.push_back(VPFreq.at(i).produto);
				}
			}
		}
		else
		{
			for (int i = 0; i < produtos_TB10.size(); i++)
			{
				produtos_maisfrequentes.push_back(produtos_TB10.at(i));
			}
		}

		for (unsigned int i = 0; i < VNB10.size(); i++)
		{
			ClientNB10_IdIx.insert(make_pair(VNB10.at(i).GetId(), i)); //preenche o map de clientes que nao sao dos bottom10 com os clientes existentes no vetor VNB10 e a sua posiçao
		}

		for (unsigned int i = 0; i < VProducts.size(); i++)
		{
			Prod_Ix.insert(make_pair(VProducts.at(i).GetProd(), i)); //preenche o map de produtos com os produtos existentes no vetor e a sua posiçao
		}

		//criacao da matriz
		vector<vector<bool>> matrix_NB10(VNB10.size(), vector<bool>(VProducts.size(), false)); //inicia a matriz dos clientes que nao sao dos bottom10 a false

		for (unsigned int i = 0; i < TNB10.size(); i++) //percorre o vetor transacoes
		{
			for (unsigned int a = 0; a < TNB10.at(i).GetProds().size(); a++) //percorre o vetor de produtos em cada transacao
			{
				matrix_NB10[ClientNB10_IdIx[TNB10.at(i).GetId()]][Prod_Ix[TNB10.at(i).GetProds().at(a)]] = true; // identifica o cliente de cada transacao e na linha desse cliente na matriz coloque a true os produtos registados nessa transação
			}
		}

		/*
		//display matriz
		for (int i = 0; i < matrix_NB10.size(); i++)
		{
			for (int a = 0; a < matrix_NB10[i].size(); a++)
			{
				cout << matrix_NB10[i][a];
			}
			cout << endl;
		}
		*/

		vector <bool> cB10(VProducts.size()); //vetor de booleanos com true na posiçao dos produdos mais frequentes comprados pelos bottom10 no VProducts

		for (int i = 0; i < produtos_maisfrequentes.size(); i++)
		{
			cB10.at(Prod_Ix[produtos_maisfrequentes[i]]) = true;
		}


		vector<unsigned int> bought_Products; // vetor com o indice dos produtos comprados pelo cliente B10

		 // preenche vetor bought_Products
		for (unsigned int i = 0; i < cB10.size(); i++)
			if (cB10.at(i))
				bought_Products.push_back(i);


		vector <unsigned int> client_Index; // vetor com os indices dos clientes que compraram o mesmo produto que o cliente B10

		// percorre a matriz para preencher o vetor client_Index
		for (unsigned int i = 0; i < matrix_NB10.size(); i++)
		{

			bool comprouOsMesmos = true;

			for (auto c : bought_Products)
			{
				if (matrix_NB10.at(i).at(c) != cB10.at(c))
				{
					comprouOsMesmos = false;
					break;
				}
			}

			if (comprouOsMesmos)
				client_Index.push_back(i);
		}


		vector<string> products_Recommend; //vetor de potenciais produtos para recomendar

		for (unsigned int j = 0; j < client_Index.size(); j++)
		{
			for (unsigned int w = 0; w < matrix_NB10.at(client_Index.at(j)).size(); w++) //percorre cada produto de cada cliente do vetor client_Index
			{
				if (matrix_NB10.at(client_Index.at(j)).at(w)) // se tiver comprado produto da coluna w (true)
				{
					if (find(bought_Products.begin(), bought_Products.end(), w) == bought_Products.end())
					{
						products_Recommend.push_back(VProducts.at(w).GetProd());
					}
				}
			}
		}

		if (products_Recommend.size() == 0)
		{
			// vetor com todos os produtos comprados pelos clientes
			vector<string> todos_Produtos;

			for (unsigned int i = 0; i < TNB10.size(); i++)
			{
				for (unsigned int j = 0; j < TNB10.at(i).GetProds().size(); j++)
				{
					todos_Produtos.push_back(TNB10.at(i).GetProds().at(j));
				}
			}

			// remocao dos produtos frequentes dos bottom 10
			for (int i = 0; i < todos_Produtos.size(); i++)
			{
				if (find(produtos_maisfrequentes.begin(), produtos_maisfrequentes.end(), todos_Produtos.at(i)) != produtos_maisfrequentes.end())
				{
					todos_Produtos.erase(todos_Produtos.begin() + i);
					i--;
				}
			}

			// cria um vetor de todos os produtos com a estrutura (nome do produto, numero de vezes que aparece)
			vector<ProdutosFrequencia> vector_All;

			for (int i = 0; i < todos_Produtos.size(); i++)
			{
				int t = 0; //numero de vezes que cada produto repete
				for (int j = 0; j < todos_Produtos.size(); j++)
				{
					if (todos_Produtos.at(i) == todos_Produtos.at(j))
						t++;
				}
				ProdutosFrequencia novoelem; //criacao novo elemento
				novoelem.produto = todos_Produtos.at(i);
				novoelem.total = t;
				vector_All.push_back(novoelem);
			}

			// elimina os produtos repetidos, de maneira a ficar apenas uma vez cada produto
			if (vector_All.size() > 1)
			{
				for (int i = 0; i < vector_All.size(); i++)
				{
					for (int j = 1; j < vector_All.size(); j++)
					{
						if (vector_All.at(i).produto == vector_All.at(j).produto)
						{
							vector_All.erase(vector_All.begin() + j);
							j = i + 1;
						}
					}
				}

				if (vector_All.size() > 1)
				{
					// cria um vetor com todos os totais dos produtos, de maneira a calcular o total maximo, ou seja, o produto mais frequente
					vector<int> total_All;
					vector<int>::iterator result_All;
					int totalMaximo_All;
					for (int i = 0; i < vector_All.size(); i++)
					{
						total_All.push_back(vector_All.at(i).total);
					}
					result_All = std::max_element(total_All.begin(), total_All.end()); // retorna a posicao do maior elemento (comecando em 1)
					totalMaximo_All = total_All.at(std::distance(total_All.begin(), result_All));

					//display dos produtos recomendados, os mais frequentes
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < vector_All.size(); i++)
					{
						if (totalMaximo_All == vector_All.at(i).total)
						{
							ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << vector_All.at(i).produto << endl;
						}
					}
				}
				else
				{
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < vector_All.size(); i++)
					{
						ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << vector_All.at(i).produto << endl;
					}
				}
			}
			else
			{
				ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
				for (int i = 0; i < vector_All.size(); i++)
				{
					ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << vector_All.at(i).produto << endl;
				}
			}
		}

		else {
			// cria um vetor de produtos recomendados com a estrutura (nome do produto, numero de vezes que aparece)
			vector<ProdutosFrequencia> VPR;

			for (int i = 0; i < products_Recommend.size(); i++)
			{
				int t = 0; //numero de vezes que cada produto repete
				for (int j = 0; j < products_Recommend.size(); j++)
				{
					if (products_Recommend.at(i) == products_Recommend.at(j))
						t++;
				}
				ProdutosFrequencia novoelem; //criacao novo elemento
				novoelem.produto = products_Recommend.at(i);
				novoelem.total = t;
				VPR.push_back(novoelem);
			}


			// elimina os produtos repetidos, de maneira a ficar apenas uma vez cada produto
			if (VPR.size() > 1)
			{
				for (int i = 0; i < VPR.size(); i++)
				{
					for (int j = 1; j < VPR.size(); j++)
					{
						if (VPR.at(i).produto == VPR.at(j).produto)
							VPR.erase(VPR.begin() + j);
					}
				}
				if (VPR.size() > 1)
				{
					// cria um vetor com todos os totais dos produtos, de maneira a calcular o total maximo, ou seja, o produto mais frequente
					vector<int> Totais;
					vector<int>::iterator result;
					int totalMaximo;
					for (int i = 0; i < VPR.size(); i++)
					{
						Totais.push_back(VPR.at(i).total);
					}
					result = std::max_element(Totais.begin(), Totais.end()); // retorna a posicao do maior elemento (comecando em 1)
					totalMaximo = Totais.at(std::distance(Totais.begin(), result));

					//display dos produtos recomendados, os mais frequentes
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < VPR.size(); i++)
					{
						if (totalMaximo == VPR.at(i).total)
						{
							ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << VPR.at(i).produto << endl;
						}
					}
					ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar.\n"; ut.setcolor(15); getchar();
				}
				else
				{
					ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
					for (int i = 0; i < VPR.size(); i++)
					{
						ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << VPR.at(i).produto << endl;
					}
					ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar.\n"; ut.setcolor(15); getchar();
				}
			}
			else
			{
				ut.setcolor(14); cout << "\n> ";  ut.setcolor(15); cout << "Produto(s) recomendado(s):\n";
				for (int i = 0; i < VPR.size(); i++)
				{
					ut.setcolor(11); cout << "   - ";  ut.setcolor(15); cout << VPR.at(i).produto << endl;
				}
				ut.setcolor(4); cout << "\nPressione qualquer tecla para voltar.\n"; ut.setcolor(15); getchar();
			}

		}
	}

	getchar();
	return 0;

}