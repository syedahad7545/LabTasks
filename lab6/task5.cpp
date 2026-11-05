#include <iostream>
using namespace std;

template <typename T> class LinkedList {
private:
  class Node {
  public:
    T data;
    Node *next;

    Node(T value) : data(value), next(nullptr) {}
  };

  Node *head;

public: LinkedList() : head(nullptr) {}
  ~LinkedList() {
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
    while (curr != nullptr) {
      Node *nextNode = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nextNode;
    }
    head = prev;
  }
  void reverseHelper(Node *curr, Node *&prev, Node *next) {
    if (curr == nullptr) {
      return;
    }
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
    reverseHelper(curr, prev, next);
  }
  void reverseRecursive() {
    Node *curr = head;
    Node *prev = nullptr;
    Node *next = nullptr;
    reverseHelper(curr, prev, next);
    head = prev;
  }

  void display() {
    if (head == nullptr) {
      cout << "List is empty." << endl;
      return;
    }
    Node *curr = head;
    while (curr != nullptr) {
      cout << curr->data << " ";
      curr = curr->next;
    }
    cout << endl;
  }
};

int main() {
  LinkedList<int> list;
  list.insertAtTail(10);
  list.insertAtTail(20);
  list.insertAtTail(30);
  list.insertAtTail(40);
  list.insertAtTail(50);

  cout << "Before: ";
  list.display();
  list.reverseRecursive();
  cout << "After: ";
  list.display();

  // LinkedList<int> empty;
  // empty.reverseRecursive();
  // cout << "Empty list after reverseRecursive: ";
  // empty.display();

  // LinkedList<int> single;
  // single.insertAtTail(5);
  // single.reverseRecursive();
  // cout << "Single node list after reverseRecursive: ";
  // single.display();
  return 0;
}
