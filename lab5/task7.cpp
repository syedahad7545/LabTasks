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

struct Process {
    int id;
    int remaining;
};

void roundRobin(int processIDs[], int burstTimes[], int n, int quantum) {
    LinkedQueue<Process> q;
    for (int i = 0; i < n; i++) {
        q.enqueue({processIDs[i], burstTimes[i]});
    }
    int time = 0;
    while (!q.isEmpty()) {
        Process p = q.frontElement();
        q.dequeue();
        int run = p.remaining < quantum ? p.remaining : quantum;
        time += run;
        p.remaining -= run;
        if (p.remaining > 0) {
            q.enqueue(p);
        } else {
            cout << "P" << p.id << " completes at t=" << time << endl;
        }
    }
}

int main() {
    int processIDs[] = {1, 2, 3};
    int burstTimes[] = {5, 3, 1};
    roundRobin(processIDs, burstTimes, 3, 2);
    return 0;
}
