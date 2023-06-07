#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

int cnt = 0;

class node {
public:
    node* left;
    char word[50];
    char mean[50];
    node* right;
};

class BT {
public:
    node* root;
    
    BT() {
        root = nullptr;
    }
    
    void create();
    node* insert(node*, node*);
    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void search(node*, const char[]);
    void modify(node*, const char[]);
    node* dlt(node*, const char[]);
    node* FindMin(node*);
};

void BT::create() {
    int op;
    node* temp;
    
    do {
        temp = new node;
        
        cout << "Enter A Word: ";
        cin >> temp->word;
        cout << "Enter a meaning: ";
        cin >> temp->mean;
        
        temp->left = temp->right = nullptr;
        
        if (root == nullptr) {
            root = temp;
        } else {
            root = insert(root, temp);
        }
        
        cout << "Want to insert again? (1/0): ";
        cin >> op;
    } while (op == 1);
}

node* BT::insert(node* root, node* temp) {
    if (strcmp(temp->word, root->word) < 0) {
        if (root->left == nullptr) {
            root->left = temp;
        } else {
            insert(root->left, temp);
        }
    } else {
        if (root->right == nullptr) {
            root->right = temp;
        } else {
            insert(root->right, temp);
        }
    }
    
    return root;
}

void BT::inorder(node* temp) {
    if (temp != nullptr) {
        inorder(temp->left);
        cout << temp->word << "->" << temp->mean << ", ";
        inorder(temp->right);
    }
}

void BT::preorder(node* temp) {
    if (temp != nullptr) {
        cout << temp->word << "->" << temp->mean << ", ";
        preorder(temp->left);
        preorder(temp->right);
    }
}

void BT::postorder(node* temp) {
    if (temp != nullptr) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->word << "->" << temp->mean << ", ";
    }
}

void BT::search(node* temp, const char src[]) {
    if (temp != nullptr) {
        if (strcmp(temp->word, src) == 0) {
            cout << "\nWord Found";
            cout << "\nWord: " << temp->word;
            cout << "\nMeaning: " << temp->mean;
            cnt++;
        }
        
        if (strcmp(src, temp->word) > 0) {
            search(temp->right, src);
            cnt++;
        } else {
            search(temp->left, src);
            cnt++;
        }
    } else {
        cout << "\nWord Not Found";
        cout << "\nTotal number of comparisons to search an element is: " << cnt;
    }
}

void BT::modify(node* temp, const char src[]) {
    if (temp != nullptr) {
        if (strcmp(temp->word, src) == 0) {
            cout << "\nWord Found";
            cout << "\nEnter New Meaning Of Word: " << temp->word;
            cin >> temp->mean;
        } else {
            if (strcmp(temp->word, src) < 0) {
                modify(temp->right, src);
            } else if (strcmp(temp->word, src) > 0) {
                modify(temp->left, src);
            }
        }
    } else {
        cout << "\nWord Not Found";
    }
}

node* BT::dlt(node* root, const char src[]) {
    if (root != nullptr) {
        if (strcmp(root->word, src) > 0) {
            root->left = dlt(root->left, src);
        } else if (strcmp(root->word, src) < 0) {
            root->right = dlt(root->right, src);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete(root);
                root = nullptr;
            } else if (root->left == nullptr && root->right != nullptr) {
                node* temp = root;
                root = root->right;
                strcpy(root->word, temp->word);
                strcpy(root->mean, temp->mean);
                temp->right = nullptr;
                delete(temp);
            } else if (root->right == nullptr) {
                node* temp = root;
                root = root->left;
                strcpy(root->word, temp->word);
                strcpy(root->mean, temp->mean);
                temp->left = nullptr;
                delete(temp);
            } else {
                node* temp = FindMin(root->right);
                strcpy(root->word, temp->word);
                strcpy(root->mean, temp->mean);
                root->right = dlt(root->right, temp->word);
            }
        }
    }
    
    return root;
}

node* BT::FindMin(node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    
    return root;
}

int main() {
    BT b;
    int op;
    char src[100];
    
    while (1) {
        cout << "\n";
        cout << "1. Insert Binary Search Tree" << endl;
        cout << "2. Display Inorder, Preorder, and Postorder" << endl;
        cout << "3. Search The Word" << endl;
        cout << "4. Modify Meaning of Word" << endl;
        cout << "5. Delete Word From Dictionary" << endl;
        cout << "6. Exit" << endl;
        
        cout << "Enter Your Choice: ";
        cin >> op;
        
        switch (op) {
            case 1:
                b.create();
                break;
            case 2:
                cout << "Inorder: ";
                b.inorder(b.root);
                cout << endl;
                cout << "Preorder: ";
                b.preorder(b.root);
                cout << endl;
                cout << "Postorder: ";
                b.postorder(b.root);
                cout << endl;
                break;
            case 3:
                cnt = 0;
                cout << "Enter the Word you want to search: ";
                cin >> src;
                b.search(b.root, src);
                break;
            case 4:
                cout << "Enter The Word you want to Modify: ";
                cin >> src;
                b.modify(b.root, src);
                break;
            case 5:
                cout << "Enter the word you want to delete: ";
                cin >> src;
                b.dlt(b.root, src);
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << "Invalid Option" << endl;
                break;
        }
    }
    
    return 0;
}
