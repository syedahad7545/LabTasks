#include <iostream>

/**
 * Task 3: Merge Two Sorted Linked Lists
 *
 * Merges another sorted singly linked list into the current list by relinking existing nodes.
 *
 * Time Complexity: O(n + m) - Where n and m are the number of nodes in the two lists.
 *                            Each node is visited and relinked at most once.
 * Space Complexity: O(1)    - Operates purely in-place by updating next pointers.
 *                            No new nodes or auxiliary arrays are allocated.
 *
 * Restrictions followed:
 * - No new nodes allocated.
 * - No arrays or STL containers used.
 * - Assumes both input lists are sorted in ascending order.
 * - The other list is left empty (other.head = nullptr) after the merge.
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

    // Destructor
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

    // Inserts a new node at the tail of the list
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
     * Merges 'other' sorted linked list into 'this' sorted linked list by relinking existing nodes.
     *
     * Time Complexity:  O(n + m) where n = size of *this and m = size of other.
     * Space Complexity: O(1) extra space (in-place relinking, no new node allocations).
     */
    void mergeSorted(LinkedList<T>& other) {
        // Prevent self-merging which would create a cycle
        if (this == &other) {
            return;
        }

        // If the other list is empty, nothing needs to be merged
        if (other.head == nullptr) {
            return;
        }

        // If this list is empty, simply take ownership of other's head
        if (this->head == nullptr) {
            this->head = other.head;
            other.head = nullptr;
            return;
        }

        Node* p1 = this->head;
        Node* p2 = other.head;
        Node* newHead = nullptr;
        Node* tail = nullptr;

        // Choose the smaller starting node for the merged list
        if (p1->data <= p2->data) {
            newHead = p1;
            p1 = p1->next;
        } else {
            newHead = p2;
            p2 = p2->next;
        }
        tail = newHead;

        // Traverse and relink nodes in ascending order
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->data <= p2->data) {
                tail->next = p1;
                p1 = p1->next;
            } else {
                tail->next = p2;
                p2 = p2->next;
            }
            tail = tail->next;
        }

        // Attach any remaining nodes from either list
        if (p1 != nullptr) {
            tail->next = p1;
        } else {
            tail->next = p2;
        }

        this->head = newHead;
        other.head = nullptr; // Crucial: other list is left empty
    }

    // Displays all elements in the list
    void display() const {
        if (head == nullptr) {
            std::cout << "(empty)" << std::endl;
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
    std::cout << "================ Task 3: Merge Two Sorted Linked Lists ================" << std::endl;

    // Test Case 1: Manual Example (A: 1 3 5, B: 2 4 6)
    std::cout << "\n--- Test Case 1: Manual Example ---" << std::endl;
    LinkedList<int> A;
    A.insertAtTail(1);
    A.insertAtTail(3);
    A.insertAtTail(5);

    LinkedList<int> B;
    B.insertAtTail(2);
    B.insertAtTail(4);
    B.insertAtTail(6);

    std::cout << "List A: ";
    A.display();
    std::cout << "List B: ";
    B.display();

    std::cout << "\nA.mergeSorted(B)" << std::endl;
    A.mergeSorted(B);

    std::cout << "A: ";
    A.display();
    std::cout << "B: ";
    B.display();

    // Test Case 2: One list is empty initially
    std::cout << "\n--- Test Case 2: List A is empty, List B has elements ---" << std::endl;
    LinkedList<int> emptyA;
    LinkedList<int> populatedB;
    populatedB.insertAtTail(10);
    populatedB.insertAtTail(20);
    populatedB.insertAtTail(30);

    std::cout << "List A: ";
    emptyA.display();
    std::cout << "List B: ";
    populatedB.display();

    std::cout << "emptyA.mergeSorted(populatedB)" << std::endl;
    emptyA.mergeSorted(populatedB);

    std::cout << "A: ";
    emptyA.display();
    std::cout << "B: ";
    populatedB.display();

    // Test Case 3: List B is empty initially
    std::cout << "\n--- Test Case 3: List A has elements, List B is empty ---" << std::endl;
    LinkedList<int> listX;
    listX.insertAtTail(7);
    listX.insertAtTail(14);
    LinkedList<int> emptyList;

    std::cout << "List A: ";
    listX.display();
    std::cout << "List B: ";
    emptyList.display();

    std::cout << "listX.mergeSorted(emptyList)" << std::endl;
    listX.mergeSorted(emptyList);

    std::cout << "A: ";
    listX.display();
    std::cout << "B: ";
    emptyList.display();

    // Test Case 4: Unequal lengths with duplicates
    std::cout << "\n--- Test Case 4: Unequal lengths with duplicate values ---" << std::endl;
    LinkedList<int> L1;
    L1.insertAtTail(2);
    L1.insertAtTail(5);
    L1.insertAtTail(5);
    L1.insertAtTail(9);

    LinkedList<int> L2;
    L2.insertAtTail(1);
    L2.insertAtTail(5);
    L2.insertAtTail(8);
    L2.insertAtTail(12);
    L2.insertAtTail(15);

    std::cout << "List 1: ";
    L1.display();
    std::cout << "List 2: ";
    L2.display();

    L1.mergeSorted(L2);
    std::cout << "Merged List: ";
    L1.display();
    std::cout << "List 2: ";
    L2.display();

    return 0;
}
