#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    int copies;

    Book(int i = 0, string t = "", int c = 0) {
        id = i;
        title = t;
        copies = c;
    }

    bool operator<(const Book& other) const {
        return id < other.id;
    }

    bool operator>(const Book& other) const {
        return id > other.id;
    }

    bool operator==(const Book& other) const {
        return id == other.id;
    }
};

ostream& operator<<(ostream& out, const Book& b) {
    out << "ID: " << b.id << " | " << b.title << " | Copies: " << b.copies;
    return out;
}

template <typename T>
class BST {
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T d) {
            data = d;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    bool insert(Node*& node, T data) {
        if (node == nullptr) {
            node = new Node(data);
            return true;
        }
        if (data < node->data) {
            return insert(node->left, data);
        }
        if (data > node->data) {
            return insert(node->right, data);
        }
        return false;
    }

    T* search(Node* node, T data) {
        if (node == nullptr) {
            return nullptr;
        }
        if (data < node->data) {
            return search(node->left, data);
        }
        if (data > node->data) {
            return search(node->right, data);
        }
        return &node->data;
    }

    Node* findMin(Node* node) {
        if (node == nullptr || node->left == nullptr) {
            return node;
        }
        return findMin(node->left);
    }

    Node* findMax(Node* node) {
        if (node == nullptr || node->right == nullptr) {
            return node;
        }
        return findMax(node->right);
    }

    bool remove(Node*& node, T data) {
        if (node == nullptr) {
            return false;
        }
        if (data < node->data) {
            return remove(node->left, data);
        }
        if (data > node->data) {
            return remove(node->right, data);
        }
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* successor = findMin(node->right);
            node->data = successor->data;
            remove(node->right, successor->data);
        }
        return true;
    }

    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->data << endl;
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->data << endl;
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << node->data << endl;
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int l = height(node->left);
        int r = height(node->right);
        return 1 + (l > r ? l : r);
    }

    bool isBalanced(Node* node) {
        if (node == nullptr) {
            return true;
        }
        int diff = height(node->left) - height(node->right);
        if (diff < -1 || diff > 1) {
            return false;
        }
        return isBalanced(node->left) && isBalanced(node->right);
    }

    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeafNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return countLeafNodes(node->left) + countLeafNodes(node->right);
    }

    Node* clone(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node* copy = new Node(node->data);
        copy->left = clone(node->left);
        copy->right = clone(node->right);
        return copy;
    }

    void clear(Node*& node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }

public:
    BST() {
        root = nullptr;
    }

    BST(const BST& other) {
        root = clone(other.root);
    }

    BST& operator=(const BST& other) {
        if (this != &other) {
            clear();
            root = clone(other.root);
        }
        return *this;
    }

    ~BST() {
        clear();
    }

    bool isEmpty() {
        return root == nullptr;
    }

    bool insert(T data) {
        return insert(root, data);
    }

    T* search(T data) {
        return search(root, data);
    }

    bool remove(T data) {
        return remove(root, data);
    }

    T* findMin() {
        Node* node = findMin(root);
        if (node == nullptr) {
            return nullptr;
        }
        return &node->data;
    }

    T* findMax() {
        Node* node = findMax(root);
        if (node == nullptr) {
            return nullptr;
        }
        return &node->data;
    }

    void inorder() {
        inorder(root);
    }

    void preorder() {
        preorder(root);
    }

    void postorder() {
        postorder(root);
    }

    int height() {
        return height(root);
    }

    bool isBalanced() {
        return isBalanced(root);
    }

    int countNodes() {
        return countNodes(root);
    }

    int countLeafNodes() {
        return countLeafNodes(root);
    }

    BST clone() {
        BST copy;
        copy.root = clone(root);
        return copy;
    }

    void clear() {
        clear(root);
    }
};

int main() {
    BST<Book> catalog;
    int choice = -1;

    while (choice != 0 && cin) {
        cout << endl;
        cout << "1. Add new book" << endl;
        cout << "2. Remove book" << endl;
        cout << "3. Search book" << endl;
        cout << "4. Display InOrder" << endl;
        cout << "5. Display PreOrder" << endl;
        cout << "6. Display PostOrder" << endl;
        cout << "7. Catalog Depth" << endl;
        cout << "8. Total Book Count" << endl;
        cout << "9. Find Highest / Lowest Book ID" << endl;
        cout << "10. Balance Check" << endl;
        cout << "11. Count Leaf Books" << endl;
        cout << "12. Copy Catalog" << endl;
        cout << "13. Clear Catalog" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Book ID: ";
            int id;
            cin >> id;
            if (catalog.search(Book(id)) != nullptr) {
                cout << "Book ID already exists. Record rejected." << endl;
                continue;
            }
            cout << "Enter Title: ";
            string title;
            cin.ignore();
            getline(cin, title);
            cout << "Enter Copies Available: ";
            int copies = 0;
            cin >> copies;
            if (copies < 0) {
                cout << "Copies cannot be negative. Record rejected." << endl;
                continue;
            }
            catalog.insert(Book(id, title, copies));
            cout << "Book added successfully." << endl;
        } else if (choice == 2) {
            cout << "Enter Book ID to remove: ";
            int id;
            cin >> id;
            if (catalog.remove(Book(id))) {
                cout << "Book removed successfully." << endl;
            } else {
                cout << "Book with ID " << id << " was not found." << endl;
            }
        } else if (choice == 3) {
            cout << "Enter Book ID to search: ";
            int id;
            cin >> id;
            Book* b = catalog.search(Book(id));
            if (b != nullptr) {
                cout << "Book found: " << *b << endl;
            } else {
                cout << "Book with ID " << id << " was not found." << endl;
            }
        } else if (choice >= 4 && choice <= 6) {
            if (catalog.isEmpty()) {
                cout << "The catalog is empty." << endl;
            } else if (choice == 4) {
                catalog.inorder();
            } else if (choice == 5) {
                catalog.preorder();
            } else {
                catalog.postorder();
            }
        } else if (choice == 7) {
            cout << "Catalog depth: " << catalog.height() << endl;
        } else if (choice == 8) {
            cout << "Total books: " << catalog.countNodes() << endl;
        } else if (choice == 9) {
            if (catalog.isEmpty()) {
                cout << "The catalog is empty." << endl;
            } else {
                cout << "Highest: " << *catalog.findMax() << endl;
                cout << "Lowest: " << *catalog.findMin() << endl;
            }
        } else if (choice == 10) {
            if (catalog.isBalanced()) {
                cout << "The catalog is height-balanced." << endl;
            } else {
                cout << "The catalog is not height-balanced." << endl;
            }
        } else if (choice == 11) {
            cout << "Number of leaf books: " << catalog.countLeafNodes() << endl;
        } else if (choice == 12) {
            BST<Book> copy = catalog.clone();
            if (copy.isEmpty()) {
                cout << "The copied catalog is empty." << endl;
            } else {
                cout << "Copied catalog:" << endl;
                copy.inorder();
            }
        } else if (choice == 13) {
            catalog.clear();
            cout << "All book records deleted." << endl;
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
