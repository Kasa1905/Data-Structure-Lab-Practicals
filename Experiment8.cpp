#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Dictionary {
private:
    static const int TABLE_SIZE = 10;
    vector<list<pair<string, string>>> table;

    int hashFunction(const string &key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE;
        }
        return hash;
    }

public:
    Dictionary() {
        table.resize(TABLE_SIZE);
    }

    void insert(const string &key, const string &value) {
        int index = hashFunction(key);
        for (auto &kv : table[index]) {
            if (kv.first == key) {
                cout << "Key already exists. Updating value." << endl;
                kv.second = value;
                return;
            }
        }
        table[index].push_back(make_pair(key, value));
        cout << "Inserted (" << key << ", " << value << ")" << endl;
    }

    void find(const string &key) {
        int index = hashFunction(key);
        for (auto &kv : table[index]) {
            if (kv.first == key) {
                cout << "Found: " << kv.second << endl;
                return;
            }
        }
        cout << "Key not found." << endl;
    }

    void remove(const string &key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                cout << "Key " << key << " deleted." << endl;
                return;
            }
        }
        cout << "Key not found." << endl;
    }
};

void menu() {
    Dictionary dict;
    int choice;
    string key, value;

    do {
        cout << "\nDictionary Operations Menu:\n";
        cout << "1. Insert (key, value)\n";
        cout << "2. Find value by key\n";
        cout << "3. Delete key\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                dict.find(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.remove(key);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;
}
