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

void inorder(Node* r) {
    if (r) { inorder(r->left); cout << r->data << " "; inorder(r->right); }
}

int findMin(Node* r) { while (r->left) r = r->left; return r->data; }
int findMax(Node* r) { while (r->right) r = r->right; return r->data; }

void printGreater(Node* r, double t) {
    if (!r) return;
    printGreater(r->left, t);
    if (r->data > t) cout << r->data << " ";
    printGreater(r->right, t);
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


void longestPath(Node* r) {
    if (!r) return;
    cout << r->data;
    if (!r->left && !r->right) return;
    cout << " -> ";
    if (height(r->left) >= height(r->right)) longestPath(r->left);
    else longestPath(r->right);
}

bool isSkewed(Node* r) {
    if (!r) return true;
    if (r->left && r->right) return false;
    return isSkewed(r->left) && isSkewed(r->right);
}


Node* deleteOneChild(Node* r, int &count) {
    if (!r) return NULL;
    r->left = deleteOneChild(r->left, count);
    r->right = deleteOneChild(r->right, count);
    if (!r->left && r->right) {
        Node* t = r->right;
        delete r;
        count++;
        return t;
    }
    if (r->left && !r->right) {
        Node* t = r->left;
        delete r;
        count++;
        return t;
    }
    return r;
}


void kthSmallest(Node* r, int k, int &count, int &result) {
    if (!r || count >= k) return;
    kthSmallest(r->left, k, count, result);
    count++;
    if (count == k) { result = r->data; return; }
    kthSmallest(r->right, k, count, result);
}

int main() {
    int a[] = {45, 25, 65, 15, 35, 55, 75, 10, 30, 40, 60, 80, 32, 33};
    Node* root = NULL;
    for (int i = 0; i < 14; i++) root = insert(root, a[i]);

    int k;
    cout << "Enter k: ";
    cin >> k;

    cout << "Original inorder: ";
    inorder(root);
    cout << endl;

    int mn = findMin(root), mx = findMax(root);
    double threshold = (mn + mx) / 2.0;
    cout << "Min: " << mn << ", Max: " << mx << endl;
    cout << "Threshold: " << threshold << endl;
    cout << "Marks greater than threshold: ";
    printGreater(root, threshold);
    cout << endl;

    cout << "Nodes with two children: " << twoChildren(root) << endl;
    cout << "Longest root-to-leaf path: ";
    longestPath(root);
    cout << endl;
    cout << "Skewed: " << (isSkewed(root) ? "Yes" : "No") << endl;

    int deleted = 0;
    root = deleteOneChild(root, deleted);
    cout << "Nodes deleted: " << deleted << endl;
    cout << "Final inorder: ";
    inorder(root);
    cout << endl;

    int count = 0, result = -1;
    kthSmallest(root, k, count, result);
    if (result == -1) cout << "k is out of range" << endl;
    else cout << k << "th smallest remaining mark: " << result << endl;
    return 0;
}
