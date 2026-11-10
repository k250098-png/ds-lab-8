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

void preorder(Node* r)  { if (r) { cout << r->data << " "; preorder(r->left); preorder(r->right); } }
void inorder(Node* r)   { if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); } }
void postorder(Node* r) { if (r) { postorder(r->left); postorder(r->right); cout << r->data << " "; } }

int oneChild(Node* r) {
    if (!r) return 0;
    int c = ((r->left == NULL) != (r->right == NULL)) ? 1 : 0;
    return c + oneChild(r->left) + oneChild(r->right);
}

int twoChildren(Node* r) {
    if (!r) return 0;
    int c = (r->left && r->right) ? 1 : 0;
    return c + twoChildren(r->left) + twoChildren(r->right);
}

int height(Node* r) {
    if (!r) return -1;
    return 1 + max(height(r->left), height(r->right));
}

int main() {
    int a[] = {45, 25, 65, 15, 35, 55, 75, 30};
    Node* root = NULL;
    for (int i = 0; i < 8; i++) root = insert(root, a[i]);

    cout << "Preorder: ";  preorder(root);  cout << endl;
    cout << "Inorder: ";   inorder(root);   cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
    cout << "Nodes with one child: " << oneChild(root) << endl;
    cout << "Nodes with two children: " << twoChildren(root) << endl;
    cout << "Height (edges): " << height(root) << endl;
    return 0;
}
