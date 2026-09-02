#ifndef dynamicArray_H
#include <iostream>

template<typename T>
class dynamicArray{
  private:
    T* data;
    int capacity;
    int currentSize;
  public:
    dynamicArray(int capacity): capacity(capacity), currentSize(0){
      data = new T[capacity];
    }
    dynamicArray(const dynamicArray& obj){
      this->capacity = obj.capacity;
      this->currentSize = obj.currentSize;
      this-> data = new T[capacity];
      for (int i = 0; i < currentSize; ++i) {
        this->data[i] = obj.data[i];
      }
    }
    
    void insert(T num){
      if(currentSize >= capacity){
        std::cout << "The array is full. I am doubling the capacity" << std::endl;

        capacity *= 2;
        T* temp_data = new T[capacity];
        for (int i = 0; i < currentSize; ++i) {
          temp_data[i] = data[i];
        }
        delete data;
        data = temp_data;
        temp_data = nullptr;
      }

      data[currentSize] = num;
      currentSize++;
    }

    T get(int pos){
      if(pos >= currentSize || pos < 0){ // I am assuming idx starting from zero from the user
        std::cerr << "You are accessing out of bounds" << std::endl;
      }
      return data[pos];
    }

    void set(T num, int pos){
      if(pos >= currentSize || pos < 0){ // I am assuming idx starting from zero from the user
        std::cerr << "You are accessing out of bounds" << std::endl;
      }
      data[pos] = num;
    }

    int size(){
      return currentSize;
    }

    void display(){
      for (int i = 0; i < currentSize; ++i) {
        std::cout << data[i] << " ";
      }
      std::cout << std::endl;
    }

    void removeAt(int pos){
      if(pos >= currentSize || pos < 0){ // I am assuming idx starting from zero from the user
        std::cerr << "You are accessing out of bounds" << std::endl;
      }

      for(int i = pos; i < currentSize - 1; ++i){
        data[i] = data[i + 1];
      }

      currentSize--;
    }

    ~dynamicArray(){
      delete data;
      data = nullptr;
    }
};
#endif // !dynamicArray_H
