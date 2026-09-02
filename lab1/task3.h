#pragma once
#include <iostream>
template <typename T>
void swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}

template <typename T>
void displayArray(T* arr, int size) {
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
		std::cout << std::endl;

}
template <typename T>
T findMaximum(T* arr, int size) {
	T max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
template <typename T>
T findMinimum(T* arr, int size) {

	T min = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	return min;

}
template <typename T>
void reverseArray(T* arr, int size) {
	int idx = size / 2;
	for (int i = 0; i < idx; i++)
	{
		swap(arr[i], arr[(size - 1 - i)]);
	}

}
