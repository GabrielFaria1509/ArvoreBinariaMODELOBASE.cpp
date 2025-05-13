#include<iostream>
#include<string>
using namespace std;

struct node {
	int info;
	node * left;
	node * right;
};

// Função para inserir um novo valor na árvore
void insert(node * &curr, int info){
	if(curr == NULL){
		// Cria um novo nó se a posição estiver vazia
		curr = new node;
		curr->info = info;
		curr->left = NULL;
		curr->right = NULL;
	} else {
		// Insere recursivamente à esquerda ou direita
		if(info < curr->info){
			insert(curr->left, info);
		} else {
			insert(curr->right, info);
		}
	}
}

// Função auxiliar para encontrar o menor valor da subárvore direita
// e ajustá-la ao remover um nó com dois filhos
node * repoint_less(node *&curr){
	if(curr->left == NULL){
		// Encontrou o menor (mais à esquerda)
		node * aux = curr;
		curr = curr->right; // Reposiciona o ponteiro para manter a árvore válida
		return aux;
	} else {
		return repoint_less(curr->left);
	}
}

// Função para remover um valor da árvore
bool remove(node *&curr, int info){ // ALTERADO: passou curr por referência (node *&)
	if(curr == NULL){
		return false; // Valor não encontrado
	} else {
		if(curr->info == info){
			// Caso 1: nó sem filho à esquerda
			if(curr->left == NULL){
				node * aux = curr;
				curr = curr->right;
				delete aux;
			}
			// Caso 2: nó sem filho à direita
			else if(curr->right == NULL){
				node * aux = curr;
				curr = curr->left;
				delete aux;
			}
			// Caso 3: nó com dois filhos
			else{
				node* aux = repoint_less(curr->right); // Encontra sucessor
				curr->info = aux->info; // Copia valor
				delete aux; // Remove o nó original
			}
			return true;
		} else {
			// Busca recursiva pelo valor
			if(info < curr->info){
				return remove(curr->left, info);
			} else {
				return remove(curr->right, info);
			}
		}
	}
}

// Função para buscar um valor na árvore
node * search (node * curr, int info){
	if(curr == NULL){
		return NULL;
	} else {
		if(curr->info == info){
			return curr;
		} else {
			if(info < curr->info){
				return search(curr->left, info);
			} else {
				return search(curr->right, info);
			}
		}
	}
}

int main() {
	int n;
	cin >> n;

	node* root = NULL;

	for (int i = 0; i < n; i++) {
		string op;
		int x;
		cin >> op >> x;

		if (op == "i") {
			insert(root, x); // Inserção
		} else if (op == "b") {
			node* result = search(root, x); // Busca
			if(result == NULL) {
				cout << "Não" << endl;
			} else {
				cout << "Sim" << endl;
			}
		} else if(op == "r"){
			remove(root,x); // Remoção
		}
	}

	return 0;
}
