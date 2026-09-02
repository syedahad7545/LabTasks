#pragma once
#include <iostream>

template<typename T>
class ArrayStatistics
{
private:
	T* arr;
	int size;
public:
	ArrayStatistics(T* array, int size): arr(array), size(size)
	{
		std::cout << "Vals initialized" << std::endl;
	}
	T minimum() {
		T min = arr[0];
		for (int i = 0; i < size; i++) {
			if (arr[i] < min) {
				min = arr[i];
			}
		}
		return min;
	}
	T maximum() {
		T max = arr[0];
		for (int i = 0; i < size; i++) {
			if (arr[i] > max) {
				max = arr[i];
			}
	}
		return max;
	}
	double average() {
		double avg = 0.0;
		int i;
		for (i = 0; i < size; ++i) {
			avg += arr[i];
		}
		avg = avg / size;
		return avg;
	}
	T count(T value) {
		//Not specified what is to be done in this function
		return value;
	}
	void display() {
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
};

