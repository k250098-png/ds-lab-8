#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v) { data = v; left = right = NULL; }
};

Node* insert(Node* root, int v) {
    if (!root) return new Node(v);
    if (v < root->data) root->left = insert(root->left, v);
    else if (v > root->data) root->right = insert(root->right, v);
    return root;
}

Node* minNode(Node* r) {
    while (r->left) r = r->left;
    return r;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return NULL;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left && !root->right) {        
            delete root;
            return NULL;
        }
        if (!root->left) {                        
            Node* t = root->right;
            delete root;
            return t;
        }
        if (!root->right) {                      
            Node* t = root->left;
            delete root;
            return t;
        }
        Node* succ = minNode(root->right);       
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    return root;
}

void inorder(Node* r) {
    if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); }
}

int main() {
    int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    Node* root = NULL;
    for (int i = 0; i < 9; i++) root = insert(root, a[i]);

    int d[] = {20, 30, 50};
    for (int i = 0; i < 3; i++) {
        root = deleteNode(root, d[i]);
        cout << "After deleting " << d[i] << ": ";
        inorder(root);
        cout << endl;
    }
    return 0;
}
