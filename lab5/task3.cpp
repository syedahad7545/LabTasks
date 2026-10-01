#include <iostream>
using namespace std;

template <typename T>
class ArrayQueue {
private:
    T* arr;
    int capacity;
    int front;
    int rear;

public:
    ArrayQueue(int capacity) : capacity(capacity), front(0), rear(0) {
        arr = new T[capacity];
    }

    void enqueue(T value) {
        if (isFull()) {
            return;
        }
        arr[rear++] = value;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }
        front++;
    }

    T frontElement() {
        if (isEmpty()) {
            return T();
        }
        return arr[front];
    }

    bool isEmpty() {
        return front == rear;
    }

    bool isFull() {
        return rear == capacity;
    }

    int size() {
        return rear - front;
    }

    ~ArrayQueue() {
        delete[] arr;
    }
};

int main() {
    ArrayQueue<int> q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.dequeue();
    q.dequeue();
    q.enqueue(4);
    q.enqueue(5);
    cout << q.size() << endl;
    q.enqueue(6);
    cout << q.isFull() << endl;
    cout << q.size() << endl;
    return 0;
}
