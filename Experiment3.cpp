#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    int height(Node* node) {
        if (!node) return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    int findMin(Node* node) {
        if (!node) return -1; // or throw exception if tree empty
        while (node->left)
            node = node->left;
        return node->data;
    }

    void mirror(Node* node) {
        if (!node) return;
        mirror(node->left);
        mirror(node->right);
        swap(node->left, node->right);
    }

    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        if (val < node->data)
            return search(node->left, val);
        else
            return search(node->right, val);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    int height() {
        return height(root);
    }

    int findMin() {
        return findMin(root);
    }

    void mirror() {
        mirror(root);
    }

    bool search(int val) {
        return search(root, val);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int choice, val;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert node\n";
        cout << "2. Find height (number of nodes in longest path)\n";
        cout << "3. Find minimum value\n";
        cout << "4. Mirror the tree\n";
        cout << "5. Search for a value\n";
        cout << "6. Display inorder traversal\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                cout << "Value inserted.\n";
                break;
            case 2:
                cout << "Height of the tree: " << tree.height() << endl;
                break;
            case 3:
                val = tree.findMin();
                if (val == -1)
                    cout << "Tree is empty.\n";
                else
                    cout << "Minimum value in the tree: " << val << endl;
                break;
            case 4:
                tree.mirror();
                cout << "Tree mirrored.\n";
                break;
            case 5:
                cout << "Enter value to search: ";
                cin >> val;
                if (tree.search(val))
                    cout << "Value found in the tree.\n";
                else
                    cout << "Value not found in the tree.\n";
                break;
            case 6:
                cout << "Inorder traversal: ";
                tree.inorder();
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
