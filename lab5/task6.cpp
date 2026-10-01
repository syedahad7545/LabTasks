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

struct Customer {
    int id;
    int arrival;
    int service;
};

void simulateTicketCounter(int arrivalTimes[], int serviceTimes[], int n) {
    LinkedQueue<Customer> q;
    for (int i = 0; i < n; i++) {
        q.enqueue({i + 1, arrivalTimes[i], serviceTimes[i]});
    }
    int time = 0;
    double totalWait = 0;
    while (!q.isEmpty()) {
        Customer c = q.frontElement();
        q.dequeue();
        int start = time > c.arrival ? time : c.arrival;
        int finish = start + c.service;
        int wait = start - c.arrival;
        totalWait += wait;
        time = finish;
        cout << "Customer " << c.id << ": arrives " << c.arrival << ", starts " << start
             << ", finishes " << finish << ", wait " << wait << endl;
    }
    if (n > 0) {
        cout << "Average wait: " << totalWait / n << endl;
    }
}

int main() {
    int arrivalTimes[] = {0, 1, 2};
    int serviceTimes[] = {4, 2, 1};
    simulateTicketCounter(arrivalTimes, serviceTimes, 3);
    return 0;
}
