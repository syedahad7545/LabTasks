#include <iostream>

template <typename T>
class CircularLinkedList {
public:
    class Node {
    public:
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

private:
    Node* head;

public:
    CircularLinkedList() : head(nullptr) {}

    ~CircularLinkedList() {
        clear();
    }

    CircularLinkedList(const CircularLinkedList& other) : head(nullptr) {
        if (other.head == nullptr) {
            return;
        }
        Node* curr = other.head;
        do {
            insertAtEnd(curr->data);
            curr = curr->next;
        } while (curr != other.head);
    }

    CircularLinkedList& operator=(const CircularLinkedList& other) {
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
            return;
        }
        Node* curr = head;
        while (curr->next != head) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->next = head;
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

    void splitInHalf(CircularLinkedList<T>& firstHalf, CircularLinkedList<T>& secondHalf) {
        firstHalf.clear();
        secondHalf.clear();

        if (head == nullptr) {
            return;
        }

        if (head->next == head) {
            firstHalf.head = head;
            head = nullptr;
            return;
        }

        Node* slow = head;
        Node* fast = head;

        while (fast->next != head && fast->next->next != head) {
            fast = fast->next->next;
            slow = slow->next;
        }

        if (fast->next->next == head) {
            fast = fast->next;
        }

        firstHalf.head = head;
        secondHalf.head = slow->next;
        fast->next = secondHalf.head;
        slow->next = firstHalf.head;

        head = nullptr;
    }
};

int main() {
    CircularLinkedList<int> list;
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);

    std::cout << "List (circular): ";
    list.display();

    CircularLinkedList<int> firstHalf;
    CircularLinkedList<int> secondHalf;

    list.splitInHalf(firstHalf, secondHalf);

    std::cout << "firstHalf: ";
    firstHalf.display();

    std::cout << "secondHalf: ";
    secondHalf.display();

    return 0;
}
