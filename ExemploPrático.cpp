#include <iostream>
#include <string>
using namespace std;

struct node {
    int info;
    node* left;
    node* right;
};

void insert(node*& curr, int info) {
    if (curr == NULL) {
        curr = new node;
        curr->info = info;
        curr->left = NULL;
        curr->right = NULL;
    } else {
        if (info < curr->info) {
            insert(curr->left, info);
        } else {
            insert(curr->right, info);
        }
    }
}

node* search(node* curr, int info) {
    if (curr == NULL) {
        return NULL;
    } else if (curr->info == info) {
        return curr;
    } else if (info < curr->info) {
        return search(curr->left, info);
    } else {
        return search(curr->right, info);
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
            insert(root, x);
        } else if (op == "b") {
            node* result = search(root, x);
            if (result == NULL) {
                cout << "Não" << endl;
            } else {
                cout << "Sim" << endl;
            }
        }
    }

    return 0;
}
