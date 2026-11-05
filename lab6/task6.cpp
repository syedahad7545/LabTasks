#include <iostream>
using namespace std;

int arraySum(int arr[], int n) {
    if (n == 1) {
        return arr[0];
    }
    return arr[n - 1] + arraySum(arr, n - 1);
}

int arrayMin(int arr[], int n) {
    if (n == 1) {
        return arr[0];
    }
    int restMin = arrayMin(arr, n - 1);
    return arr[n - 1] < restMin ? arr[n - 1] : restMin;
}

int arrayMax(int arr[], int n) {
    if (n == 1) {
        return arr[0];
    }
    int restMax = arrayMax(arr, n - 1);
    return arr[n - 1] > restMax ? arr[n - 1] : restMax;
}

int main() {
    int arr[] = {8, 3, 12, 5, 1, 9};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "arraySum(arr, 6) -> " << arraySum(arr, n) << endl;
    cout << "arrayMin(arr, 6) -> " << arrayMin(arr, n) << endl;
    cout << "arrayMax(arr, 6) -> " << arrayMax(arr, n) << endl;
    return 0;
}
