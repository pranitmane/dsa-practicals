#include <iostream>
using namespace std;

class Node {
public:
    Node *Left, *Right;
    string key, val;
    int height;
};

class Avl {
public:
    Node *create(Node *root, string key, string val) {
        root = new Node();
        root->key = key;
        root->val = val;
        root->Left = NULL;
        root->Right = NULL;
        root->height = 1;
        return root;
    }

    Node *insert(Node *root, string key, string val) {
        if (root == NULL) {
            return create(root, key, val);
        } else if (key < root->key) {
            root->Left = insert(root->Left, key, val);
        } else {
            root->Right = insert(root->Right, key, val);
        }
        root = balance(root); // Fix the balance after insertion
        return root;
    }

    int height(Node *temp) {
        int h = 0;
        if (temp != NULL) {
            int l_height = height(temp->Left);
            int r_height = height(temp->Right);
            int max_height = max(l_height, r_height);
            h = max_height + 1;
        }
        return h;
    }

    int balFac(Node *temp) {
        int l_height = height(temp->Left);
        int r_height = height(temp->Right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    Node *rr(Node *root) {
        Node *temp;
        temp = root->Right;
        root->Right = temp->Left;
        temp->Left = root;
        return temp;
    }

    Node *ll(Node *root) {
        Node *temp;
        temp = root->Left;
        root->Left = temp->Right;
        temp->Right = root;
        return temp;
    }

    Node *lr(Node *root) {
        Node *temp;
        temp = root->Left;
        root->Left = rr(temp);
        return ll(root);
    }

    Node *rl(Node *root) {
        Node *temp;
        temp = root->Right;
        root->Right = ll(temp);
        return rr(root);
    }

    Node *balance(Node *root) {
        int bal_factor = balFac(root);
        if (bal_factor > 1) {
            if (balFac(root->Left) > 0) {
                root = ll(root);
            } else {
                root = lr(root);
            }
        } else if (bal_factor < -1) {
            if (balFac(root->Right) > 0) {
                root = rl(root);
            } else {
                root = rr(root);
            }
        }
        return root;
    }

    void inorder(Node *root) {
        if (root == NULL) {
            return;
        }
        inorder(root->Left);
        cout << root->key << " " << root->val << endl;
        inorder(root->Right);
    }

    void modify(Node *root, string modKey) {
        if (root == NULL) {
            cout << "\nWord not Found!";
            return;
        }
        if (modKey.compare(root->key) < 0) {
            modify(root->Left, modKey);
        } else if (modKey.compare(root->key) > 0) {
            modify(root->Right, modKey);
        } else {
            cout << "\nWord Found!\nWord: " << root->key << "\t" << root->val;
            cout << "\nEnter the New Meaning: ";
            string NewMeaning;
            cin >> NewMeaning;
            root->val = NewMeaning;
            cout << "\nDictionary Modified!\n";
        }
    }

    void delet(Node *root, string delkey) {
        Node *current = root;
        Node *temp = NULL;
        bool isleft = false;

        while (current != NULL && current->key.compare(delkey) != 0) {
            if (current->key.compare(delkey) > 0) {
                temp = current;
                isleft = true;
                current = current->Left;
            } else if (current->key.compare(delkey) < 0) {
                temp = current;
                isleft = false;
                current = current->Right;
            }
        }

        if (current == NULL) {
            cout << "\nWord not Found!";
            return;
        }

        if (current->Left == NULL && current->Right == NULL) {
            if (isleft) {
                temp->Left = NULL;
            } else {
                temp->Right = NULL;
            }
            delete current;
        } else if (current->Left == NULL) {
            if (isleft) {
                temp->Left = current->Right;
            } else {
                temp->Right = current->Right;
            }
            delete current;
        } else if (current->Right == NULL) {
            if (isleft) {
                temp->Left = current->Left;
            } else {
                temp->Right = current->Left;
            }
            delete current;
        } else {
            Node *successor = findMinNode(current->Right);
            current->key = successor->key;
            current->val = successor->val;
            delet(current->Right, successor->key);
        }
        root = balance(root); // Fix the balance after deletion
        cout << "\nDeleted";
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current && current->Left != NULL)
            current = current->Left;
        return current;
    }
};

int main() {
    int choice;
    string key, val, modkey, delkey;
    Node *root = NULL;
    Avl avlobj;

    do {
        cout << "\n=====MENU=====";
        cout << "\n 1.Add Word \n 2.Delete Word \n 3.Update Word \n 4.Display \n 5.Exit ";
        cout << "\n Enter your Choice ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n Enter the Word and Meaning: ";
                cin >> key >> val;
                root = avlobj.insert(root, key, val);
                break;
            case 2:
                cout << "\n Enter the Word you want to Delete: ";
                cin >> delkey;
                avlobj.delet(root, delkey);
                break;
            case 3:
                cout << "\n Enter the Word you want to Update: ";
                cin >> modkey;
                avlobj.modify(root, modkey);
                break;
            case 4:
                avlobj.inorder(root);
                break;
            case 5:
                exit(0);
            default:
                cout << "\n Wrong Option.Try Again";
        }
    } while (choice != 5);
    return 0;
}
