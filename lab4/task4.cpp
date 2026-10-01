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

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node = nullptr) : current(node) {}

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        Iterator& operator--() {
            if (current != nullptr) {
                current = current->prev;
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Node* node() const {
            return current;
        }
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

    void deleteAtHead() {
        if (head == nullptr) {
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
    }

    void deleteAtTail() {
        if (head == nullptr) {
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

    void deleteNode(Node* nodeToDelete) {
        if (nodeToDelete == nullptr) {
            return;
        }
        if (nodeToDelete == head) {
            head = nodeToDelete->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else {
            nodeToDelete->prev->next = nodeToDelete->next;
            if (nodeToDelete->next != nullptr) {
                nodeToDelete->next->prev = nodeToDelete->prev;
            }
        }
        delete nodeToDelete;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
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

template <typename T>
DoublyLinkedList<T> differenceList(
    typename DoublyLinkedList<T>::Iterator begin1,
    typename DoublyLinkedList<T>::Iterator end1,
    typename DoublyLinkedList<T>::Iterator begin2,
    typename DoublyLinkedList<T>::Iterator end2
) {
    DoublyLinkedList<T> result;
    auto it1 = begin1;
    auto it2 = begin2;

    while (it1 != end1 && it2 != end2) {
        if (*it1 < *it2) {
            result.insertAtTail(*it1);
            ++it1;
        } else if (*it2 < *it1) {
            ++it2;
        } else {
            ++it1;
        }
    }

    while (it1 != end1) {
        result.insertAtTail(*it1);
        ++it1;
    }

    return result;
}

int main() {
    DoublyLinkedList<int> listA;
    listA.insertAtTail(1);
    listA.insertAtTail(2);
    listA.insertAtTail(3);
    listA.insertAtTail(4);
    listA.insertAtTail(5);

    DoublyLinkedList<int> listB;
    listB.insertAtTail(2);
    listB.insertAtTail(4);
    listB.insertAtTail(6);

    std::cout << "List A: ";
    listA.display();

    std::cout << "List B: ";
    listB.display();

    DoublyLinkedList<int> result = differenceList<int>(listA.begin(), listA.end(), listB.begin(), listB.end());

    std::cout << "Result (A - B): ";
    result.display();

    return 0;
}
