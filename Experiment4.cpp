#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;

    Node(string key, string val) : keyword(key), meaning(val), left(nullptr), right(nullptr) {}
};

class DictionaryBST {
private:
    Node* root;

    Node* insert(Node* node, const string& key, const string& val) {
        if (!node) return new Node(key, val);
        if (key < node->keyword)
            node->left = insert(node->left, key, val);
        else if (key > node->keyword)
            node->right = insert(node->right, key, val);
        else
            node->meaning = val; // Update meaning if key exists
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, const string& key) {
        if (!node) return nullptr;
        if (key < node->keyword)
            node->left = deleteNode(node->left, key);
        else if (key > node->keyword)
            node->right = deleteNode(node->right, key);
        else {
            // Node found
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* temp = findMin(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right, temp->keyword);
            }
        }
        return node;
    }

    Node* search(Node* node, const string& key) {
        if (!node) return nullptr;
        if (key == node->keyword) return node;
        if (key < node->keyword)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->keyword << " : " << node->meaning << endl;
        inorder(node->right);
    }

    void reverseInorder(Node* node) {
        if (!node) return;
        reverseInorder(node->right);
        cout << node->keyword << " : " << node->meaning << endl;
        reverseInorder(node->left);
    }

    int height(Node* node) {
        if (!node) return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

public:
    DictionaryBST() : root(nullptr) {}

    void add(const string& key, const string& val) {
        root = insert(root, key, val);
    }

    void remove(const string& key) {
        root = deleteNode(root, key);
    }

    bool update(const string& key, const string& val) {
        Node* node = search(root, key);
        if (node) {
            node->meaning = val;
            return true;
        }
        return false;
    }

    void displayAscending() {
        if (!root) {
            cout << "Dictionary is empty." << endl;
            return;
        }
        cout << "Dictionary in ascending order:" << endl;
        inorder(root);
    }

    void displayDescending() {
        if (!root) {
            cout << "Dictionary is empty." << endl;
            return;
        }
        cout << "Dictionary in descending order:" << endl;
        reverseInorder(root);
    }

    int maxComparisons() {
        return height(root);
    }
};

int main() {
    DictionaryBST dict;
    int choice;
    string key, val;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add new keyword\n";
        cout << "2. Delete keyword\n";
        cout << "3. Update meaning of a keyword\n";
        cout << "4. Display dictionary in ascending order\n";
        cout << "5. Display dictionary in descending order\n";
        cout << "6. Find maximum comparisons for searching a keyword\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // to consume newline after choice input

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, val);
                dict.add(key, val);
                cout << "Keyword added/updated successfully.\n";
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dict.remove(key);
                cout << "Keyword deleted if it existed.\n";
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, val);
                if (dict.update(key, val))
                    cout << "Keyword updated successfully.\n";
                else
                    cout << "Keyword not found.\n";
                break;
            case 4:
                dict.displayAscending();
                break;
            case 5:
                dict.displayDescending();
                break;
            case 6:
                cout << "Maximum comparisons required: " << dict.maxComparisons() << endl;
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
