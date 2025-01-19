#include <iostream>
#include <map>
#include <string>

using namespace std;

class HashTable {
private:
    map<string, bool> table;

public:
    void addName(string name) {
        table[name] = true;
    }

    bool checkName(string name) {
        return table.find(name) != table.end();
    }

    void removeName(string name) {
        if (table.find(name) != table.end()) {
            table.erase(name);
        } else {
            cout << "Name not found in the table." << endl;
        }
    }

    void displayAllNames() {
        for (auto& u : table) {
            cout << u.first << endl;
        }
    }
};

int main() {
    HashTable ht;

    ht.addName("Alice");
    ht.addName("Bob");
    ht.addName("Charlie");

    cout << "Check Alice: " << (ht.checkName("Alice") ? "Found" : "Not Found") << endl;
    cout << "Check Dave: " << (ht.checkName("Dave") ? "Found" : "Not Found") << endl;

    cout << "All Names in Hash Table:" << endl;
    ht.displayAllNames();

    ht.removeName("Alice");
    cout << "Check Alice after removal: " << (ht.checkName("Alice") ? "Found" : "Not Found") << endl;

    cout << "All Names in Hash Table after removal:" << endl;
    ht.displayAllNames();

    return 0;
}