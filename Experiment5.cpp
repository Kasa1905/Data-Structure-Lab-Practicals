#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

class TelephoneBookHashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<list<pair<string, string>>> table;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE;
        }
        return hash;
    }

public:
    TelephoneBookHashTable() {
        table.resize(TABLE_SIZE);
    }

    void add(const string& name, const string& phone) {
        int index = hashFunction(name);
        for (auto& entry : table[index]) {
            if (entry.first == name) {
                entry.second = phone; // Update existing
                cout << "Updated phone number for " << name << ".\n";
                return;
            }
        }
        table[index].push_back(make_pair(name, phone));
        cout << "Added " << name << " to telephone book.\n";
    }

    void remove(const string& name) {
        int index = hashFunction(name);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == name) {
                table[index].erase(it);
                cout << "Removed " << name << " from telephone book.\n";
                return;
            }
        }
        cout << "Name not found in telephone book.\n";
    }

    bool update(const string& name, const string& phone) {
        int index = hashFunction(name);
        for (auto& entry : table[index]) {
            if (entry.first == name) {
                entry.second = phone;
                cout << "Updated phone number for " << name << ".\n";
                return true;
            }
        }
        cout << "Name not found in telephone book.\n";
        return false;
    }

    void search(const string& name) {
        int index = hashFunction(name);
        for (const auto& entry : table[index]) {
            if (entry.first == name) {
                cout << "Phone number of " << name << " is " << entry.second << ".\n";
                return;
            }
        }
        cout << "Name not found in telephone book.\n";
    }

    void display() {
        cout << "Telephone Book Entries:\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (!table[i].empty()) {
                for (const auto& entry : table[i]) {
                    cout << "Name: " << entry.first << ", Phone: " << entry.second << endl;
                }
            }
        }
    }
};

int main() {
    TelephoneBookHashTable phoneBook;
    int choice;
    string name, phone;

    do {
        cout << "\nTelephone Book Menu:\n";
        cout << "1. Add new client\n";
        cout << "2. Delete client\n";
        cout << "3. Update client phone number\n";
        cout << "4. Search client phone number\n";
        cout << "5. Display all clients\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter client name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phone);
                phoneBook.add(name, phone);
                break;
            case 2:
                cout << "Enter client name to delete: ";
                getline(cin, name);
                phoneBook.remove(name);
                break;
            case 3:
                cout << "Enter client name to update: ";
                getline(cin, name);
                cout << "Enter new phone number: ";
                getline(cin, phone);
                phoneBook.update(name, phone);
                break;
            case 4:
                cout << "Enter client name to search: ";
                getline(cin, name);
                phoneBook.search(name);
                break;
            case 5:
                phoneBook.display();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
