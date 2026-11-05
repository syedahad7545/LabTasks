#include <iostream>
using namespace std;

int sumOfDigits(int n) {
    if (n < 0) {
        return sumOfDigits(-n);
    }
    if (n == 0) {
        return 0;
    }
    return n % 10 + sumOfDigits(n / 10);
}

int main() {
    cout << "sumOfDigits(1234) -> " << sumOfDigits(1234) << endl;
    cout << "sumOfDigits(0)    -> " << sumOfDigits(0) << endl;
    cout << "sumOfDigits(-56)  -> " << sumOfDigits(-56) << endl;
}
