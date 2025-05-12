#include<iostream>
using namespace std;

struct node {
	int info;
	node * left;
	node * right;
};

void insert(node * &curr, int info){
	if(curr == NULL){
		curr = new node;
		curr->info = info;
		curr->left = NULL;
		curr->right = NULL;
	} else {
		if(info < curr->info){
			insert(curr->left, info);
		} else {
			insert(curr->right, info);
		}
	}
}
node * repoint_less(node *&curr){
    if(curr -> left == NULL){
        node * aux = curr;
        curr = curr -> right;
        return aux;
    }else{
        return repoint_less(curr -> left);
    }
}

bool remove(node*curr,int info){
    if(curr == NULL){
		return false;
	} else {
		if(curr->info == info){
            node * aux = curr;
			if(curr -> left == NULL){
                curr = curr ->right;
            }else if(curr ->right == NULL){
                curr = curr ->left;
            }else{
                node* aux= repoint_less(curr ->right)
                curr ->info = aux ->info;
                
            }
            delete aux;
            aux = NULL;
            return true;
		} else {
			if(info < curr->info){
				return remove(curr->left, info);
			} else {
				return remove(curr->right, info);
			}
		}
	}
}

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

int main(){
	
	node * root = NULL;
	
	insert(root, 10);
	
	insert(root, 12);
	
	insert(root, 6);
	
	insert(root, 33);
	
	node * result = search(root, 11);
	
	if(result == NULL) {
		cout << 11 << " nao encontrado" << endl;
	} else {
		cout << result->info << endl;
	}
	
	result = search(root, 6);
	
	if(result == NULL) {
		cout << 6 << " nao encontrado" << endl;
	} else {
		cout << result->info << endl;
	}
	
	return 0;
}






