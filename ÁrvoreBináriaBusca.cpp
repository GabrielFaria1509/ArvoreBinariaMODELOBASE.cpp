/*

    NOTA DO AUTOR: CASO QUEIRA MUDAR A COR DO COUT, UTILIZE A VARIÁVEL COM O 
    NOME DA COR (roxoClaro;) E O CONSOLE VAI MUDAR DE COR!

    PARA CASO DE ERRO, ESCREVA erro(cor, tempo), SENDO QUE A COR É A COR QUE O TEXTO
    VAI FICAR DEPOIS DE PISCAR, E O TEMPO É A QUANTIDADE DE MILISSEGUNDOS ENTRE CADA PISCADA!

    QUALQUER DÚVIDA ME PERGUNTE *POR FAVOR*, E NÃO MEXE NOS DEFINES POR FAVOR (OBRIGADO)

        -??

*/


// includes
#include <bits/stdc++.h>
#include <windows.h>
// defines
#define _size 1000
#define inf 0x4f4f4f4f
#define cls system("CLS")
#define rep(i, a, b) for (int i = a; i < b; i++)
#define preto system("color 00")
#define azul system("color 01")
#define verde system("color 02")
#define agua system("color 03")
#define vermelho system("color 04")
#define roxo system("color 05")
#define amarelo system("color 06")
#define branco system("color 07")
#define pretoClaro system("color 08")
#define azulClaro system("color 09")
#define verdeClaro system("color 0A")
#define aguaClaro system("color 0B")
#define vermelhoClaro system("color 0C")
#define roxoClaro system("color 0D")
#define amareloClaro system("color 0E")
#define brancoClaro system("color 0F")
#define apagarlinha Sleep(10); cout << "\033[A\033[K"
#define erro(color, time) \
    system("color 40");   \
    Sleep(time);          \
    color;                \
    Sleep(time);          \
    system("color 40");   \
    Sleep(time);          \
    color;                \
    Sleep(time)

// código
using namespace std;

struct pokemon{   // estrutura para os pokemons
    string nome;
    string tipo;
    int numero;
};
struct node{    // Árvore binária de busca para os pokemons
    pokemon*info;  // ponteiro para o pokemon
    node*left;
    node*right;
};
int nEstradas, nCidades;
int pi[_size];
typedef long long custo;
typedef long long ll;
vector<pair<int, custo> > adj[_size];
vector<string> nomes[_size];
bool vis[_size];      // vertices visitados (dfs)
custo distancia[_size]; // distancia entre 2 vertices (bfs)
bool temCidade = false;
bool temRota = false;
string nome = getenv("USERNAME");
vector<bool> temPC;

void dijkstra(int origem) {
    priority_queue< pair<custo, int> > queue;
  
    memset(distancia, inf, sizeof(distancia));
    // don't use memset if cost_t is double
  
    distancia[origem] = 0;
    queue.push( {distancia[origem], origem});
  
    while (!queue.empty()) {
      pair<custo, int> top = queue.top();
      queue.pop();
  
      int u = top.second;
      ll d = -top.first;
      
      if (d != distancia[u]) continue;
  
      rep(i, 0, (int)adj[u].size()) {
        int v = adj[u][i].first;
        custo cost_uv = adj[u][i].second;
  
        if (distancia[u] + cost_uv < distancia[v]) {
          distancia[v] = distancia[u] + cost_uv;
          pi[v] = u;
          queue.push( {-distancia[v], v} );
        }
      }
    }
  }

void cadastrarCidade()
{ // funcoes para as funcionalidades
    string townName;
    int townNo;
    char resposta;
    do
    {
        cls;
        aguaClaro;
        cout << "Quantas cidades?" << endl;
        cin >> nCidades;
        if (nCidades <= 0)
        {
            cls;
            vermelhoClaro;
            cout << "Erro: é necessário um número válido de cidades!" << endl;
            erro(vermelhoClaro, 20);
            Sleep(900);
        }
    } while (nCidades <= 0);
    cls;
    aguaClaro;
    cout << "Nomeie as " << nCidades << " cidades:" << endl;
    for (int i = 0; i < nCidades; i++)
    {
        cout << "Nome da cidade " << i + 1 << ": ";
        cin.ignore();
        getline(cin, townName);
        nomes[i].push_back(townName);
        cout << "Ela tem Centro Pokémon? (S ou N): ";
        cin >> resposta;
        if(resposta == 'S' || resposta == 's'){
            temPC.push_back(true);
        }
        else if(resposta == 'N' || resposta == 'n'){
            temPC.push_back(false);
        }
        else{
            temPC.push_back(false);
        }
    }
    
    cout << endl
         << "Cidades configuradas! Retornando ao menu..." << endl;
    temCidade = true;
    Sleep(1500);
    cls;
}

void cadastrarEstrada()
{
    int townA, townB;
    int dist;
    if (!temCidade)
    {
        cls;
        vermelhoClaro;
        cout << "Ops! Parece que você não cadastrou uma cidade, " << nome << "." << endl
             << "Retornando ao menu..." << endl;
        erro(vermelhoClaro, 20);
        Sleep(1800);
        cls;
    }
    else
    {

        do
        {
            cls;
            aguaClaro;
            Sleep(10);
            nEstradas=1;
            cout << "Quantas rotas existem?" << endl;
            cin >> nEstradas;
            if (nEstradas <= 0)
            {
                cls;
                vermelhoClaro;
                cout << "Erro: é necessário um número válido de estradas!" << endl;
                erro(vermelhoClaro, 20);
                Sleep(900);
            }
        } while (nEstradas <= 0);
        cls;
        cout << "Digite todas as rotas existentes entre as cidades, de 1 até " << nEstradas << endl << "declarando o número da cidade A, da cidade B, e o tamanho dessa rota" << endl;
        cout << "Só são válidas distâncias positivas, e cidades de 1 a " << nCidades << ", sendo que A!=B" << endl;
            for(int i = 0; i < nEstradas; i++){   
                do{
                cout << "Rota " << i+1 << ": ";
                cin >> townA >> townB >> dist;
                if(townA<=0||townA>nCidades || townB<=0||townB>nCidades || townA==townB || dist<=0){
                    cls;
                
                }else{
                    adj[townA-1].push_back({townB-1, dist});
                    adj[townB-1].push_back({townA-1, dist});
                    distancia[i] = dist;
                }
            }while(townA<=0||townA>nCidades || townB<=0||townB>nCidades || townA==townB || dist<=0);            
        }
        cls;
        cout << "Certo! Tudo pronto! Voltando ao menu..." << endl;
        Sleep(900);
    }
}

void centroPokemonPerto()
{
    int src;
    cls;
    cout << "Qual a cidade de origem? ";
    cin >> src;
    dijkstra(src-1);
    for(int i = 0; i < 3; i++){
        cout << endl << "Procurando Centro Pókemon mais próximo para você." << endl;
        Sleep(200);
        cls;
        cout << endl << "Procurando Centro Pókemon mais próximo para você.." << endl;
        Sleep(200);
        cls;
        cout << endl << "Procurando Centro Pókemon mais próximo para você..." << endl;
        Sleep(200);
        cls;
    }
    cls;
    int menordist = inf;
    int menorpos = inf;
    for(int j = 0; j < _size; j++){
        if (temPC[j] && distancia[j] < menordist) {
            menordist = distancia[j];
            menorpos = j;
        }
    }
    cls;
    aguaClaro;
    if(menorpos != inf){
        cout << "O Centro Pókemon mais próximo de " << nomes[src - 1][0] 
             << " fica a " << menordist << " quilômetros, em " << nomes[menorpos][0] << "." << endl;
    }else{
        vermelhoClaro;
        cout << "Nenhum Centro Pókemon foi encontrado próximo à cidade de " << nomes[src - 1][0] << "." << endl;
    }
    system("pause");
    cls;
    


}

void cadastrarPokemon(pokemon* novoPokemon , int numero)
{
    string opcao;
    cout << "Deseja começar por nome,tipo ou numero ?" << endl;
    getline(cin >>ws, opcao);

    pokemon* novoPokemon = new pokemon; // cria um novo pokemon
    if(opcao =='nome'){
        
        node* raizPorNome = NULL; // raiz da árvore binária de busca por nome
        cout << "Digite o nome do Pokémon: ";
        
        
    }
    else if(opcao == 'tipo'){
        
        node* raizPorTipo = NULL; // raiz da árvore binária de busca por tipo
        cout << "Digite o tipo do Pokémon: ";
    }
    else if(opcao =='numero' ){
        
        
        cout << "Digite o número do Pokémon: ";
        if(node* raizPorNumero = NULL){
            node* raizPorNumero = new node; // raiz da árvore binária de busca por número
            novoPokemon ->numero =numero; // número do pokemon
            node* novoPokemon ->left = NULL;
            node* novoPokemon ->right = NULL;
            cin >> novoPokemon ->numero;
            
        }else{
            if(numero < raizPorNumero -> numero){
                cadastrarPokemon(raizPorNumero -> left, numero);
            }else{
                cadastrarPokemon(raizPorNumero -> right, numero);
            }
        } 

    }
    else{
        cout << "Opção inválida! Tente novamente." << endl;
        cadastrarPokemon();
    }
    
}

void listarPokemonNome()
{
    cout << "Funcionalidade em construcao" << endl;
}

void listarPokemonTipo()
{
    cout << "Funcionalidade em construcao" << endl;
}

void contarPokemonTipo()
{
    cout << "Funcionalidade em construcao" << endl;
}

void encontrarPokemon()
{
    cout << "Funcionalidade em construcao" << endl;
}

void menu()
{
    int opcao = -1;
    do
    {
        brancoClaro;
        // menu inicial
        if (opcao == 0)
        {
            cls;
            brancoClaro;
            cout << "Erro: entrada incorreta!" << endl;
        }
        cout << "Escolha sua opcao:" << endl;
        cout << "1 - Cadastrar cidade" << endl;
        cout << "2 - Cadastrar estrada" << endl;
        cout << "3 - Buscar centro Pokemon mais proximo" << endl;
        cout << "4 - Cadastrar Pokemon" << endl;
        cout << "5 - Listar Pokemon (ordem alfabetica - nome)" << endl;
        cout << "6 - Listar Pokemon (ordem alfabetica - tipo)" << endl;
        cout << "7 - Contar Pokemon por tipo" << endl;
        cout << "8 - Encontrar Pokemons proximos" << endl;
        cout << "9 - Sair" << endl;
        if (opcao == 0)
        {
            erro(brancoClaro, 20);
        }
        opcao = -1;
        string opt;
        cin >> opt;
        cls;
        if (opt.size() == 1)
        {
            if (isdigit(opt[0]))
            {
                opcao = opt[0] - '0';
            }
            else
            {
                opcao = 0;
            }
        }
        else
        {
            opcao = 0;
        }

        switch (opcao)
        { // opcoes menu
        case 1:
            cadastrarCidade();
            break;
        case 2:
            cadastrarEstrada();
            break;
        case 3:
            centroPokemonPerto();
            break;
        case 4:
            cadastrarPokemon();
            break;
        case 5:
            listarPokemonNome();
            break;
        case 6:
            listarPokemonTipo();
            break;
        case 7:
            contarPokemonTipo();
            break;
        case 8:
            encontrarPokemon();
            break;
        case 9:
            cls;
            cout << "Saindo da Pókedex..." << endl;
            Sleep(1000);
            cls;
            vermelhoClaro;
            exit(EXIT_SUCCESS);
            break;
        }

    } while (opcao != 9); // encerra menu
}

int main()
{
    if (!nome.empty())
    {
        nome[0] = toupper(nome[0]);
        for (size_t i = 1; i < nome.size(); ++i)
        {
            nome[i] = tolower(nome[i]);
        }
    }
    setlocale(LC_ALL, "Portuguese");
    system("title Pókedex");
    cls;
    amareloClaro;

    cout << "Olá, " << nome << "! Bem-vindo(a) à Pókedex!" << endl;
    system("pause");
    cls;
    menu();
}
