#include <iostream>

template <typename T>
class CircularDoublyLinkedList {
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
    CircularDoublyLinkedList() : head(nullptr) {}

    ~CircularDoublyLinkedList() {
        clear();
    }

    CircularDoublyLinkedList(const CircularDoublyLinkedList& other) : head(nullptr) {
        if (other.head == nullptr) {
            return;
        }
        Node* curr = other.head;
        do {
            insertAtEnd(curr->data);
            curr = curr->next;
        } while (curr != other.head);
    }

    CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList& other) {
        if (this != &other) {
            clear();
            if (other.head != nullptr) {
                Node* curr = other.head;
                do {
                    insertAtEnd(curr->data);
                    curr = curr->next;
                } while (curr != other.head);
            }
        }
        return *this;
    }

    void clear() {
        if (head == nullptr) {
            return;
        }
        Node* curr = head->next;
        while (curr != head) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        delete head;
        head = nullptr;
    }

    void insertAtEnd(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
            return;
        }
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }

    void display() const {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* curr = head;
        do {
            std::cout << curr->data;
            if (curr->next != head) {
                std::cout << " ";
            }
            curr = curr->next;
        } while (curr != head);
        std::cout << std::endl;
    }

    int size() const {
        if (head == nullptr) {
            return 0;
        }
        int count = 0;
        Node* curr = head;
        do {
            count++;
            curr = curr->next;
        } while (curr != head);
        return count;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void rotate(int k) {
        if (head == nullptr || head->next == head) {
            return;
        }

        int count = size();
        k = k % count;
        if (k < 0) {
            k += count;
        }

        if (k == 0) {
            return;
        }

        for (int i = 0; i < k; ++i) {
            head = head->next;
        }
    }
};

int main() {
    CircularDoublyLinkedList<int> list;
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);

    std::cout << "List (circular): ";
    list.display();

    list.rotate(2);

    std::cout << "List is now: ";
    list.display();

    return 0;
}
