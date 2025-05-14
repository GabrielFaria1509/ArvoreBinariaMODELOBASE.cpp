#include <iostream>
#include <string>

using namespace std;

struct dados {
    string nome, tipo;
};

struct treenode {
    dados rocha;
    treenode *esquerda;
    treenode *direita;
};

typedef treenode *treenodeptr;

void tree_insert(treenodeptr &tree, dados rocha){
    if(tree == NULL){
        tree = new treenode;
        tree->rocha = rocha;
        tree->esquerda = NULL;
        tree->direita = NULL;
    } else if (rocha.nome < tree->rocha.nome){
        tree_insert(tree->esquerda, rocha);
    } else {
        tree_insert(tree->direita, rocha);
    }
}

treenodeptr search_tree(treenodeptr tree, string nome_busca){
    if(tree == NULL){
        return NULL;
    }
    if(nome_busca == tree->rocha.nome){
        return tree;
    }
    if(nome_busca < tree->rocha.nome){
        return search_tree(tree->esquerda, nome_busca);
    } else {
        return search_tree(tree->direita, nome_busca);
    }
}

// Encontra o menor da subárvore à direita
treenodeptr repoint_less(treenodeptr &tree) {
    if (tree->esquerda != NULL) {
        return repoint_less(tree->esquerda);
    } else {
        treenodeptr temp = tree;
        tree = tree->direita;
        return temp;
    }
}

bool remove(treenodeptr &tree, dados rocha){
    if(tree == NULL){
        return false;
    } else {
        if(tree->rocha.nome == rocha.nome && tree->rocha.tipo == rocha.tipo){
            if(tree->esquerda == NULL){
                treenode *aux = tree;
                tree = tree->direita;
                delete aux;
            } else if(tree->direita == NULL){
                treenode *aux = tree;
                tree = tree->esquerda;
                delete aux;
            } else {
                treenode *aux = repoint_less(tree->direita);
                tree->rocha = aux->rocha;
                delete aux;
            }
            return true;
        } else {
            if(rocha.nome < tree->rocha.nome){
                return remove(tree->esquerda, rocha);
            } else {
                return remove(tree->direita, rocha);
            }
        }
    }
}

void destroy_tree(treenodeptr &tree){
    if (tree != NULL){
        destroy_tree(tree->esquerda);
        destroy_tree(tree->direita);
        delete tree;
    }
    tree = NULL;
}

int main(){
    int opcao_menu;
    bool sair_do_programa = false;
    string nome_busca;
    treenodeptr tree = NULL, tree_busca = NULL;
    dados rocha_auxiliar;        //ou dados rochaauxiliar ou rochaAuxiliar ou dados rochaux

    do {
        cin >> opcao_menu;
        switch (opcao_menu) {
        case 0:
            sair_do_programa = true;
            break;

        case 1:
            getline(cin >> ws, rocha_auxiliar.nome);     
            getline(cin >> ws, rocha_auxiliar.tipo);
            tree_insert(tree, rocha_auxiliar);        //devo passar como tree_insert(tree, rochaauxiliar); e em remove também
            break;

        case 2:
            getline(cin >> ws, nome_busca);
            tree_busca = search_tree(tree, nome_busca);
            if(tree_busca != NULL){
                cout << "Nome: " << tree_busca->rocha.nome << endl;
                cout << "Tipo: " << tree_busca->rocha.tipo  << endl;
            } else {
                cout << "Rocha nao encontrada" << endl;
            }
            break;

        case 3:
            getline(cin >> ws, rocha_auxiliar.nome);
            getline(cin >> ws, rocha_auxiliar.tipo);
            if(remove(tree, rocha_auxiliar)){           // Tenta remover a rocha especificada (pelo nome e tipo) da árvore
                cout << "Rocha removida com sucesso" << endl; // Se a função 'remove' retornar true, significa que a rocha foi encontrada e removida com sucesso
            } else {
                cout << "Rocha nao encontrada para remocao" << endl;
            }
            break;

        default:
            cout << "Operacao invalida" << endl;
            break;
        }
    } while (!sair_do_programa);

    destroy_tree(tree);

    return 0;
}
//int main alternativa 
/*
int main() {
    int opcao_menu;
    bool sair_do_programa = false;
    string nome_busca;
    treenodeptr tree = NULL, tree_busca = NULL;

    do {
        cin >> opcao_menu;
        switch (opcao_menu) {
        case 0:
            sair_do_programa = true;
            break;

        case 1:
            dados rocha;  // Declaração diretamente na main
            getline(cin >> ws, rocha.nome);  // Preenche rocha.nome
            getline(cin >> ws, rocha.tipo);  // Preenche rocha.tipo
            tree_insert(tree, rocha);  // Insere diretamente
            break;

        case 2:
            getline(cin >> ws, nome_busca);
            tree_busca = search_tree(tree, nome_busca);
            if(tree_busca != NULL){
                cout << "Nome: " << tree_busca->rocha.nome << endl;
                cout << "Tipo: " << tree_busca->rocha.tipo  << endl;
            } else {
                cout << "Rocha nao encontrada" << endl;
            }
            break;

        case 3:
            dados rocha_remover;  // Declaração diretamente na main
            getline(cin >> ws, rocha_remover.nome);
            getline(cin >> ws, rocha_remover.tipo);
            if(remove(tree, rocha_remover)){
                cout << "Rocha removida com sucesso" << endl;
            } else {
                cout << "Rocha nao encontrada para remocao" << endl;
            }
            break;

        default:
            cout << "Operacao invalida" << endl;
            break;
        }
    } while (!sair_do_programa);

    destroy_tree(tree);
    return 0;
}
*/

