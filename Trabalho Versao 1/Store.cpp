#include "Store.h"

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
string Store::DataAtual() {
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

//Verifica se o ano é bisexto
bool Store::Bisexto(int ano)
{
	if ((ano % 400 == 0) && (ano % 100 == 0))
		return true;
	else
		if ((ano % 4 == 0) && (ano % 100 != 0))
			return true;
		else return false;
}

//Retorna total de dias do mes de um determinado ano
int Store::Dias(int mes, int ano)
{
	bool B = Bisexto(ano);

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
bool Store::DataValida(int Dia, int Mes, int Ano)
{
	int DTotal;
	bool B = Bisexto(Ano);

	if ((Mes > 0) && (Mes <= 12))
	{
		DTotal = Dias(Mes, Ano);
		if ((Dia <= DTotal) && (Dia > 0))
			return true;
		else return false;
	}
	else return false;
}

//Utilidades

void Store::setcolor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

//Menus

//MENU - Visualizar Informacao
int Store::VisualizarInformacao()
{
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  setcolor(3); cout << "Supermercado  Vende++";  setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~                ";  setcolor(7); cout << "VISUALIZAR INFORMACAO";  setcolor(15); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	setcolor(7);
	cout << setw(13) << "1. Cliente" << setw(44) << "4. Clientes por odem alfabetica" << endl
		<< setw(23) << "2. Todos os clientes" << setw(16) << "5. Transacoes" << endl
		<< setw(15) << "3. Bottom 10" << endl;
	setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  setcolor(7); cout << "< 0. Voltar >";  setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 5))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setcolor(4); cout << "> Digito invalido!" << endl;
		setcolor(15); cout << "Volte a indicar escolha: ";
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

void Store::OpcoesVisualizarInformacao()
{
	unsigned short int opcao;

	while (opcao = VisualizarInformacao())
		switch (opcao)
		{
		case 1:
			InfoInd();
			break;
		case 2:
			OpcoesListaClientes();
			break;
		case 3:
			Bottom10();
			break;
		case 4:
			ordenarCNome();
			break;
		case 5:
			OpcoesListaTransacoes();
			break;
		}
}

//MENU - Transacoes
int Store::ListaTransacoes()
{
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  setcolor(3); cout << "Supermercado  Vende++";  setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                     ";  setcolor(7); cout << "TRANSACOES";  setcolor(15); cout << "                    ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	setcolor(7); cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(15);  MostrarTransacoes();
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(7); cout << setw(18) << "1. Por cliente" << setw(32) << "3. Por dia" << endl
		<< setw(23) << "2. Entre duas datas" << endl;  setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  setcolor(7); cout << "< 0. Voltar >";  setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 3))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setcolor(4); cout << "> Digito invalido!" << endl;
		setcolor(15); cout << "Volte a indicar escolha: ";
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

void Store::OpcoesListaTransacoes()
{
	unsigned short int opcao;

	while (opcao = ListaTransacoes())
		switch (opcao)
		{
		case 1:
			TransInd();
			break;
		case 2:
			TransEntre();
			break;
		case 3:
			TransDia();
			break;
		}
}

//MENU - Produtos Disponiveis
int Store::ProdutosDisponiveis()
{
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  setcolor(3); cout << "Supermercado  Vende++";  setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~                ";  setcolor(7); cout << "PRODUTOS DISPONIVEIS";  setcolor(15); cout << "                ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	setcolor(7); cout << setw(10) << "Ref" << setw(22) << "Produto" << setw(20) << "Preco" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
	setcolor(15);  MostrarProdutos();
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(7); cout << setw(22) << "1. Efetuar Compra" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  setcolor(7); cout << "< 0. Voltar >";  setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 1))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setcolor(4); cout << "> Digito invalido!" << endl;
		setcolor(15); cout << "Volte a indicar escolha: ";
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

void Store::OpcoesProdutosDisponiveis()
{
	unsigned short int opcao;

	while (opcao = ProdutosDisponiveis())
		switch (opcao)
		{
		case 1:
			Compras();
			break;
		}
}

//MENU - Gerir Clientes
int Store::GerirClientes()
{
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  setcolor(3); cout << "Supermercado  Vende++";  setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                 ";  setcolor(7); cout << "GESTOR DE CLIENTES";  setcolor(15); cout << "                ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(15);  MostrarClientes();
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(7); cout << setw(20) << "1. Criar Cliente" << setw(32) << "3. Alterar Cliente" << endl
		<< setw(22) << "2. Remover Cliente" << endl;  setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  setcolor(7); cout << "< 0. Voltar >";  setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 3))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setcolor(4); cout << "> Digito invalido!" << endl;
		setcolor(15); cout << "Volte a indicar escolha: ";
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

void Store::OpcoesGerirClientes()
{
	unsigned short int opcao;

	while (opcao = GerirClientes())
		switch (opcao)
		{
		case 1:
			CriarCliente();
			break;
		case 2:
			RemoverCliente();
			break;
		case 3:
			AlterarCliente();
			break;
		}
}

//MENU - Lista de Clientes
int Store::ListaClientes()
{
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  setcolor(3); cout << "Supermercado  Vende++";  setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                 ";  setcolor(7); cout << "LISTA DE CLIENTES";  setcolor(15); cout << "                 ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(15);  MostrarClientes();
	setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(7);
	cout << setw(32) << "1. Ir para gestor de clientes" << endl;  setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  setcolor(7); cout << "< 0. Voltar >";  setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 1))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setcolor(4); cout << "> Digito invalido!" << endl;
		setcolor(15); cout << "Volte a indicar escolha: ";
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

void Store::OpcoesListaClientes()
{
	unsigned short int opcao;

	while (opcao = ListaClientes())
		switch (opcao)
		{
		case 1:
			OpcoesGerirClientes();
			break;
		}
}

//MENU - Saida
int Store::Saida()
{
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  setcolor(3); cout << "Supermercado  Vende++";  setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                          ";  setcolor(7); cout << "SAIR";  setcolor(15); cout << "                           |" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
	cout << endl << setw(48) << "Obrigado por utilizar este software!" << endl << endl;
	setcolor(7); cout << setw(30) << "Desenvolvido por:  ";  setcolor(15); cout << "Barbara Sofia Silva" << endl;
	cout << setw(43) << "Julieta Frade" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
	Sleep(5000);
	exit(0);
}

//MENU - Menu Inicial
int Store::MenuIniciar() {
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               ";  setcolor(3); cout << "Supermercado  Vende++";  setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                        ";  setcolor(7); cout << "MENU";  setcolor(15); cout << "                       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(23) << "1. Lista de Clientes" << setw(17) << "4. Transacoes" << endl
		<< setw(24) << "2. Gestor de Clientes" << setw(27) << "5. Visualizar Informacao" << endl
		<< setw(20) << "3. Efetuar Compra" << setw(35) << "6. Publicidade Personalizada" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
	cout << "|~~~                                 ";  setcolor(7); cout << "< 0. Sair >";  setcolor(15); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 6))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setcolor(4); cout << "> Digito invalido!" << endl;
		setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao <= 6))
	{
		if (opcao == 0)
			Saida();
		return opcao;
	}
	return 0;
}

void Store::OpcoesMenuIniciar()
{
	unsigned short int opcao;

	while (opcao = MenuIniciar())
		switch (opcao) {
		case 1:
			OpcoesListaClientes();
			break;
		case 2:
			OpcoesGerirClientes();
			break;
		case 3:
			OpcoesProdutosDisponiveis();
			break;
		case 4:
			OpcoesListaTransacoes();
			break;
		case 5:
			OpcoesVisualizarInformacao();
			break;
		case 6:
			system("cls");
			setcolor(14); cout << "< FUNCIONALIDADE EM CONSTRUCAO >" << endl << endl;  setcolor(15);
			system("pause");
			OpcoesMenuIniciar();
			break;
		}

}

//Clientes

//Extrai informacao do ficheiro dos clientes para um vetor (VClient)
void Store::ExtrairClientes() {
	ifstream Clientfile(FClient);
	string line;
	int i = 0;

	if (Clientfile.is_open())
	{
		if (!VClients.empty()) VClients.clear();

		while (getline(Clientfile, line))
		{

			if (line.find(";") != -1) {

				size_t pos1 = line.find(" ;");
				string str1 = line.substr(pos1 + 3);
				size_t pos2 = str1.find(" ;");
				string str2 = str1.substr(pos2 + 3);
				size_t pos3 = str2.find(" ;");

				string ids = line.substr(0, pos1);
				string nome = str1.substr(0, pos2);
				string data = str2.substr(0, pos3);
				string comprass = str2.substr(pos3 + 3);

				size_t posd1 = data.find("/");
				string strd1 = data.substr(posd1 + 1);
				size_t posd2 = strd1.find("/");

				string dia = data.substr(0, posd1);
				string mes = strd1.substr(0, posd2);
				string ano = strd1.substr(posd2+1);

				if (dia.size() == 1)
					dia = "0" + dia;
				if (mes.size() == 1)
					mes = "0" + mes;

				string datafinal = dia + "/" + mes + "/" + ano;

				int idi = stoi(ids);
				float comprasf = stof(comprass);

				VClients.push_back(Client(idi, formatarNome(nome), datafinal, comprasf));

				i++;
			}
		}
		Clientfile.close();
	}
	else { setcolor(4); cout << "Impossivel abrir ficheiro" << endl; setcolor(15); }
}

//Escreve vetor VClient no ficheiro dos clientes
int Store::EscreverCliente()
{
	ofstream Clientfile(FClient);
	if (Clientfile.is_open())
	{
		Clientfile << VClients.size() << endl;
		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			Clientfile << VClients.at(i).GetId() << " ; " << VClients.at(i).GetNome() << " ; " << VClients.at(i).GetData() << " ; " << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
		}
		Clientfile.close();
	}
	else { setcolor(4); cout << "Impossivel abrir ficheiro" << endl; setcolor(15); }
	return 0;
}

//Verifica se o cliente existe
bool Store::ClienteExiste(string output)
{
	int id;
	int a = 0;
	if ((int)output.at(0) >= 48 && (int)output.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
	{
		id = stoi(output, nullptr, 10); // se a opcao for o ID
		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if (id == VClients.at(i).GetId())
				a = a + 1;
		}
	}
	else {
		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if (output == VClients.at(i).GetNome())
				a = a + 1;
		}
	}
	if (a > 0)
		return true;
	else return false;
}

//Cria cliente
int Store::CriarCliente()
{
	string nome;
	float montante = 0;

	ExtrairClientes();

	cout << endl << "Introduza o nome do cliente: "; cin.ignore(); getline(cin >> setw(26), nome); cout << endl;
	VClients.push_back(Client(VClients.back().GetId() + 1, formatarNome(nome), DataAtual(), montante));

	EscreverCliente();

	return 0;
}

//Remove cliente
int Store::RemoverCliente()
{
	int id, dig;
	string opcao;

	cout << endl << "Intruduza o ID ou o NOME do cliente que pretende eliminar: ";  cin.ignore(); getline(cin, opcao); cout << endl;

	if (ClienteExiste(opcao))
	{
		if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
			id = stoi(opcao, nullptr, 10); // se a opcao for o ID
		else id = 0;

		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
			{
				cout << "Tem acerteza que quer eliminar o cliente:" << endl;
				setcolor(3); cout << "-----------------------------------------------------------" << endl; setcolor(15);
				cout << VClients.at(i).GetId();
				cout << setw(20) << VClients.at(i).GetNome();
				cout << setw(14) << VClients.at(i).GetData();
				cout << setw(15) << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
				setcolor(3); cout << "-----------------------------------------------------------" << endl; setcolor(7);
				cout << "1. SIM" << "        " << "2. NAO" << endl << endl; setcolor(15);
				cout << "Digite a sua opcao: ";  cin >> dig; cout << endl;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					setcolor(4); cout << "> Digito invalido!" << endl;
					setcolor(15); cout << "Volte a indicar escolha: ";
					cin >> dig;
				}

				if (dig == 1)
				{
					ExtrairClientes();
					VClients.erase(VClients.begin() + i);
					EscreverCliente();
					return 0;
				}
				else
					if (dig == 2)
						return 0;
			}
		}
	}
	else {
		setcolor(4); cout << "ERRO! Cliente nao encontrado." << endl; setcolor(15);
		system("pause");
		return 0;
	}

	return 0;
}

//Altera cliente
int Store::AlterarCliente()
{
	int id, dig;
	float montante;
	string opcao, nome;

	cout << endl << "Intruduza o ID ou o NOME do cliente que pretende alterar: ";  cin.ignore(); getline(cin, opcao); cout << endl;

	if (ClienteExiste(opcao))
	{
		if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
			id = stoi(opcao, nullptr, 10); // se a opcao for o ID
		else id = 0;

		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
			{
				cout << "Tem acerteza que quer alterar o cliente:" << endl;
				setcolor(3); cout << "-----------------------------------------------------------" << endl; setcolor(15);
				cout << VClients.at(i).GetId();
				cout << setw(20) << VClients.at(i).GetNome();
				cout << setw(18) << VClients.at(i).GetData();
				cout << setw(16) << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
				setcolor(3); cout << "-----------------------------------------------------------" << endl; setcolor(7);
				cout << "1. SIM" << "        " << "2. NAO" << endl << endl; setcolor(15);
				cout << "Digite a sua opcao: ";  cin >> dig; cout << endl;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					setcolor(4); cout << "> Digito invalido!" << endl;
					setcolor(15); cout << "Volte a indicar escolha: ";
					cin >> dig;
				}

				if (dig == 1)
				{
					cout << endl << "Intruduza o nome do cliente: "; cin.ignore(); getline(cin >> setw(26), nome); cout << endl;
					cout << "Introduza o montante gasto: "; cin >> montante; cout << endl;

					ExtrairClientes();
					VClients.at(i).SetNome(formatarNome(nome));
					VClients.at(i).SetMontante(montante);
					EscreverCliente();
					return 0;
				}
				else
					if (dig == 2)
						return 0;
			}
		}
	}
	else {
		setcolor(4); cout << "ERRO! Cliente nao encontrado." << endl; setcolor(15);
		system("pause");
		return 0;
	}
	return 0;
}

//Mostra a informacao de um respetivo cliente
int Store::InfoInd()
{
	int id;
	string opcao;

	cout << endl << "Intruduza o ID ou o NOME do cliente que pretende visualizar: ";  cin.ignore(); getline(cin, opcao); cout << endl;

	if (ClienteExiste(opcao))
	{
		if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
			id = stoi(opcao, nullptr, 10); // se a opcao for o ID
		else id = 0;

		for (unsigned int i = 0; i < VClients.size(); i++)
		{
			if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
			{
				system("cls");
				setcolor(14); cout << "> "; setcolor(15); cout << "Informacao do cliente: " << VClients.at(i).GetNome() << endl << endl;
				setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
				setcolor(3); cout << "-----------------------------------------------------------" << endl; setcolor(15);
				cout << setw(5) << VClients.at(i).GetId();
				cout << setw(20) << VClients.at(i).GetNome();
				cout << setw(18) << VClients.at(i).GetData();
				cout << setw(12) << setprecision(2) << fixed << VClients.at(i).GetMontante() << endl;
				setcolor(3); cout << "-----------------------------------------------------------" << endl; setcolor(15);
				system("pause");
				return 0;
			}
		}
	}
	else {
		setcolor(4); cout << "> ERRO! Cliente nao encontrado." << endl; setcolor(15);
		system("pause");
		return 0;
	}
	return 0;
}

//Muda a primeira letra de cada palavra de uma string para maiuscula e as restantes para minusculas - formata os nomes
string Store::formatarNome(string nome)
{
	string NomeAlterado = nome;

	//altera primeiro tudo para minusculas
	for (unsigned int i = 1; i < NomeAlterado.length(); i++)
	{
		NomeAlterado.at(i) = tolower(NomeAlterado.at(i));
	}

	//altera a primeira letra da string para maiusculas
	if (!isupper(NomeAlterado.at(0)))
	{
		NomeAlterado.at(0) = toupper(NomeAlterado.at(0));
	}

	//altera a letra depois de um espaço para maiusculas
	for (unsigned int i = 1; i < NomeAlterado.length(); i++)
	{
		if (NomeAlterado.at(i - 1) == ' ' && !isupper(NomeAlterado.at(i)))
		{
			NomeAlterado.at(i) = toupper(NomeAlterado.at(i));
		}
	}

	return NomeAlterado;
}



//Mostra clientes por ordem alfabética
int Store::ordenarCNome()
{
	vector <Client> VO = VClients;

	sort(VO.begin(), VO.end(), [](Client &a, Client &b) {return a.GetNome() < b.GetNome(); });

	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               "; setcolor(3); cout << "Supermercado  Vende++"; setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                 "; setcolor(7); cout << "LISTA DE CLIENTES"; setcolor(15); cout << "                 ~~~|" << endl
		<< "|~~~               por ordem  alfabetica               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(15);
	for (unsigned int i = 0; i < VO.size(); i++)
	{
		if (i < 10) {
			cout << setw(5) << VO.at(i).GetId();
			cout << setw(20) << VO.at(i).GetNome();
			cout << setw(18) << VO.at(i).GetData();
			cout << setw(12) << setprecision(2) << fixed << VO.at(i).GetMontante() << endl;
		}
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
	return 0;
}

// BOTTOM 10 //

//Mostra os piores 10 clientes
int Store::Bottom10()
{
	vector<Client> VO = VClients;

	sort(VO.begin(), VO.end(), [](Client &a, Client &b) {return a.GetMontante() < b.GetMontante(); });

	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               "; setcolor(3); cout << "Supermercado  Vende++"; setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                    "; setcolor(7); cout << "BOTTOM10"; setcolor(15); cout << "                     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	setcolor(7); cout << setw(5) << "ID" << setw(20) << "Nome do Cliente" << setw(18) << "Data Adesao" << setw(12) << "Total" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	setcolor(15);


	for (unsigned int i = 0; i < VO.size(); i++)
	{
		if (i < 10) {
			cout << setw(5) << VO.at(i).GetId();
			cout << setw(20) << VO.at(i).GetNome();
			cout << setw(18) << VO.at(i).GetData();
			cout << setw(12) << setprecision(2) << fixed << VO.at(i).GetMontante() << endl;
		}
	}
	setcolor(3); cout << "-----------------------------------------------------------" << endl; setcolor(7);
	if (VO.size() < 10)
	{
		cout << endl << "     ATENCAO: Existem menos de 10 clientes registados." << endl;
	}
	setcolor(15);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	system("Pause");
	return 0;
}

// funcao que mostra o ficheiro dos clientes
int Store::MostrarClientes() {
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
void Store::ExtrairProdutos()
{
	ifstream Prodfile(FProd);
	string line;
	int i = 0;
	if (Prodfile.is_open())
	{
		if (!VProducts.empty()) VProducts.clear();

		while (getline(Prodfile, line))
		{
			if (line.find(";") != -1) {
				VProducts.push_back(Product(line.substr(0, line.find_first_of(";") - 1), stof(line.substr(line.find_last_of(";") + 2, line.length() - line.find_last_of(";") - 2))));
				i++;
			}
		}
		Prodfile.close();
	}
	else { setcolor(4); cout << "Impossivel abrir ficheiro" << endl;  setcolor(15); }
}

//Escreve vetor VProd no ficheiro dos produtos
int Store::EscreverProduto()
{
	ofstream Prodfile(FProd);
	if (Prodfile.is_open())
	{
		Prodfile << VProducts.size() << endl;
		for (unsigned int i = 0; i < VProducts.size(); i++)
		{
			Prodfile << VProducts.at(i).GetProd() << " ; " << setprecision(1) << fixed << VProducts.at(i).GetPrice() << endl;
		}
		Prodfile.close();
	}
	else { setcolor(4); cout << "Impossivel abrir ficheiro" << endl;  setcolor(15); }
	return 0;
}

//Mostra o ficheiro dos produtos
int Store::MostrarProdutos()
{
	for (unsigned int i = 0; i < VProducts.size(); i++)
	{
		cout << setw(10) << i + 1 << setw(22) << VProducts.at(i).GetProd() << setw(20) << setprecision(1) << fixed << VProducts.at(i).GetPrice() << endl;
	}
	return 0;
}

//Efetua compras, adiciona transacao, adiciona montante gasta ao total do cliente, e caso seja necessario, cria cliente
int Store::Compras()
{
	unsigned int ref, dig, op;
	string produtos;
	float total = 0;
	string opcao;
	unsigned int id;

	setcolor(14); cout << "> ";  setcolor(15); cout << "Tendo em conta os produtos disponiveis, qual deseja comprar?" << endl;
	setcolor(14); cout << "> ";  setcolor(15); cout << "Quando terminar, por favor digite ";  setcolor(11); cout << " 0";  setcolor(15); cout << ".\n\n";
	
	//selecao de produtos a comprar
	while (true)
	{
		cin >> ref;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			setcolor(4); cout << "> Referencia Invalida!" << endl;
			setcolor(15); cin >> ref;
		}

		if (ref == 0)
			break;
		else {
			if (ref <= VProducts.size())
			{
				produtos.append(VProducts.at(ref - 1).GetProd());
				produtos.append(", ");
				setcolor(7); cout << "> Produto Adicionado!\n\n";  setcolor(15);
				total += VProducts.at(ref - 1).GetPrice();
			}
			else { setcolor(4); cout << "> Este produto nao existe!\n\n";  setcolor(15); }
		}
	}

	//caso nao tenha inserido nenhum produto valido, ou apenas tenha desistido de comprar
	if (produtos.empty())
	{
		setcolor(4); cout << "> Nao introduziu nenhum produto valido." << endl;  setcolor(15);
		system("pause");
		return 0;
	}

	//caso tenha inserido produtos validos
	else
	{
		//confirmacao da compra
		setcolor(14); cout << endl << "> ";  setcolor(15); cout << "Quer comprar o(s) produto(s): ";  setcolor(3); cout << "{ ";  setcolor(15); cout << produtos.substr(0, produtos.size() - 2) << "." << endl;
		setcolor(3); cout << "-----------------------------------------------------------" << endl;
		setcolor(7); cout << "1. SIM" << "        " << "2. NAO" << endl << endl;  setcolor(15);
		cout << "Digite a sua opcao: ";  cin >> dig; cout << endl;

		while ((dig != 1) && (dig != 2))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			setcolor(4); cout << "> Digito invalido!" << endl;
			setcolor(15); cout << "Volte a indicar escolha: ";
			cin >> dig;
		}
		if (dig == 1)
		{
			//selecao do cliente a efetuar a compra
			setcolor(14); cout << endl << "> ";  setcolor(15); cout << "Ja e cliente?" << endl;
			setcolor(3); cout << "-----------------------------------------------------------" << endl;
			setcolor(7); cout << "1. SIM" << "        " << "2. NAO" << endl << endl;  setcolor(15);
			cout << "Digite a sua opcao: ";  cin >> op; cout << endl;

			while ((op != 1) && (op != 2))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				setcolor(4); cout << "> Digito invalido!" << endl;
				setcolor(15); cout << "Volte a indicar escolha: ";
				cin >> op;
			}

			if (op == 1)
			{
				cout << endl << "Intruduza o ID ou Nome do cliente: ";  setcolor(3); cout << "{ ";  setcolor(15); cin.ignore(); getline(cin, opcao);

				while ((ClienteExiste(opcao)) == false)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					setcolor(4); cout << "> Este id/nome nao existe!" << endl;
					setcolor(15); cout << "Volte a indicar: ";
					cin >> opcao;
				}

				if (ClienteExiste(opcao))
				{
					if ((int)opcao.at(0) >= 48 && (int)opcao.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
						id = stoi(opcao, nullptr, 10); // se a opcao for o ID
					else id = 0;
				}
			}
			else if (op == 2)
			{
				CriarCliente();
				id = VClients.back().GetId();
			}

			//Display da montante total a pagar
			cout << endl << "Total a pagar: ";  setcolor(3); cout << "{ ";  setcolor(15); cout << total << " euros" << endl;

			//Ajuste da montante no cliente
			for (unsigned int i = 0; i < VClients.size(); i++)
			{
				if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
				{
					ExtrairClientes();
					VClients.at(i).SetMontante(total);
					id = VClients.at(i).GetId();
					EscreverCliente();
				}
			}
			AdicionarTrans(id, produtos);
			setcolor(4); cout << "\n> Compra Efetuada!\n";  setcolor(15);
			Sleep(3000);
			return 0;
		}
		else {
			if (dig == 2)
			{
				setcolor(4); cout << "> Compra Apagada!\n";  setcolor(15);
				system("pause");
				return 0;
			}
			else
			{
				setcolor(4); cout << "ERRO!" << endl;  setcolor(15);
				system("pause");
				return 0;
			}
		}
	}
	return 0;
}

//Transacoes

//Extrai informacao do ficheiro das transacoes para um vetor (VTrans)
void Store::ExtrairTransacoes()
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
				string strd1 = data.substr(posd1 + 1);
				size_t posd2 = strd1.find("/");

				string dia = data.substr(0, posd1);
				string mes = strd1.substr(0, posd2);
				string ano = strd1.substr(posd2 + 1);

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
	else { setcolor(4); cout << "Impossivel abrir ficheiro" << endl;  setcolor(15); }
}

//Escreve o vetor VTrans no ficheiro de transacoes
int Store::EscreverTrans()
{
	ofstream TransFile(FTrans);
	string produtos;

	if (TransFile.is_open())
	{
		TransFile << VTrans.size() << endl;
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
	else { setcolor(4); cout << "Impossivel abrir ficheiro" << endl;  setcolor(15); }
	return 0;
}

//Mostra as transacoes efetuadas num intervalo de datas
int Store::TransEntre()
{
	int dia1, mes1, ano1, dia2, mes2, ano2;
	string d1, m1, a1, d2, m2, a2;
	string data1, data2, datadig1, datadig2, produtos;
	int dataint1, dataint2, DataInteira;
	string DataDigitos, DataCompleta;
	int c=0; //contador

	cout << endl;
	setcolor(14); cout << "> ";  setcolor(15); cout << "Tera que escolher duas datas para visualizar as transacoes efetuadas nesse intervalo." << endl;
	setcolor(14); cout << "> ";  setcolor(15); cout << "Introduza a primeira data:" << endl << endl;
	cout << "> Dia: "; cin >> dia1; cout << "> Mes: "; cin >> mes1; cout << "> Ano: "; cin >> ano1;

	//Verifica se a primeira data é valida
	if (DataValida(dia1, mes1, ano1))
	{
		setcolor(7); cout << "Data Valida!\n";  setcolor(15);
	}
	else
	{
		setcolor(4); cout << "Data Invalida\n";  setcolor(15);
		system("pause");
		OpcoesListaTransacoes();
	}
	cout << endl;

	setcolor(14); cout << "> ";  setcolor(15); cout << "Introduza a segunda data: " << endl;
	cout << "> Dia: "; cin >> dia2; cout << "> Mes: "; cin >> mes2; cout << "> Ano: "; cin >> ano2;

	//Verifica se a segunda data é valida
	if (DataValida(dia2, mes2, ano2))
	{
		setcolor(7); cout << "Data Valida!\n";  setcolor(15);
		system("pause");
	}
	else
	{
		setcolor(4); cout << "Data Invalida\n";  setcolor(15);
		system("pause");
		OpcoesListaTransacoes();
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

	system("cls");
	setcolor(14); cout << "> ";  setcolor(15); cout << "Transacoes entre: " << data1 << " e " << data2 << endl << endl;
	setcolor(7);  cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);

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
	setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
	if (c == 0)
	{
		setcolor(7); cout << endl << "ATENCAO: "; setcolor(15); cout << "Nao existe nenhuma transacao efetuada \n         entre estas datas.\n" << endl;
	}
	system("pause");
	return 0;
}

//Mostra as transacoes efetuadas num determinado dia
int Store::TransDia()
{
	int dia1, mes1, ano1;
	string d1, m1, a1;
	string data1, datadig1, produtos;
	int dataint1, DataInteira;
	string DataDigitos, DataCompleta;

	cout << endl;
	setcolor(14); cout << "> ";  setcolor(15); cout << "Introduza a data que pretende visualizar." << endl;
	cout << "> Dia: "; cin >> dia1; cout << "> Mes: "; cin >> mes1; cout << "> Ano: "; cin >> ano1;

	if (DataValida(dia1, mes1, ano1))
	{
		setcolor(7); cout << "Data Valida!\n";  setcolor(15);
	}
	else
	{
		setcolor(4); cout << "Data Invalida\n";  setcolor(15);
		system("pause");
		OpcoesListaTransacoes();
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

	bool DataExiste = TransData(dataint1);

	if (DataExiste)
	{
		cout << endl;
		setcolor(7); cout << "Foi efetuada alguma transacao neste dia." << endl;  setcolor(15);
		system("pause");
		system("cls");
		setcolor(14); cout << "> ";  setcolor(15); cout << "Transacoes do dia: " << data1 << endl << endl;
		setcolor(7); cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
		setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);

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
		setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
		system("pause");
		return 0;
	}
	else
	{
		cout << endl;
		setcolor(4); cout << "> Nao foi efetuada nenhuma transacao neste dia." << endl;  setcolor(15);
		system("pause");
		return 0;
	}
	return 0;
}

//Verifica se a transacao com determinado ID existe
bool Store::TransExiste(unsigned int id)
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
int Store::TransInd()
{
	int id;
	string opcao, produtos;

	cout << endl << "Intruduza o ID do cliente que pretende visualizar: ";  cin >> id; cout << endl;

	if (TransExiste(id))
	{
		if (ClienteExiste(to_string(id)))
		{
			for (unsigned int i = 0; i < VClients.size(); i++)
			{
				if ((id == VClients.at(i).GetId()) || (opcao == VClients.at(i).GetNome()))
				{
					system("cls");
					setcolor(14); cout << "> ";  setcolor(15); cout << "Transacoes do cliente: " << VClients.at(i).GetNome() << endl << endl;
					setcolor(7);  cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
					setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
				}
			}
		}
		else
		{
			system("cls");
			setcolor(14); cout << "> ";  setcolor(15); cout << "Transacoes de um cliente eliminado." << endl << endl;
			setcolor(7);  cout << setw(5) << "ID" << setw(14) << "Data" << setw(28) << "Produtos" << endl;
			setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
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
		setcolor(3); cout << "-----------------------------------------------------------" << endl;  setcolor(15);
		system("pause");
		return 0;
	}
	else {
		setcolor(4); cout << "> Nao existe nenhuma transacao com este ID." << endl;  setcolor(15);
		system("pause");
		return 0;
	}
	return 0;
}

//Verifica se existe alguma transacao efetuada com esta data
bool Store::TransData(int dataint1)
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
int Store::MostrarTransacoes()
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
void Store::AdicionarTrans(int id, string produtos)
{
	vector<string> products;
	while (!(produtos.empty()))
	{
		products.push_back(produtos.substr(0, produtos.find_first_of(",")));
		produtos.erase(0, produtos.find_first_of(",") + 2);
	}

	ExtrairTransacoes();
	VTrans.push_back(Transaction(id, DataAtual(), products));
	EscreverTrans();

	return;
}