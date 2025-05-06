#include<iostream>
using namespace std;

struct node {
    int info;
    node* left;
    node* right;
};

void insert(node * &curr, int info){
    if(curr == NULL){
        curr = new node;
        curr->info = info;
        curr->left = NULL;
        curr->right = NULL;
    }else{
        if(info < curr->info){
            insert(curr->left, info); // Chama a função recursivamente para o filho esquerdo
        }else{
            insert(curr->right, info); // Chama a função recursivamente para o filho direito
        }
    }
}

node * search(node * curr, int info){
    if(curr == NULL){
        return NULL; // Se o nó atual for nulo, retorna nulo
    }
    else{
        if(curr->info == info){
            return curr; // Se o nó atual contém o valor procurado, retorna o nó
        }else{
            if(info < curr->info){
                return search(curr->left, info); // Chama a função recursivamente para o filho esquerdo
            }
            else{
                return search(curr->right, info); // Chama a função recursivamente para o filho direito
            }
        }
    }
}

int main(){
    node * root = NULL; // Inicializa a raiz da árvore como nula

    insert(root, 10); // Insere o valor 10 na árvore

    insert(root, 5); // Insere o valor 5 na árvore

    insert(root, 15); // Insere o valor 15 na árvore

    node * result = search(root,11); // Busca o valor 11 na árvore

    if(result == NULL){
        cout << "Valor não encontrado na árvore." << endl; // Se o valor não for encontrado, imprime mensagem
    }else{
        cout << result->info << endl;
    }

    result = search(root,6);
    
    if(result == NULL){
        cout << 6 << " não encontrado na árvore." << endl; // Se o valor não for encontrado, imprime mensagem
    }else{
        cout << result->info << endl;
    }

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}