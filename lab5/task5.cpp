#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue {
public:
    class Node {
    public:
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

private:
    Node* front;
    Node* rear;
    int count;

public:
    LinkedQueue() : front(nullptr), rear(nullptr), count(0) {}

    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        count--;
    }

    T frontElement() {
        if (isEmpty()) {
            return T();
        }
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int size() {
        return count;
    }

    ~LinkedQueue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    LinkedQueue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.dequeue();
    cout << q.frontElement() << endl;
    cout << q.size() << endl;
    return 0;
}
