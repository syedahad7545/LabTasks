#include <iostream>
#include <string>
using namespace std;

struct Order {
    int orderId;
    string customerName;
    int amount;

    Order(int id = 0, string name = "", int amt = 0) {
        orderId = id;
        customerName = name;
        amount = amt;
    }

    bool operator<(const Order& other) const {
        return orderId < other.orderId;
    }

    bool operator>(const Order& other) const {
        return orderId > other.orderId;
    }
};

ostream& operator<<(ostream& out, const Order& o) {
    out << "ID: " << o.orderId << " | " << o.customerName << " | Rs. " << o.amount;
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

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int l = height(node->left);
        int r = height(node->right);
        return 1 + (l > r ? l : r);
    }

    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int printRange(Node* node, T low, T high) {
        if (node == nullptr) {
            return 0;
        }
        int count = 0;
        if (low < node->data) {
            count += printRange(node->left, low, high);
        }
        if (!(node->data < low) && !(node->data > high)) {
            cout << node->data << endl;
            count++;
        }
        if (node->data < high) {
            count += printRange(node->right, low, high);
        }
        return count;
    }

    int countInRange(Node* node, T low, T high) {
        if (node == nullptr) {
            return 0;
        }
        int count = 0;
        if (low < node->data) {
            count += countInRange(node->left, low, high);
        }
        if (!(node->data < low) && !(node->data > high)) {
            count++;
        }
        if (node->data < high) {
            count += countInRange(node->right, low, high);
        }
        return count;
    }

    Node* findPredecessor(Node* node, T data, Node* best) {
        if (node == nullptr) {
            return best;
        }
        if (node->data < data) {
            return findPredecessor(node->right, data, node);
        }
        return findPredecessor(node->left, data, best);
    }

    Node* findSuccessor(Node* node, T data, Node* best) {
        if (node == nullptr) {
            return best;
        }
        if (node->data > data) {
            return findSuccessor(node->left, data, node);
        }
        return findSuccessor(node->right, data, best);
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

    ~BST() {
        clear();
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
        return node == nullptr ? nullptr : &node->data;
    }

    T* findMax() {
        Node* node = findMax(root);
        return node == nullptr ? nullptr : &node->data;
    }

    void inorder() {
        inorder(root);
    }

    int height() {
        return height(root);
    }

    int countNodes() {
        return countNodes(root);
    }

    int printRange(T low, T high) {
        return printRange(root, low, high);
    }

    int countInRange(T low, T high) {
        return countInRange(root, low, high);
    }

    T* findPredecessor(T data) {
        Node* node = findPredecessor(root, data, nullptr);
        return node == nullptr ? nullptr : &node->data;
    }

    T* findSuccessor(T data) {
        Node* node = findSuccessor(root, data, nullptr);
        return node == nullptr ? nullptr : &node->data;
    }

    void clear() {
        clear(root);
    }
};

int readInt(string prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        if (cin.eof()) {
            return 0;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. " << prompt;
    }
    return value;
}

int main() {
    BST<Order> orders;
    int choice = -1;

    while (choice != 0) {
        cout << endl;
        cout << "========= ORDER TRACKER =========" << endl;
        cout << "1.  Place order" << endl;
        cout << "2.  Cancel order" << endl;
        cout << "3.  Search order" << endl;
        cout << "4.  Display All Orders" << endl;
        cout << "5.  Orders in ID Range" << endl;
        cout << "6.  Count in ID Range" << endl;
        cout << "7.  Find Previous Order" << endl;
        cout << "8.  Find Next Order" << endl;
        cout << "9.  Total Order Count" << endl;
        cout << "10. Earliest / Latest" << endl;
        cout << "11. Order Tree Height" << endl;
        cout << "12. Clear All Orders" << endl;
        cout << "0.  Exit" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Order ID: ");
            if (orders.search(Order(id)) != nullptr) {
                cout << "Order ID already exists. Order rejected." << endl;
                continue;
            }
            string name;
            cout << "Enter Customer Name: ";
            getline(cin >> ws, name);
            int amount = readInt("Enter Amount: ");
            orders.insert(Order(id, name, amount));
            cout << "Order placed successfully." << endl;
        } else if (choice == 2) {
            int id = readInt("Enter Order ID to cancel: ");
            if (orders.remove(Order(id))) {
                cout << "Order cancelled successfully." << endl;
            } else {
                cout << "Order not found." << endl;
            }
        } else if (choice == 3) {
            int id = readInt("Enter Order ID: ");
            Order* o = orders.search(Order(id));
            if (o != nullptr) {
                cout << "Order found: " << *o << endl;
            } else {
                cout << "Order not found." << endl;
            }
        } else if (choice == 4) {
            if (orders.countNodes() == 0) {
                cout << "There are no orders." << endl;
            } else {
                orders.inorder();
            }
        } else if (choice == 5 || choice == 6) {
            int low = readInt("Enter first Order ID: ");
            int high = readInt("Enter second Order ID: ");
            if (low > high) {
                cout << "First Order ID cannot be larger than the second." << endl;
            } else if (choice == 5) {
                if (orders.printRange(Order(low), Order(high)) == 0) {
                    cout << "No orders in this range." << endl;
                }
            } else {
                cout << "Orders in range: " << orders.countInRange(Order(low), Order(high)) << endl;
            }
        } else if (choice == 7) {
            int id = readInt("Enter Order ID: ");
            Order* o = orders.findPredecessor(Order(id));
            if (o != nullptr) {
                cout << "Previous order: " << *o << endl;
            } else {
                cout << "No earlier order exists." << endl;
            }
        } else if (choice == 8) {
            int id = readInt("Enter Order ID: ");
            Order* o = orders.findSuccessor(Order(id));
            if (o != nullptr) {
                cout << "Next order: " << *o << endl;
            } else {
                cout << "No later order exists." << endl;
            }
        } else if (choice == 9) {
            cout << "Total orders: " << orders.countNodes() << endl;
        } else if (choice == 10) {
            if (orders.countNodes() == 0) {
                cout << "There are no orders." << endl;
            } else {
                cout << "Earliest order: " << *orders.findMin() << endl;
                cout << "Latest order: " << *orders.findMax() << endl;
            }
        } else if (choice == 11) {
            cout << "Order tree height: " << orders.height() << endl;
        } else if (choice == 12) {
            orders.clear();
            cout << "All orders deleted." << endl;
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
