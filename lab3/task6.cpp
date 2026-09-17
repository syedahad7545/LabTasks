#include <iostream>

/**
 * Task 6: Delete a Given Node
 *
 * Deletes a specific node from a doubly linked list given only a direct pointer to that node.
 *
 * Time Complexity: O(1) - Unlinks and frees the node directly using its own prev and next pointers.
 *                         No traversal from head is performed.
 * Space Complexity: O(1) - In-place pointer manipulation with no extra space.
 *
 * Restrictions followed:
 * - Does not traverse from head to locate nodeToDelete.
 * - Handles deletion of head node correctly.
 * - Handles deletion of tail node correctly.
 * - Handles deletion of middle node correctly.
 * - Clearly states time complexity in comments.
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
    DoublyLinkedList() : head(nullptr) {}

    ~DoublyLinkedList() {
        clear();
    }

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr) {
        Node* curr = other.head;
        while (curr != nullptr) {
            insertAtTail(curr->data);
            curr = curr->next;
        }
    }

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

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

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

    /**
     * Helper to find a node by value so its pointer can be passed to deleteNode().
     * (Simulates having a pointer to a specific node as described in the task).
     */
    Node* findNode(T value) const {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == value) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    /**
     * Deletes a given node in O(1) time without traversing the list.
     *
     * Time Complexity:  O(1) - Modifies neighboring pointers directly.
     * Space Complexity: O(1) - Constant auxiliary space.
     */
    void deleteNode(Node* nodeToDelete) {
        if (nodeToDelete == nullptr) {
            return;
        }

        // Case 1: The node to delete is the head of the list
        if (nodeToDelete == head) {
            head = nodeToDelete->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else {
            // Case 2: The node is in the middle or at the tail
            // Connect previous node to next node
            nodeToDelete->prev->next = nodeToDelete->next;

            // If it is not the tail, connect next node back to previous node
            if (nodeToDelete->next != nullptr) {
                nodeToDelete->next->prev = nodeToDelete->prev;
            }
        }

        // Free the memory of the target node
        delete nodeToDelete;
    }

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

    void displayReverse() const {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        while (curr != nullptr) {
            std::cout << curr->data;
            if (curr->prev != nullptr) {
                std::cout << " ";
            }
            curr = curr->prev;
        }
        std::cout << std::endl;
    }
};

int main() {
    std::cout << "================ Task 6: Delete a Given Node (O(1)) ================" << std::endl;

    DoublyLinkedList<int> list;
    list.insertAtTail(100);
    list.insertAtTail(200);
    list.insertAtTail(300);
    list.insertAtTail(400);
    list.insertAtTail(500);

    // Initial list display
    std::cout << "\nInitial List: ";
    list.display();

    // 1. Manual Example: Deleting middle node (300)
    std::cout << "\n--- Step 1: Deleting middle node (300) in O(1) ---" << std::endl;
    DoublyLinkedList<int>::Node* node300 = list.findNode(300);
    if (node300 != nullptr) {
        list.deleteNode(node300);
    }
    std::cout << "display() -> ";
    list.display();
    std::cout << "displayReverse() -> ";
    list.displayReverse();

    // 2. Deleting head node (100)
    std::cout << "\n--- Step 2: Deleting head node (100) in O(1) ---" << std::endl;
    DoublyLinkedList<int>::Node* node100 = list.findNode(100);
    if (node100 != nullptr) {
        list.deleteNode(node100);
    }
    std::cout << "display() -> ";
    list.display();
    std::cout << "displayReverse() -> ";
    list.displayReverse();

    // 3. Deleting tail node (500)
    std::cout << "\n--- Step 3: Deleting tail node (500) in O(1) ---" << std::endl;
    DoublyLinkedList<int>::Node* node500 = list.findNode(500);
    if (node500 != nullptr) {
        list.deleteNode(node500);
    }
    std::cout << "display() -> ";
    list.display();
    std::cout << "displayReverse() -> ";
    list.displayReverse();

    // 4. Deleting remaining nodes until empty
    std::cout << "\n--- Step 4: Deleting remaining nodes (200, 400) ---" << std::endl;
    DoublyLinkedList<int>::Node* node200 = list.findNode(200);
    list.deleteNode(node200);
    std::cout << "After deleting 200: ";
    list.display();

    DoublyLinkedList<int>::Node* node400 = list.findNode(400);
    list.deleteNode(node400);
    std::cout << "After deleting 400 (only remaining node): ";
    list.display();

    return 0;
}
