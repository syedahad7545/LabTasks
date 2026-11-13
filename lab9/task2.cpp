#include <iostream>
#include <string>
using namespace std;

struct Request {
    int requestId;
    string endpoint;
    int responseTime;

    Request(int id = 0, string ep = "", int time = 0) {
        requestId = id;
        endpoint = ep;
        responseTime = time;
    }

    int key() const {
        return requestId;
    }

    bool operator<(const Request& other) const {
        return requestId < other.requestId;
    }

    bool operator>(const Request& other) const {
        return requestId > other.requestId;
    }
};

ostream& operator<<(ostream& out, const Request& r) {
    out << "ID: " << r.requestId << " | " << r.endpoint << " | " << r.responseTime << " ms";
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

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int l = height(node->left);
        int r = height(node->right);
        return 1 + (l > r ? l : r);
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

    int height() {
        return height(root);
    }

    void clear() {
        clear(root);
    }
};

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
    bool showMessages;

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
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    Node* rebalance(Node* node) {
        updateHeight(node);
        int balance = getBalanceFactor(node);

        if (balance == 2) {
            if (getBalanceFactor(node->left) >= 0) {
                if (showMessages) {
                    cout << "Imbalance at request " << node->data.key() << ": LL case, right rotation performed." << endl;
                }
                llCount++;
                return rotateRight(node);
            }
            if (showMessages) {
                cout << "Imbalance at request " << node->data.key() << ": LR case, left-right rotation performed." << endl;
            }
            lrCount++;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance == -2) {
            if (getBalanceFactor(node->right) <= 0) {
                if (showMessages) {
                    cout << "Imbalance at request " << node->data.key() << ": RR case, left rotation performed." << endl;
                }
                rrCount++;
                return rotateLeft(node);
            }
            if (showMessages) {
                cout << "Imbalance at request " << node->data.key() << ": RL case, right-left rotation performed." << endl;
            }
            rlCount++;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
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
            node = rebalance(node);
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
            node = rebalance(node);
        }
        return removed;
    }

    int purgeBefore(Node*& node, T cutoff) {
        Node* smallest = findMin(node);
        if (smallest == nullptr || !(smallest->data < cutoff)) {
            return 0;
        }
        remove(node, smallest->data);
        return 1 + purgeBefore(node, cutoff);
    }

    int depthOf(Node* node, T data, int depth) {
        if (node == nullptr) {
            return 0;
        }
        if (data < node->data) {
            return depthOf(node->left, data, depth + 1);
        }
        if (data > node->data) {
            return depthOf(node->right, data, depth + 1);
        }
        return depth;
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
        int l = height(node->left);
        int r = height(node->right);
        if (l - r < -1 || l - r > 1) {
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
        showMessages = true;
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

    int purgeBefore(T cutoff) {
        return purgeBefore(root, cutoff);
    }

    int depthOf(T data) {
        return depthOf(root, data, 1);
    }

    void setShowMessages(bool show) {
        showMessages = show;
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

    void clear() {
        clear(root);
        resetCounters();
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
    AVLTree<Request> log;
    int choice = -1;

    while (choice != 0) {
        cout << endl;
        cout << "========= REQUEST LOG MONITOR =========" << endl;
        cout << "1.  Log request" << endl;
        cout << "2.  Remove request" << endl;
        cout << "3.  Search request" << endl;
        cout << "4.  Display InOrder" << endl;
        cout << "5.  Display Tree Structure" << endl;
        cout << "6.  Request Depth" << endl;
        cout << "7.  Purge Old Requests" << endl;
        cout << "8.  Log Height" << endl;
        cout << "9.  Total Request Count" << endl;
        cout << "10. Rotation Statistics" << endl;
        cout << "11. Balance Check" << endl;
        cout << "12. Stress Test" << endl;
        cout << "13. Clear Log" << endl;
        cout << "0.  Exit" << endl;
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            int id = readInt("Enter Request ID: ");
            if (log.search(Request(id)) != nullptr) {
                cout << "Request ID already exists. Request rejected." << endl;
                continue;
            }
            string endpoint;
            cout << "Enter Endpoint: ";
            getline(cin >> ws, endpoint);
            int time = readInt("Enter Response Time: ");
            log.insert(Request(id, endpoint, time));
            cout << "Request logged successfully." << endl;
        } else if (choice == 2) {
            int id = readInt("Enter Request ID to remove: ");
            if (log.remove(Request(id))) {
                cout << "Request removed successfully." << endl;
            } else {
                cout << "Request not found." << endl;
            }
        } else if (choice == 3) {
            int id = readInt("Enter Request ID: ");
            Request* r = log.search(Request(id));
            if (r != nullptr) {
                cout << "Request found: " << *r << endl;
            } else {
                cout << "Request not found." << endl;
            }
        } else if (choice == 4) {
            if (log.countNodes() == 0) {
                cout << "The log is empty." << endl;
            } else {
                log.inorder();
            }
        } else if (choice == 5) {
            if (log.countNodes() == 0) {
                cout << "The log is empty." << endl;
            } else {
                cout << "Tree structure (right subtree on top):" << endl;
                log.printTree();
            }
        } else if (choice == 6) {
            int id = readInt("Enter Request ID: ");
            int depth = log.depthOf(Request(id));
            if (depth == 0) {
                cout << "Request " << id << " was not found." << endl;
            } else {
                cout << "Request " << id << " is at depth " << depth << "." << endl;
            }
        } else if (choice == 7) {
            int cutoff = readInt("Enter cutoff Request ID: ");
            cout << log.purgeBefore(Request(cutoff)) << " requests purged." << endl;
        } else if (choice == 8) {
            cout << "Log height: " << log.height() << endl;
        } else if (choice == 9) {
            cout << "Total requests: " << log.countNodes() << endl;
        } else if (choice == 10) {
            log.printRotationStats();
        } else if (choice == 11) {
            if (log.isBalanced()) {
                cout << "The log is height-balanced." << endl;
            } else {
                cout << "The log is not height-balanced." << endl;
            }
        } else if (choice == 12) {
            AVLTree<Request>* avl = new AVLTree<Request>();
            BST<Request>* bst = new BST<Request>();
            avl->setShowMessages(false);
            cout << "Inserting requests 2001 to 2015 into a plain BST and an AVL tree..." << endl;
            for (int id = 2001; id <= 2015; id++) {
                avl->insert(Request(id, "/test", 100));
                bst->insert(Request(id, "/test", 100));
            }
            cout << "Plain BST height: " << bst->height() << endl;
            cout << "AVL tree height: " << avl->height() << endl;
            avl->printRotationStats();
            delete avl;
            delete bst;
            cout << "Temporary trees deleted." << endl;
        } else if (choice == 13) {
            log.clear();
            cout << "All requests deleted." << endl;
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
