#include <iostream>
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
     * Checks whether the doubly linked list reads the same forwards and backwards.
     *
     * Time Complexity:  O(n) - O(n) to find the tail and O(n/2) comparisons.
     * Space Complexity: O(1) - Only two pointers used for inward traversal.
     */
    bool isPalindrome() const {
        // Required Behaviour: Empty list and single-node list are palindromes
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        // Pointer starting at the front
        Node* left = head;

        // Pointer starting at the tail
        Node* right = head;
        while (right->next != nullptr) {
            right = right->next;
        }

        // Walk inward from both ends:
        // - For odd-length lists: terminates when left and right meet at the same node (left == right)
        // - For even-length lists: terminates when left and right cross each other (left->prev == right)
        while (left != right && left->prev != right) {
            if (left->data != right->data) {
                return false;
            }
            left = left->next;
            right = right->prev;
        }

        return true;
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
};

int main() {

    DoublyLinkedList<int> list1;
    list1.insertAtTail(1);
    list1.insertAtTail(2);
    list1.insertAtTail(3);
    list1.insertAtTail(2);
    list1.insertAtTail(1);

    std::cout << "List: ";
    list1.display();
    std::cout << "isPalindrome(): " << (list1.isPalindrome() ? "true" : "false") << std::endl;


    return 0;
}
