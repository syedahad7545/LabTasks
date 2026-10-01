#include <iostream>
#include <string>
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

bool evaluatePostfix(const string& expression, int& result) {
    LinkedStack<int> s;
    int i = 0;
    int n = expression.size();
    while (i < n) {
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        string token = "";
        while (i < n && expression[i] != ' ') {
            token += expression[i];
            i++;
        }
        if (token[0] >= '0' && token[0] <= '9') {
            int value = 0;
            for (char ch : token) {
                if (ch < '0' || ch > '9') {
                    return false;
                }
                value = value * 10 + (ch - '0');
            }
            s.push(value);
        } else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            if (s.size() < 2) {
                return false;
            }
            int b = s.topElement();
            s.pop();
            int a = s.topElement();
            s.pop();
            if (token[0] == '+') {
                s.push(a + b);
            } else if (token[0] == '-') {
                s.push(a - b);
            } else if (token[0] == '*') {
                s.push(a * b);
            } else {
                if (b == 0) {
                    return false;
                }
                s.push(a / b);
            }
        } else {
            return false;
        }
    }
    if (s.size() != 1) {
        return false;
    }
    result = s.topElement();
    return true;
}

int main() {
    string expressions[] = {"5 1 2 + 4 * + 3 -", "8 3 -", "2 +", "4 0 /", "1 2", "3 a +"};
    for (const string& e : expressions) {
        int result;
        if (evaluatePostfix(e, result)) {
            cout << result << endl;
        } else {
            cout << "Invalid" << endl;
        }
    }
    return 0;
}
