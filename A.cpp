//1 Tree
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int value, char direction) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (direction == 'L') {
        root->left = insert(root->left, value, direction);
    } else {
        root->right = insert(root->right, value, direction);
    }
    return root;
}

void findMinMaxPathSums(Node* root, int currentSum, int& minSum, int& maxSum) {
    if (root == nullptr) {
        return;
    }
    currentSum += root->value;
    if (root->left == nullptr && root->right == nullptr) {
        minSum = min(minSum, currentSum);
        maxSum = max(maxSum, currentSum);
    }
    findMinMaxPathSums(root->left, currentSum, minSum, maxSum);
    findMinMaxPathSums(root->right, currentSum, minSum, maxSum);
}

void BFS(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->value << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << endl;
}

void DFS(Node* root) {
    if (root == nullptr) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        cout << current->value << " ";
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
    cout << endl;
}

int height(Node* node) {
    if (node == nullptr) return 0;
    return max(height(node->left), height(node->right)) + 1;
}

int getBalance(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

Node* balanceTree(Node* node) {
    int balance = getBalance(node);
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void heapify(Node* root) {
    if (root == nullptr) return;
    if (root->left && root->left->value < root->value) {
        swap(root->value, root->left->value);
        heapify(root->left);
    }
    if (root->right && root->right->value < root->value) {
        swap(root->value, root->right->value);
        heapify(root->right);
    }
}

void convertToMinHeap(Node* root) {
    if (root == nullptr) return;
    convertToMinHeap(root->left);
    convertToMinHeap(root->right);
    heapify(root);
}

int main() {
    Node* root = new Node(5);
    root = insert(root, 3, 'L'); 
    root = insert(root, 8, 'R'); 
    root->right = insert(root->right, 7, 'L'); 
    root->right = insert(root->right, 10, 'R');
    root->right->right = insert(root->right->right, 15, 'R'); 

    int minSum = INT_MAX, maxSum = INT_MIN;
    findMinMaxPathSums(root, 0, minSum, maxSum);
    cout << "Minimum Path Sum: " << minSum << endl;
    cout << "Maximum Path Sum: " << maxSum << endl;

    cout << "BFS Traversal: ";
    BFS(root);

    cout << "DFS Traversal: ";
    DFS(root);

    root = balanceTree(root);

    cout << "Balanced Tree BFS Traversal: ";
    BFS(root);

    convertToMinHeap(root);

    cout << "Min-Heap BFS Traversal: ";
    BFS(root);

    return 0;
}





//2 Merge Sort
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Merge Sort
void mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) return;
    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid), right(arr.begin() + mid, arr.end());
    
    mergeSort(left);
    mergeSort(right);

    arr.clear();
    merge(left.begin(), left.end(), right.begin(), right.end(), back_inserter(arr));
}

// Median
double findMedian(const vector<int>& arr) {
    int n = arr.size();
    return (n % 2 == 0) ? (arr[n / 2 - 1] + arr[n / 2]) / 2.0 : arr[n / 2];
}

int main() {
    vector<int> scores = {95, 82, 67, 58, 88, 100, 75, 91};
    mergeSort(scores);

    cout << "Sorted Scores: ";
    for (int score : scores) cout << score << " ";
    cout << endl;

    cout << "Median Score: " << findMedian(scores) << endl;
    return 0;
}







//3 Selection Sort
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void selectionSort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        swap(nums[i], nums[minIndex]);
    }
}

double findMedian(vector<int>& nums) {
    int n = nums.size();
    if (n % 2 == 0) {
        return (nums[n / 2 - 1] + nums[n / 2]) / 2.0;
    } else {
        return nums[n / 2];
    }
}

int main() {
    vector<int> nums = {45, 12, 67, 23, 89, 34, 56};

    selectionSort(nums);

    cout << "Sorted Numbers: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    double median = findMedian(nums);
    cout << "Median Number: " << median << endl;

    return 0;
}






//4. Hash
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 1000;

class HashTable {
    vector<string> table;
public:
    HashTable() : table(TABLE_SIZE, "") {}

    int hash(const string& key) {
        int hash = 0;
        for (char ch : key) hash = (hash * 31 + ch) % TABLE_SIZE;
        return hash;
    }

    void add(const string& name) {
        int index = hash(name);
        while (!table[index].empty() && table[index] != name)
            index = (index + 1) % TABLE_SIZE;
        table[index] = name;
    }

    bool exists(const string& name) {
        int index = hash(name), start = index;
        while (!table[index].empty()) {
            if (table[index] == name) return true;
            index = (index + 1) % TABLE_SIZE;
            if (index == start) break;
        }
        return false;
    }

    void remove(const string& name) {
        int index = hash(name), start = index;
        while (!table[index].empty()) {
            if (table[index] == name) {
                table[index] = "";
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == start) break;
        }
    }

    void display() {
        for (const auto& name : table)
            if (!name.empty()) cout << name << " ";
        cout << endl;
    }
};

int main() {
    HashTable ht;
    ht.add("Alice");
    ht.add("Bob");
    ht.add("Charlie");

    cout << "Check (Alice): " << (ht.exists("Alice") ? "Found" : "Not Found") << endl;
    cout << "Check (Daisy): " << (ht.exists("Daisy") ? "Found" : "Not Found") << endl;

    ht.remove("Bob");
    ht.display();

    return 0;
}





//5.
#include <iostream>
#include <queue>
#include <stack>
#include <deque>
#include <string>
using namespace std;

struct Player {
    string name;
    bool hasPowerUp;
    Player(string n, bool powerUp) : name(n), hasPowerUp(powerUp) {}
};

int main() {
    deque<Player> gameQueue; // Use deque to allow manipulation at both ends
    stack<string> completedStack;

    // Initial players joining the queue
    gameQueue.push_back(Player("Player 1", false));
    gameQueue.push_back(Player("Player 2", true));
    gameQueue.push_back(Player("Player 3", false));
    gameQueue.push_back(Player("Player 4", false));
    gameQueue.push_back(Player("Player 5", false));

    // Game process
    while (!gameQueue.empty()) {
        Player currentPlayer = gameQueue.front();
        gameQueue.pop_front(); // Remove the player from the front of the queue

        if (currentPlayer.hasPowerUp) {
            cout << currentPlayer.name << " uses a power-up and takes their turn immediately." << endl;
        } else {
            cout << currentPlayer.name << " takes their turn." << endl;
        }
        completedStack.push(currentPlayer.name); // Add the player to the stack
    }

    // Display completed stack
    cout << "Game over. Completed players in order: ";
    while (!completedStack.empty()) {
        cout << completedStack.top() << " ";
        completedStack.pop();
    }
    cout << endl;

    return 0;
}