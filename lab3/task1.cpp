#include <iostream>

/**
 * Task 1: Complete the Singly Linked List ADT (Deletion)
 *
 * Implements a singly linked list template class supporting:
 * - deleteAtHead: removes head node in O(1) time
 * - deleteAtTail: removes tail node in O(n) time (no tail pointer)
 * - ~LinkedList: destructor freeing all nodes in O(n) time
 *
 * Does not use any STL container.
 */
template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    // Constructor: initializes an empty linked list
    LinkedList() : head(nullptr) {}

    // Destructor: deletes every remaining node to prevent memory leaks
    // Time Complexity: O(n) - walks through all remaining nodes and frees them
    // Space Complexity: O(1)
    ~LinkedList() {
        clear();
    }

    // Deep copy constructor (Rule of Three)
    LinkedList(const LinkedList& other) : head(nullptr) {
        Node* curr = other.head;
        while (curr != nullptr) {
            insertAtTail(curr->data);
            curr = curr->next;
        }
    }

    // Deep copy assignment operator (Rule of Three)
    LinkedList& operator=(const LinkedList& other) {
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

    // Helper method to clear all nodes
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Inserts a new node at the front of the list
    // Time Complexity: O(1)
    void insertAtHead(T value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Inserts a new node at the end of the list
    // Time Complexity: O(n)
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
    }

    // Removes the node currently at the head of the list
    // Time Complexity: O(1) - directly updates the head pointer
    // Space Complexity: O(1)
    void deleteAtHead() {
        if (head == nullptr) {
            std::cout << "List is empty. Cannot delete from head." << std::endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Removes the node currently at the tail of the list
    // Time Complexity: O(n) - traverses to the second-to-last node (no tail pointer)
    // Space Complexity: O(1)
    void deleteAtTail() {
        if (head == nullptr) {
            std::cout << "List is empty. Cannot delete from tail." << std::endl;
            return;
        }
        // If there is only one node in the list
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        // Traverse to find the second-to-last node
        Node* curr = head;
        while (curr->next->next != nullptr) {
            curr = curr->next;
        }
        delete curr->next;
        curr->next = nullptr;
    }

    // Displays all elements in the list from head to tail
    // Time Complexity: O(n)
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

    // Returns the number of nodes currently in the list
    // Time Complexity: O(n)
    int size() const {
        int count = 0;
        Node* curr = head;
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    // Returns true if the list contains no nodes, false otherwise
    // Time Complexity: O(1)
    bool isEmpty() const {
        return head == nullptr;
    }
};

int main() {
    std::cout << "================ Task 1: Singly Linked List Deletion ================" << std::endl;
    LinkedList<int> list;

    // Example from lab manual
    std::cout << "\n--- Inserting elements (10, 20, 30, 40) ---" << std::endl;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtTail(40);
    std::cout << "List: ";
    list.display();

    std::cout << "\nCalling deleteAtHead()..." << std::endl;
    list.deleteAtHead();
    std::cout << "display() -> ";
    list.display();

    std::cout << "\nCalling deleteAtTail()..." << std::endl;
    list.deleteAtTail();
    std::cout << "display() -> ";
    list.display();

    // Boundary Testing: Deleting until list is empty
    std::cout << "\n--- Boundary Testing: Deleting remaining nodes ---" << std::endl;
    std::cout << "Calling deleteAtHead()..." << std::endl;
    list.deleteAtHead();
    std::cout << "display() -> ";
    list.display();

    std::cout << "Calling deleteAtTail()..." << std::endl;
    list.deleteAtTail();
    std::cout << "display() -> ";
    list.display();

    // Testing deletion on an empty list (must not crash)
    std::cout << "\n--- Testing delete on empty list ---" << std::endl;
    std::cout << "Calling deleteAtHead() on empty list: ";
    list.deleteAtHead();
    std::cout << "Calling deleteAtTail() on empty list: ";
    list.deleteAtTail();

    return 0;
}
