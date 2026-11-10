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

void printRange(Node* r, int L, int R) {
    if (!r) return;
    if (r->data > L) printRange(r->left, L, R);
    if (r->data >= L && r->data <= R) cout << r->data << " ";
    if (r->data < R) printRange(r->right, L, R);
}

int countRange(Node* r, int L, int R) {
    if (!r) return 0;
    if (r->data < L) return countRange(r->right, L, R);
    if (r->data > R) return countRange(r->left, L, R);
    return 1 + countRange(r->left, L, R) + countRange(r->right, L, R);
}
Node* deleteOutside(Node* r, int L, int R) {
    if (!r) return NULL;
    r->left = deleteOutside(r->left, L, R);
    r->right = deleteOutside(r->right, L, R);
    if (r->data < L) {
        Node* t = r->right;
        delete r;
        return t;
    }
    if (r->data > R) {
        Node* t = r->left;
        delete r;
        return t;
    }
    return r;
}

void inorder(Node* r) {
    if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); }
}

int main() {
    int a[] = {50, 25, 75, 10, 30, 60, 90, 20, 40, 70, 80};
    Node* root = NULL;
    for (int i = 0; i < 11; i++) root = insert(root, a[i]);

    int L = 25, R = 70;
    cout << "IDs in range: ";
    printRange(root, L, R);
    cout << endl;
    cout << "Count: " << countRange(root, L, R) << endl;

    root = deleteOutside(root, L, R);
    cout << "After deleting outside range: ";
    inorder(root);
    cout << endl;
    return 0;
}
