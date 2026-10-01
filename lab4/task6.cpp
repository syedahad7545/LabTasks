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
bool equalLists(
    typename DoublyLinkedList<T>::Iterator begin1,
    typename DoublyLinkedList<T>::Iterator end1,
    typename DoublyLinkedList<T>::Iterator begin2,
    typename DoublyLinkedList<T>::Iterator end2
) {
    auto it1 = begin1;
    auto it2 = begin2;

    while (it1 != end1 && it2 != end2) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }

    return (it1 == end1 && it2 == end2);
}

int main() {
    DoublyLinkedList<int> a1;
    a1.insertAtTail(1);
    a1.insertAtTail(2);
    a1.insertAtTail(3);

    DoublyLinkedList<int> b1;
    b1.insertAtTail(1);
    b1.insertAtTail(2);
    b1.insertAtTail(3);

    std::cout << "List A: ";
    a1.display();
    std::cout << "List B: ";
    b1.display();
    std::cout << "equalLists: " << std::boolalpha << equalLists<int>(a1.begin(), a1.end(), b1.begin(), b1.end()) << std::endl;

    DoublyLinkedList<int> a2;
    a2.insertAtTail(1);
    a2.insertAtTail(2);
    a2.insertAtTail(3);

    DoublyLinkedList<int> b2;
    b2.insertAtTail(1);
    b2.insertAtTail(2);
    b2.insertAtTail(4);

    std::cout << "List A: ";
    a2.display();
    std::cout << "List B: ";
    b2.display();
    std::cout << "equalLists: " << std::boolalpha << equalLists<int>(a2.begin(), a2.end(), b2.begin(), b2.end()) << std::endl;

    DoublyLinkedList<int> a3;
    a3.insertAtTail(1);
    a3.insertAtTail(2);
    a3.insertAtTail(3);

    DoublyLinkedList<int> b3;
    b3.insertAtTail(1);
    b3.insertAtTail(2);

    std::cout << "List A: ";
    a3.display();
    std::cout << "List B: ";
    b3.display();
    std::cout << "equalLists: " << std::boolalpha << equalLists<int>(a3.begin(), a3.end(), b3.begin(), b3.end()) << std::endl;

    return 0;
}
