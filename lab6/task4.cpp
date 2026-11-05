#include <iostream>
using namespace std;

// TOH(A, B, C, n): move n disks from peg A to peg B using peg C as helper
void TOH(char A, char B, char C, int n) {
  // base case: a single disk moves directly from A to B
  if (n == 1) {
    cout << "Move disk 1 from " << A << " to " << B << endl;
    return;
  }
  // recursive case
  // move top n-1 disks from A to C, using B as helper
  TOH(A, C, B, n - 1);
  // move the largest disk from A to B
  cout << "Move disk " << n << " from " << A << " to " << B << endl;
  // move the n-1 disks from C to B, using A as helper
  TOH(C, B, A, n - 1);
}

// lab signature: source -> destination, with auxiliary as helper
void towerOfHanoi(int n, char source, char auxiliary, char destination) {
  TOH(source, destination, auxiliary, n);
}

int main() {
  cout << "towerOfHanoi(3, 'A', 'B', 'C')" << endl;
  towerOfHanoi(3, 'A', 'B', 'C');

  cout << "\nTOH('A', 'B', 'C', 3)  (example from the video)" << endl;
  TOH('A', 'B', 'C', 3);

  int n;
  cout << "\nEnter number of disks: ";
  cin >> n;
  if (n <= 0) {
    cout << "Number of disks must be positive." << endl;
    return 0;
  }
  towerOfHanoi(n, 'A', 'B', 'C');
  cout << "Total moves: " << (1 << n) - 1 << endl;
  return 0;
}
