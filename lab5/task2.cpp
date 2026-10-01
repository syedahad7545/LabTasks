#include <iostream>
using namespace std;

template <typename T>
class LinkedStack {
public:
    class Node {
    public:
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

private:
    Node* top;
    int count;

public:
    LinkedStack() : top(nullptr), count(0) {}

    void push(T value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        count++;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    T topElement() {
        if (isEmpty()) {
            return T();
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int size() {
        return count;
    }

    ~LinkedStack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int main() {
    LinkedStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.pop();
    cout << s.topElement() << endl;
    cout << s.size() << endl;
    return 0;
}
