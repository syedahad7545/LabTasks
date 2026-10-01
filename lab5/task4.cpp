#include <iostream>
using namespace std;

template <typename T>
class CircularArrayQueue {
private:
    T* arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    CircularArrayQueue(int capacity) : capacity(capacity), front(0), rear(0), count(0) {
        arr = new T[capacity];
    }

    void enqueue(T value) {
        if (isFull()) {
            return;
        }
        arr[rear] = value;
        rear = (rear + 1) % capacity;
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }
        front = (front + 1) % capacity;
        count--;
    }

    T frontElement() {
        if (isEmpty()) {
            return T();
        }
        return arr[front];
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    int size() {
        return count;
    }

    ~CircularArrayQueue() {
        delete[] arr;
    }
};

int main() {
    CircularArrayQueue<int> q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << q.isFull() << endl;
    q.dequeue();
    cout << q.isFull() << endl;
    q.enqueue(4);
    cout << q.frontElement() << endl;
    cout << q.isFull() << endl;
    return 0;
}
