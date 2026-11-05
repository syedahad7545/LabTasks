#include <iostream>
using namespace std;

long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    cout << "fibonacci(0)  -> " << fibonacci(0) << endl;
    cout << "fibonacci(1)  -> " << fibonacci(1) << endl;
    cout << "fibonacci(10) -> " << fibonacci(10) << endl;

    return 0;
}
