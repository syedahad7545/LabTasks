#include <iostream>
using namespace std;

template <typename T>
class ArrayStack {
private:
    T* arr;
    int capacity;
    int top;

public:
    ArrayStack(int capacity) : capacity(capacity), top(-1) {
        arr = new T[capacity];
    }

    void push(T value) {
        if (isFull()) {
            return;
        }
        arr[++top] = value;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        top--;
    }

    T topElement() {
        if (isEmpty()) {
            return T();
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    int size() {
        return top + 1;
    }

    ~ArrayStack() {
        delete[] arr;
    }
};

int main() {
    ArrayStack<int> s(3);
    s.push(10);
    s.push(20);
    s.push(30);
    cout << s.isFull() << endl;
    cout << s.topElement() << endl;
    s.push(40);
    s.pop();
    cout << s.topElement() << endl;
    cout << s.size() << endl;
    return 0;
}
