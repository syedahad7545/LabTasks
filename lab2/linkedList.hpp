#ifndef LINKEDLIST_H
#include <iostream>
class linkedList{
  private:
    class Node{
      public:
        int data;
        Node* next;

        Node(){}
        Node(int val){
          data = val;
          next = nullptr;
        }
    }; //the class ends here
    Node head;
    int size;

  public:
    linkedList():size(0){
      head.next = nullptr;
    }

    void insertAtHead(int val){
      Node* node = new Node(val);
      node->next = head.next;
      head.next = node;
      size++;
    }

    void insertAtTail(int val){ 
      Node* node = new Node(val);

      Node* ptr = &(head);
      for(;ptr->next != nullptr;){
        ptr = ptr->next; 
      }
      node->next = ptr->next; //This is always nullptr
      ptr->next = node;
      size++;
    }

    int Size(){
      return size;
    }

    void Display(){
      Node* ptr = head.next;
      for(int i = 0; i < size; ++i){
        std::cout << ptr->data << " ";
        ptr = ptr->next; 
      }
      std::cout << std::endl;
    }

    bool isEmpty(){
      if(size == 0)
        return true;
      else
        return false;
    }

    Node* findMiddle(){
      int idx = (size / 2) + 1;

      Node* middle = head.next;
      int i;
      for(i = 0; i < idx - 1; ++i){ //It is already pointing on the first element that's why we did idx - 1
        middle = middle->next;
      }
      return middle;
    }
    Node* findNthFromEnd(int k){
      int idx = size - k;
      if(idx < 0){
        std::cout << "No elements in the list try again later" << std::endl;
        std::abort();
      }
      Node* ptr = &head;
      for(int i =0; i <= idx; ++i){
       ptr = ptr->next; 
      }
      return ptr;
    }
    bool hasCycle(){
      Node* ptr = &head;
      for(int i = 0; i < size; ++i){
        ptr = ptr->next;
      }
      bool flag;
      if(ptr->next){ //existence of nullptr
        flag = true;
      }else{
        flag = false;
      }
      return flag;
    }
    void NodeDeletion(int val){
      if(size == 0){
        std::cout << "Size of the array is zero. No element can be deleted" << std::endl;
        return;
      }
      //Two tasks:
      //1- find that the element exist or not
      //2- if exist then have the address of it and of the previous node
      bool flag = true;
      Node* node = &head;
      Node* prevNode = &head;
      for(int i = 0; i < size; ++i){
        if(node->data != val){
          prevNode = node;
          node = node->next;
        }else{
          flag = false;
          break;
        }
      }
      if(flag){
        std::cout << "The element is not found in the list" << std::endl;
        return;
      }
      prevNode->next = node->next; //The new link
      delete node;  // deleting the removed link
      size--;
    }
};

#endif // !LINKEDLIST_H
