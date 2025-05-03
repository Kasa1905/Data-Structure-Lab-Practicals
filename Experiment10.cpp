#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct AVLNode {
    string keyword;
    string meaning;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(string k, string m) : keyword(k), meaning(m), height(1), left(nullptr), right(nullptr) {}
};

class AVLTreeDictionary {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode* insertRec(AVLNode* node, const string& keyword, const string& meaning) {
        if (!node)
            return new AVLNode(keyword, meaning);

        if (keyword < node->keyword)
            node->left = insertRec(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insertRec(node->right, keyword, meaning);
        else {
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && keyword < node->left->keyword)
            return rightRotate(node);

        if (balance < -1 && keyword > node->right->keyword)
            return leftRotate(node);

        if (balance > 1 && keyword > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    AVLNode* deleteRec(AVLNode* node, const string& keyword) {
        if (!node)
            return node;

        if (keyword < node->keyword)
            node->left = deleteRec(node->left, keyword);
        else if (keyword > node->keyword)
            node->right = deleteRec(node->right, keyword);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;
                delete temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteRec(node->right, temp->keyword);
            }
        }

        if (!node)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* searchNode(AVLNode* node, const string& keyword) {
        if (!node || node->keyword == keyword)
            return node;

        if (keyword < node->keyword)
            return searchNode(node->left, keyword);
        else
            return searchNode(node->right, keyword);
    }

    void inorder(AVLNode* node) {
        if (node) {
            inorder(node->left);
            cout << node->keyword << " : " << node->meaning << endl;
            inorder(node->right);
        }
    }

    void reverseInorder(AVLNode* node) {
        if (node) {
            reverseInorder(node->right);
            cout << node->keyword << " : " << node->meaning << endl;
            reverseInorder(node->left);
        }
    }

public:
    AVLTreeDictionary() : root(nullptr) {}

    void insert(const string& keyword, const string& meaning) {
        root = insertRec(root, keyword, meaning);
    }

    void deleteKeyword(const string& keyword) {
        root = deleteRec(root, keyword);
    }

    bool update(const string& keyword, const string& newMeaning) {
        AVLNode* node = searchNode(root, keyword);
        if (node) {
            node->meaning = newMeaning;
            return true;
        }
        return false;
    }

    string search(const string& keyword) {
        AVLNode* node = searchNode(root, keyword);
        return node ? node->meaning : "Not found";
    }

    void displayAscending() {
        cout << "Dictionary in Ascending Order:" << endl;
        inorder(root);
    }

    void displayDescending() {
        cout << "Dictionary in Descending Order:" << endl;
        reverseInorder(root);
    }

    int maxComparisons() {
        return height(root);
    }
};

int main() {
    AVLTreeDictionary dictionary;
    int choice;
    string keyword, meaning;

    do {
        cout << "\nDictionary Operations using AVL Tree:" << endl;
        cout << "1. Add new keyword" << endl;
        cout << "2. Delete keyword" << endl;
        cout << "3. Update meaning of a keyword" << endl;
        cout << "4. Display dictionary in ascending order" << endl;
        cout << "5. Display dictionary in descending order" << endl;
        cout << "6. Find maximum comparisons required to find any keyword" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, keyword);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dictionary.insert(keyword, meaning);
                cout << "Keyword added/updated successfully." << endl;
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, keyword);
                dictionary.deleteKeyword(keyword);
                cout << "Keyword deleted if it existed." << endl;
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, keyword);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                if (dictionary.update(keyword, meaning)) {
                    cout << "Keyword updated successfully." << endl;
                } else {
                    cout << "Keyword not found." << endl;
                }
                break;
            case 4:
                dictionary.displayAscending();
                break;
            case 5:
                dictionary.displayDescending();
                break;
            case 6:
                cout << "Maximum comparisons required to find any keyword: " << dictionary.maxComparisons() << endl;
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 7);

    return 0;
}