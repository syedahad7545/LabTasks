#include <iostream>

/**
 * Task 4: Complete the Doubly Linked List ADT
 *
 * Implements a template class DoublyLinkedList<T> without a tail pointer.
 * Each node stores data, prev, and next pointers.
 *
 * Complexity Requirements:
 * - insertAtHead: O(1)
 * - insertAtTail: O(n) (no tail pointer)
 * - deleteAtHead: O(1)
 * - deleteAtTail: O(n) (no tail pointer)
 * - display: O(n)
 * - displayReverse: O(n) (walks to tail then steps backward via prev pointers)
 * - size: O(n) - uses on-demand node count approach
 * - isEmpty: O(1)
 * - ~DoublyLinkedList: O(n)
 */
template <typename T>
class DoublyLinkedList {
public:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;

        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

private:
    Node* head;

public:
    // Constructor: initializes an empty list
    DoublyLinkedList() : head(nullptr) {}

    // Destructor: deletes all allocated nodes to prevent memory leaks
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    ~DoublyLinkedList() {
        clear();
    }

    // Deep copy constructor (Rule of Three)
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr) {
        Node* curr = other.head;
        while (curr != nullptr) {
            insertAtTail(curr->data);
            curr = curr->next;
        }
    }

    // Deep copy assignment operator (Rule of Three)
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* curr = other.head;
            while (curr != nullptr) {
                insertAtTail(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Clears all nodes in the list
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Inserts a new node at the head of the list
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    void insertAtHead(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // Inserts a new node at the tail of the list
    // Time Complexity: O(n) - traverses to the tail as no tail pointer is stored
    // Space Complexity: O(1)
    void insertAtTail(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->prev = curr;
    }

    // Removes the node currently at the head of the list
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    void deleteAtHead() {
        if (head == nullptr) {
            std::cout << "List is empty. Cannot delete from head." << std::endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
    }

    // Removes the node currently at the tail of the list
    // Time Complexity: O(n) - traverses to the tail
    // Space Complexity: O(1)
    void deleteAtTail() {
        if (head == nullptr) {
            std::cout << "List is empty. Cannot delete from tail." << std::endl;
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->prev->next = nullptr;
        delete curr;
    }

    // Prints every node's value in order from head to tail
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    void display() const {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* curr = head;
        while (curr != nullptr) {
            std::cout << curr->data;
            if (curr->next != nullptr) {
                std::cout << " ";
            }
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    // Prints every node's value in reverse from tail to head using prev pointers
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    void displayReverse() const {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        // Step 1: Walk to the last node
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        // Step 2: Traverse backward using prev pointers
        while (curr != nullptr) {
            std::cout << curr->data;
            if (curr->prev != nullptr) {
                std::cout << " ";
            }
            curr = curr->prev;
        }
        std::cout << std::endl;
    }

    // Returns the number of nodes currently in the list
    // Approach used: Count nodes on demand
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    int size() const {
        int count = 0;
        Node* curr = head;
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    // Returns true if list has no elements, false otherwise
    // Approach used: Direct head pointer check
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    bool isEmpty() const {
        return head == nullptr;
    }
};

int main() {
    std::cout << "================ Task 4: Doubly Linked List ADT ================" << std::endl;

    DoublyLinkedList<int> list;

    // Follow the exact steps from the manual
    std::cout << "\n--- Step 1: Performing insertions as per manual example ---" << std::endl;
    list.insertAtHead(20);
    list.insertAtHead(10);
    list.insertAtTail(30);
    list.insertAtTail(40);

    std::cout << "display()        -> ";
    list.display();

    std::cout << "displayReverse() -> ";
    list.displayReverse();

    std::cout << "\n--- Step 2: deleteAtHead() ---" << std::endl;
    list.deleteAtHead();
    std::cout << "display() -> ";
    list.display();

    std::cout << "\n--- Step 3: deleteAtTail() ---" << std::endl;
    list.deleteAtTail();
    std::cout << "display() -> ";
    list.display();

    std::cout << "\nCurrent size(): " << list.size() << " (Expected: 2)" << std::endl;
    std::cout << "isEmpty(): " << (list.isEmpty() ? "true" : "false") << " (Expected: false)" << std::endl;

    std::cout << "\n--- Step 4: Deleting remaining nodes down to empty ---" << std::endl;
    list.deleteAtHead(); // removes 20
    std::cout << "After deleteAtHead(): ";
    list.display();

    list.deleteAtTail(); // removes 30 (last node)
    std::cout << "After deleteAtTail(): ";
    list.display();

    std::cout << "isEmpty() now: " << (list.isEmpty() ? "true" : "false") << " (Expected: true)" << std::endl;
    std::cout << "size() now: " << list.size() << " (Expected: 0)" << std::endl;

    std::cout << "\n--- Step 5: Testing display on empty list ---" << std::endl;
    std::cout << "display(): ";
    list.display();
    std::cout << "displayReverse(): ";
    list.displayReverse();

    std::cout << "\n--- Step 6: Testing delete on empty list ---" << std::endl;
    std::cout << "deleteAtHead(): ";
    list.deleteAtHead();
    std::cout << "deleteAtTail(): ";
    list.deleteAtTail();

    return 0;
}
