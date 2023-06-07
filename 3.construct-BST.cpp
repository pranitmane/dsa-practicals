#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* ln;
    Node* rn;
};

class Tree {
public:
    Node* root;

    Node* createTree(int key) {
        root = new Node();
        root->key = key;
        root->ln = nullptr;
        root->rn = nullptr;
        return root;
    }

    void insertNode(int key, Node* root) {
        Node* node = new Node();
        node->key = key;
        if (root->key > key) {
            if (root->ln == nullptr) {
                root->ln = node;
            }
            else
                insertNode(key, root->ln);
        }
        else if (root->key < key) {
            if (root->rn == nullptr) {
                root->rn = node;
            }
            else
                insertNode(key, root->rn);
        }
    }

    void searchNode(int searchkey, Node* root) {
        if (root == nullptr) {
            cout << "No tree present";
            return;
        }
        if (root->key == searchkey) {
            cout << "Key found!!!";
            return;
        }
        else if (root->key > searchkey) {
            if (root->ln == nullptr) {
                cout << "Key is not present in the tree";
                return;
            }
            else
                searchNode(searchkey, root->ln);
        }
        else if (root->key < searchkey) {
            if (root->rn == nullptr) {
                cout << "Key is not present in the tree";
                return;
            }
            else
                searchNode(searchkey, root->rn);
        }
    }

    void displayInorder(Node* root) {
        if (root != nullptr) {
            displayInorder(root->ln);
            cout << root->key << "\n";
            displayInorder(root->rn);
        }
    }

    void displayMin(Node* root) {
        while (root->ln != nullptr) {
            root = root->ln;
        }
        cout << "Minimum number is " << root->key << "\n";
    }

    int longestPath(Node* root) {
        if (root == nullptr)
            return 0;

        int Lctr = longestPath(root->ln);
        int Rctr = longestPath(root->rn);
        if (Lctr > Rctr)
            return (Lctr + 1);
        else
            return (Rctr + 1);
    }

    Node* swapNodes(Node* root) {
        if (root == nullptr)
            return nullptr;

        Node* temp = root->ln;
        root->ln = root->rn;
        root->rn = temp;

        root->ln = swapNodes(root->ln);
        root->rn = swapNodes(root->rn);

        return root;
    }
};

int main() {
    int choice, order, flag = 0;
    int key, searchKey;
    Tree t1;
    Node* root = nullptr;

    do {
        cout<<"===== MENU ======"<<endl;
        cout << "\n 1. Enter a number \n 2. Display \n 3. Display min valued node \n 4. Swap left and right nodes \n 5. Search \n 6. No. of nodes in longest path \n 7. Exit"<<endl;
        cout<< "Enter your choice : ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter the number ";
            cin >> key;
            if (flag == 0) {
                root = t1.createTree(key);
                flag = 1;
            }
            else {
                t1.insertNode(key, root);
            }
            break;
        case 2:
            t1.displayInorder(root);
            break;
        case 3:
            t1.displayMin(root);
            break;
        case 4:
            root = t1.swapNodes(root);
            cout << "Swapped! The new list is: ";
            t1.displayInorder(root);
            break;
        case 5:
            cout << "\nEnter the key you want to search: ";
            cin >> searchKey;
            t1.searchNode(searchKey, root);
            break;
        case 6:
            cout << "The height of the tree or the longest path is: " << t1.longestPath(root) << "\n";
            break;
        case 7:
            return 0;
        }
    } while (choice != 7);

    return 0;
}
