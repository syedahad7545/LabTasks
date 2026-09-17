#include "linkedList.hpp"

int main(){
  linkedList obj;

  //obj.insertAtHead(70);
  //obj.insertAtHead(60);
  //obj.insertAtHead(50);
  obj.insertAtHead(40);
  obj.insertAtHead(30);
  obj.insertAtHead(20);
  obj.insertAtHead(10);

  //obj.Display();
  obj.NodeDeletion(30);
  obj.Display();
  return 0;
}
