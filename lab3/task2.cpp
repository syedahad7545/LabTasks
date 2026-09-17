#include <iostream>

/**
 * Task 2: Reverse a Linked List (Iterative)
 *
 * Implements an in-place iterative reversal of a singly linked list.
 *
 * Time Complexity: O(n) - Iterates through each of the n nodes exactly once.
 * Space Complexity: O(1) - Operates purely in-place using three pointer variables
 *                          (prev, curr, nextNode) with no auxiliary data structures.
 *
 * Restrictions followed:
 * - No recursion used.
 * - No copying values into an array or rebuilding the list.
 * - No STL containers used.
 * - Head is updated to the new first node.
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
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor to prevent memory leaks
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

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Inserts a new node at the end of the list
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

    /**
     * Reverses the singly linked list iteratively in place.
     *
     * Time Complexity: O(n) - Each node in the list of length n is visited once.
     * Space Complexity: O(1) - In-place pointer manipulation using three local pointers.
     */
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;

        while (curr != nullptr) {
            nextNode = curr->next; // Temporarily store reference to the next node
            curr->next = prev;     // Reverse the link to point to previous node
            prev = curr;           // Advance prev to current node
            curr = nextNode;       // Advance curr to next node
        }

        head = prev; // Update head pointer to the new first node (formerly last)
    }

    // Displays all elements in the list
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

    bool isEmpty() const {
        return head == nullptr;
    }
};

int main() {
    std::cout << "================ Task 2: Reverse a Linked List (Iterative) ================" << std::endl;

    // Test Case 1: Manual Example (10 20 30 40)
    std::cout << "\n--- Test Case 1: Multiple Elements (Manual Example) ---" << std::endl;
    LinkedList<int> list1;
    list1.insertAtTail(10);
    list1.insertAtTail(20);
    list1.insertAtTail(30);
    list1.insertAtTail(40);

    std::cout << "Before: ";
    list1.display();

    std::cout << "reverse()" << std::endl;
    list1.reverse();

    std::cout << "After:  ";
    list1.display();

    // Test Case 2: Single Node List (Boundary)
    std::cout << "\n--- Test Case 2: Single Node List ---" << std::endl;
    LinkedList<int> list2;
    list2.insertAtTail(100);
    std::cout << "Before: ";
    list2.display();
    list2.reverse();
    std::cout << "After:  ";
    list2.display();

    // Test Case 3: Empty List (Boundary)
    std::cout << "\n--- Test Case 3: Empty List ---" << std::endl;
    LinkedList<int> list3;
    std::cout << "Before: ";
    list3.display();
    list3.reverse();
    std::cout << "After:  ";
    list3.display();

    // Test Case 4: Two-element list
    std::cout << "\n--- Test Case 4: Two Elements ---" << std::endl;
    LinkedList<int> list4;
    list4.insertAtTail(5);
    list4.insertAtTail(15);
    std::cout << "Before: ";
    list4.display();
    list4.reverse();
    std::cout << "After:  ";
    list4.display();

    return 0;
}
