#include <iostream>
#include "task3.h"
#include "ArrayStatistics.h"
#include "dynamicArray.h"

void swap(int& a, int& b) {
  int c = a;
  a = b;
  b = c;
}
void inputArray(int* arr, int size) {
  std::cout << "Array: ";
  for (int i = 0; i < size; ++i) {
    std::cin >> arr[i];
  }
}
void displayArray(int* arr, int size) {
  for (int i = 0; i < size; i++)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}
int findMinimum(int* arr, int size) {
  int min = arr[0];
  for (int i = 0; i < size; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  return min;
}
int findMaximum(int* arr, int size) {
  int max = arr[0];
  for (int i = 0; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}
int calculateSum(int* arr, int size) {
  int sum = 0;

  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}
int countEven(int* arr, int size) {
  int count = 0;
  for (int i = 0; i < size; ++i) {
    if (arr[i] % 2 == 0) {
      count++;
    }
  }
  return count;
}
void reverseArray(int* arr, int size) {
  int idx = size / 2;
  for (int i = 0; i < idx; i++)
  {
    swap(arr[i], arr[(size - 1 - i)]);
  }
}

int main() {
  std::cout << "Enter the question you want to test: ";
  int choice;
  std::cin >> choice;

  switch(choice){
    case 1:{
             std::cout << "Size: ";
             int size;
             std::cin >> size;

             int* array = new int[size];
             inputArray(array, size);

             std::cout << "Max: " << findMaximum(array, size) << std::endl;
             std::cout << "Min: "<<findMinimum(array, size) << std::endl;
             std::cout << "Sum: " << calculateSum(array, size) << std::endl;
             std::cout << "Even: " << countEven(array, size) << std::endl;
             reverseArray(array,  size);
             displayArray(array, size);
             break;
           }
    case 2:{

             //This code logic isn't complete and correct
             std::cout << "Size: ";
             int size;
             std::cin >> size;

             int* array = new int[size];
             inputArray(array, size);

             std::cout << "Enter the target value: ";
             int T;
             std::cin >> T;

             int pair1;
             int pair2;

             for (int i = 0; i < size; i++)
             {
               int pair1 = array[i];
               for (int j = j; j < size; j++)
               {
                 if (pair1 + array[j] == T) {
                   pair2 = array[j];
                   break;
                 }
               }
             }
             break;
           }
    case 3:{
             int numbers[] = {10, 20, 5, 15};
             double values[] = {2.5, 8.4, 1.2, 6.7};
             char letters[] = {'D', 'A', 'C', 'B'};

             std::cout << "Max: " <<  findMaximum(numbers, 4) << std::endl;
             std::cout <<  "Min: " << findMinimum(numbers, 4) << std::endl;
             reverseArray(numbers, 4);
             displayArray(numbers, 4);
             std::cout << std::endl;
             std::cout << "Max: " <<  findMaximum(values, 4) << std::endl;
             std::cout <<  "Min: " << findMinimum(values, 4) << std::endl;
             reverseArray(values, 4);
             displayArray(values, 4);
             std::cout << std::endl;
             std::cout << "Max: " <<  findMaximum(letters, 4) << std::endl;
             std::cout <<  "Min: " << findMinimum(letters, 4) << std::endl;
             reverseArray(letters, 4);
             displayArray(letters, 4);
             break;
           }
    case 4:{
             dynamicArray<float> obj1(10);
             obj1.insert(1);
             obj1.insert(2);
             obj1.insert(3);
             obj1.insert(4);
             obj1.insert(5);
             obj1.insert(6);
             obj1.insert(7);
             obj1.insert(8);
             obj1.insert(9);
             obj1.insert(10);
             std::cout <<"The size right after initializing the object with 10 numbers: "<< obj1.size() << std::endl;
             obj1.display();

             obj1.removeAt(3);
             std::cout <<"The size right after removing element at index 3: "<< obj1.size() << std::endl;
             obj1.display();

             obj1.set(99, 8);
             std::cout << "The array after Setting the number at position 8 to 99: ";
             obj1.display();

             std::cout << "Now I am going to insert 4 more elements to this array" << std::endl;
             obj1.insert(1000);
             obj1.insert(1000);
             obj1.insert(1000);
             obj1.insert(1000);
             std::cout <<"The size right after inserting 4 elements in the array: "<< obj1.size() << std::endl;
             obj1.display();

             std::cout << "Deep copy performed: ";
             dynamicArray obj2 = obj1;
             obj2.display();
             break;
           }
    case 5:{
             int size = 5;
             int intArr[] = { 1,2,3,4,5 };
             double doubleArr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
             ArrayStatistics<int> intStats(intArr, size);
             ArrayStatistics<double> doubleStats(doubleArr, size);

             std::cout << intStats.minimum() << std::endl;
             std::cout << intStats.maximum() << std::endl;
             std::cout << intStats.count(4) << std::endl;
             std::cout << intStats.average() << std::endl;
             intStats.display();

             std::cout << doubleStats.minimum() << std::endl;
             std::cout << doubleStats.maximum() << std::endl;
             std::cout << doubleStats.count(4) << std::endl;
             std::cout << doubleStats.average() << std::endl;
             intStats.display();
             break;
           }
    default:
           std::cout << "You entered the wrong choice try again. We only have 5 questions right now!!!!!!" << std::endl;
  }

}


