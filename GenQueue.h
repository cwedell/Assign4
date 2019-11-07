#include "GenDoublyLinkedList.h"
#include <iostream>

using namespace std;

template <class T>
class GenQueue {
private:
  int head;
  int tail;
  int numElements;

  GenDoublyLinkedList<T> myList = GenDoublyLinkedList<T>();

public:
  GenQueue();
  ~GenQueue();

  void insert(T data);
  T remove();
  T peek();
  int getSize();

  bool isEmpty();
};

template <class T>
GenQueue<T>::GenQueue() {
  head = 0;
  tail = -1;
  numElements = 0;
}

template <class T>
GenQueue<T>::~GenQueue() {
}

template <class T>
void GenQueue<T>::insert(T data) {
  myList.insertBack(data);
  ++tail;
  ++numElements;
}

template <class T>
T GenQueue<T>::remove() {
  --numElements;
  return myList.removeFront();
}

template <class T>
T GenQueue<T>::peek() {
  T temp = myList.removeFront();
  myList.insertFront(temp);
  return temp;
}

template <class T>
int GenQueue<T>::getSize() {
  return numElements;
}

template <class T>
bool GenQueue<T>::isEmpty() {
  return (numElements == 0);
}
