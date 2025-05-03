#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string name;
    vector<Node*> children;

    Node(const string &n) : name(n) {}

    void addChild(Node *child) {
        children.push_back(child);
    }
};

void printTree(Node *node, int level = 0) {
    if (!node) return;
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    cout << node->name << endl;
    for (auto child : node->children) {
        printTree(child, level + 1);
    }
}

int main() {
    Node *book = new Node("Book");

    int numChapters;
    cout << "Enter number of chapters in the book: ";
    cin >> numChapters;
    cin.ignore();

    for (int i = 1; i <= numChapters; i++) {
        string chapterName;
        cout << "Enter name of chapter " << i << ": ";
        getline(cin, chapterName);
        Node *chapter = new Node("Chapter " + to_string(i) + ": " + chapterName);
        book->addChild(chapter);

        int numSections;
        cout << "Enter number of sections in chapter " << i << ": ";
        cin >> numSections;
        cin.ignore();

        for (int j = 1; j <= numSections; j++) {
            string sectionName;
            cout << "Enter name of section " << i << "." << j << ": ";
            getline(cin, sectionName);
            Node *section = new Node("Section " + to_string(i) + "." + to_string(j) + ": " + sectionName);
            chapter->addChild(section);

            int numSubsections;
            cout << "Enter number of subsections in section " << i << "." << j << ": ";
            cin >> numSubsections;
            cin.ignore();

            for (int k = 1; k <= numSubsections; k++) {
                string subsectionName;
                cout << "Enter name of subsection " << i << "." << j << "." << k << ": ";
                getline(cin, subsectionName);
                Node *subsection = new Node("Subsection " + to_string(i) + "." + to_string(j) + "." + to_string(k) + ": " + subsectionName);
                section->addChild(subsection);
            }
        }
    }

    cout << "\nBook Structure:" << endl;
    printTree(book);

    return 0;
}