#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

void BFS(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

void DFS(Node* root) {
    if (root == NULL) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* node = s.top();
        s.pop();
        cout << node->data << " ";
        if (node->left) s.push(node->left);
        if (node->right) s.push(node->right);
    }
}

int minPathSum(Node* root) {
    if (root == NULL) return INT_MAX;
    if (root->left == NULL && root->right == NULL) return root->data;

    int leftSum = minPathSum(root->left);
    int rightSum = minPathSum(root->right);

    return root->data + min(leftSum, rightSum);
}

int maxPathSum(Node* root) {
    if (root == NULL) return INT_MIN;
    if (root->left == NULL && root->right == NULL) return root->data;

    int leftSum = maxPathSum(root->left);
    int rightSum = maxPathSum(root->right);

    return root->data + max(leftSum, rightSum);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    struct Node* root = new Node(0); // Assuming A's value is 0
    root->left = new Node(3);        // B
    root->right = new Node(8);       // C
    root->right->left = new Node(7); // E
    root->right->right = new Node(10); // D
    root->right->right->right = new Node(15); // F

    cout << "Inorder Traversal: ";
    inorder(root); // Print inorder traversal
    cout << endl;

    int minSum = minPathSum(root);
    int maxSum = maxPathSum(root);

    cout << "Minimum Path Sum: " << minSum << endl;
    cout << "Maximum Path Sum: " << maxSum << endl;

    cout << "BFS Traversal: ";
    BFS(root);
    cout << endl;

    cout << "DFS Traversal: ";
    DFS(root);
    cout << endl;

    return 0;
}