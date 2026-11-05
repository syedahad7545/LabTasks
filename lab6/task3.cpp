#include <iostream>
using namespace std;

int recursiveBinarySearch(int arr[], int low, int high, int target) {
    if (low > high) {
        return -1;
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) {
        return mid;
    }
    if (target < arr[mid]) {
        return recursiveBinarySearch(arr, low, mid - 1, target);
    }
    return recursiveBinarySearch(arr, mid + 1, high, target);
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = 6;

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "recursiveBinarySearch(arr, 0, 5, 7) -> " << recursiveBinarySearch(arr, 0, n - 1, 7) << endl;
    cout << "recursiveBinarySearch(arr, 0, 5, 4) -> " << recursiveBinarySearch(arr, 0, n - 1, 4) << endl;
    cout << "recursiveBinarySearch(arr, 0, 5, 1) -> " << recursiveBinarySearch(arr, 0, n - 1, 1) << endl;
    cout << "recursiveBinarySearch(arr, 0, 5, 11) -> " << recursiveBinarySearch(arr, 0, n - 1, 11) << endl;
    return 0;
}
