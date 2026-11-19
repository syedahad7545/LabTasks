#include <iostream>
#include <string>
using namespace std;

struct Flight {
    int flightNumber;
    string destination;
    int seatsAvailable;

    Flight(int number = 0, string dest = "", int seats = 0) {
        flightNumber = number;
        destination = dest;
        seatsAvailable = seats;
    }

    int key() const {
        return flightNumber;
    }

    bool operator<(const Flight& other) const {
        return flightNumber < other.flightNumber;
    }

    bool operator>(const Flight& other) const {
        return flightNumber > other.flightNumber;
    }

};

ostream& operator<<(ostream& out, const Flight& f) {
    out << "ID: " << f.flightNumber << " | " << f.destination << " | Seats: " << f.seatsAvailable;
    return out;
}

template <typename T>
class AVLTree {
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(T d) {
            data = d;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node* root;
    int llCount;
    int rrCount;
    int lrCount;
    int rlCount;

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    void updateHeight(Node* node) {
        int l = getHeight(node->left);
        int r = getHeight(node->right);
        node->height = 1 + (l > r ? l : r);
    }

    int getBalanceFactor(Node* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    void rotateRight(Node*& node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        node = newRoot;
    }

    void rotateLeft(Node*& node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        node = newRoot;
    }

    void rebalance(Node*& node) {
        updateHeight(node);
        int balance = getBalanceFactor(node);

        if (balance == 2) {
            if (getBalanceFactor(node->left) >= 0) {
                cout << "Imbalance at flight " << node->data.key() << ": LL case, right rotation performed." << endl;
                llCount++;
                rotateRight(node);
                return;
            }
            cout << "Imbalance at flight " << node->data.key() << ": LR case, left-right rotation performed." << endl;
            lrCount++;
            rotateLeft(node->left);
            rotateRight(node);
            return;
        }

        if (balance == -2) {
            if (getBalanceFactor(node->right) <= 0) {
                cout << "Imbalance at flight " << node->data.key() << ": RR case, left rotation performed." << endl;
                rrCount++;
                rotateLeft(node);
                return;
            }
            cout << "Imbalance at flight " << node->data.key() << ": RL case, right-left rotation performed." << endl;
            rlCount++;
            rotateRight(node->right);
            rotateLeft(node);
        }
    }

    bool insert(Node*& node, T data) {
        if (node == nullptr) {
            node = new Node(data);
            return true;
        }
        bool inserted = false;
        if (data < node->data) {
            inserted = insert(node->left, data);
        } else if (data > node->data) {
            inserted = insert(node->right, data);
        }
        if (inserted) {
            rebalance(node);
        }
        return inserted;
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
        bool removed = true;
        if (data < node->data) {
            removed = remove(node->left, data);
        } else if (data > node->data) {
            removed = remove(node->right, data);
        } else if (node->left == nullptr && node->right == nullptr) {
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
        if (removed && node != nullptr) {
            rebalance(node);
        }
        return removed;
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

    void printTree(Node* node, int depth) {
        if (node == nullptr) {
            return;
        }
        printTree(node->right, depth + 1);
        cout << string(depth * 8, ' ') << node->data.key() << " (bf=" << getBalanceFactor(node) << ")" << endl;
        printTree(node->left, depth + 1);
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
        int balance = getBalanceFactor(node);
        if (balance < -1 || balance > 1) {
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

    void clone(Node* node, Node*& copy) {
        if (node == nullptr) {
            copy = nullptr;
            return;
        }
        copy = new Node(node->data);
        copy->height = node->height;
        clone(node->left, copy->left);
        clone(node->right, copy->right);
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

    void resetCounters() {
        llCount = 0;
        rrCount = 0;
        lrCount = 0;
        rlCount = 0;
    }

public:
    AVLTree() {
        root = nullptr;
        resetCounters();
    }

    AVLTree(const AVLTree& other) {
        clone(other.root, root);
        resetCounters();
    }

    ~AVLTree() {
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

    void preorder() {
        preorder(root);
    }

    void postorder() {
        postorder(root);
    }

    void printTree() {
        printTree(root, 0);
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

    void printRotationStats() {
        cout << "LL rotations: " << llCount << endl;
        cout << "RR rotations: " << rrCount << endl;
        cout << "LR rotations: " << lrCount << endl;
        cout << "RL rotations: " << rlCount << endl;
    }

    AVLTree clone() {
        return AVLTree(*this);
    }

    void clear() {
        clear(root);
        resetCounters();
    }
};

int main() {
    AVLTree<Flight> board;
    int choice = -1;

    while (choice != 0) {
        cout << endl;
        cout << "1. Add flight" << endl;
        cout << "2. Cancel flight" << endl;
        cout << "3. Search flight" << endl;
        cout << "4. Display InOrder" << endl;
        cout << "5. Display PreOrder" << endl;
        cout << "6. Display PostOrder" << endl;
        cout << "7. Display Tree Structure" << endl;
        cout << "8. Board Height" << endl;
        cout << "9. Total Flight Count" << endl;
        cout << "10. Find Highest / Lowest Flight Number" << endl;
        cout << "11. Balance Check" << endl;
        cout << "12. Count Leaf Flights" << endl;
        cout << "13. Rotation Statistics" << endl;
        cout << "14. Copy Board" << endl;
        cout << "15. Clear Board" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        int number;
        if (choice == 1) {
            string destination;
            int seats;
            cout << "Enter Flight Number: ";
            cin >> number;
            cout << "Enter Destination: ";
            getline(cin >> ws, destination);
            cout << "Enter Seats Available: ";
            cin >> seats;
            if (board.insert(Flight(number, destination, seats))) {
                cout << "Flight added successfully." << endl;
            } else {
                cout << "Flight number already exists. Record rejected." << endl;
            }
        } else if (choice == 2) {
            cout << "Enter Flight Number to cancel: ";
            cin >> number;
            if (board.remove(Flight(number))) {
                cout << "Flight cancelled successfully." << endl;
            } else {
                cout << "Flight not found." << endl;
            }
        } else if (choice == 3) {
            cout << "Enter Flight Number to search: ";
            cin >> number;
            Flight* f = board.search(Flight(number));
            if (f != nullptr) {
                cout << "Flight found: " << *f << endl;
            } else {
                cout << "Flight not found." << endl;
            }
        } else if (choice == 4) {
            board.inorder();
        } else if (choice == 5) {
            board.preorder();
        } else if (choice == 6) {
            board.postorder();
        } else if (choice == 7) {
            cout << "Tree structure (right subtree on top):" << endl;
            board.printTree();
        } else if (choice == 8) {
            cout << "Board height: " << board.height() << endl;
        } else if (choice == 9) {
            cout << "Total flights: " << board.countNodes() << endl;
        } else if (choice == 10) {
            if (board.countNodes() > 0) {
                cout << "Highest: " << *board.findMax() << endl;
                cout << "Lowest: " << *board.findMin() << endl;
            }
        } else if (choice == 11) {
            if (board.isBalanced()) {
                cout << "The board is height-balanced." << endl;
            } else {
                cout << "The board is not height-balanced." << endl;
            }
        } else if (choice == 12) {
            cout << "Number of leaf flights: " << board.countLeafNodes() << endl;
        } else if (choice == 13) {
            board.printRotationStats();
        } else if (choice == 14) {
            AVLTree<Flight> copy = board.clone();
            cout << "Copied board:" << endl;
            copy.inorder();
        } else if (choice == 15) {
            board.clear();
            cout << "All flight records deleted." << endl;
        }
    }

    return 0;
}
