#include <iostream>

template <typename T> class LinkedList {
private:
  class Node {
  public:
    T data;
    Node *next;

    Node(T value) : data(value), next(nullptr) {}
  };

  Node *head;

public:
  LinkedList() : head(nullptr) {}

  ~LinkedList() { clear(); }

  LinkedList(const LinkedList &other) : head(nullptr) {
    Node *curr = other.head;
    while (curr != nullptr) {
      insertAtTail(curr->data);
      curr = curr->next;
    }
  }

  LinkedList &operator=(const LinkedList &other) {
    if (this != &other) {
      clear();
      Node *curr = other.head;
      while (curr != nullptr) {
        insertAtTail(curr->data);
        curr = curr->next;
      }
    }
    return *this;
  }

  void clear() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void insertAtTail(T value) {
    Node *newNode = new Node(value);
    if (head == nullptr) {
      head = newNode;
      return;
    }
    Node *curr = head;
    while (curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = newNode;
  }

  void reverse() {
    Node *prev = nullptr;
    Node *curr = head;
    Node *nextNode = nullptr;

    while (curr != nullptr) {
      nextNode = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nextNode;
    }

    head = prev;
  }

  void display() const {
    if (head == nullptr) {
      std::cout << "List is empty." << std::endl;
      return;
    }
    Node *curr = head;
    while (curr != nullptr) {
      std::cout << curr->data;
      if (curr->next != nullptr) {
        std::cout << " ";
      }
      curr = curr->next;
    }
    std::cout << std::endl;
  }

  bool isEmpty() const { return head == nullptr; }
};

int main() { return 0; }
