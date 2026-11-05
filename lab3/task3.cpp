#include <iostream>

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
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    LinkedList(const LinkedList& other) : head(nullptr) {
        Node* curr = other.head;
        while (curr != nullptr) {
            insertAtTail(curr->data);
            curr = curr->next;
        }
    }

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

    void mergeSorted(LinkedList<T>& other) {
        if (this == &other) {
            return;
        }

        if (other.head == nullptr) {
            return;
        }

        if (this->head == nullptr) {
            this->head = other.head;
            other.head = nullptr;
            return;
        }

        Node* p1 = this->head;
        Node* p2 = other.head;
        Node* newHead = nullptr;
        Node* tail = nullptr;

        if (p1->data <= p2->data) {
            newHead = p1;
            p1 = p1->next;
        } else {
            newHead = p2;
            p2 = p2->next;
        }
        tail = newHead;

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

        if (p1 != nullptr) {
            tail->next = p1;
        } else {
            tail->next = p2;
        }

        this->head = newHead;
        other.head = nullptr; 
    }

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
    
}
