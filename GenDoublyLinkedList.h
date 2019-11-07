#include "ListNode.h"
#include <iostream>

using namespace std;

template <class T>
class GenDoublyLinkedList {
private:
  ListNode<T> *front = new ListNode<T>();
  ListNode<T> *back = new ListNode<T>();
  unsigned int size;
public:
  GenDoublyLinkedList();
  ~GenDoublyLinkedList();

  void insertFront(T d);
  void insertBack(T d);
  T removeFront();
  T removeBack();
  void insertPos(T d, int p);
  ListNode<T>* remove(T d);
  int find(T d);

  bool isEmpty();
  void printList();
  unsigned int getSize();
};

template <class T>
GenDoublyLinkedList<T>::GenDoublyLinkedList() {
  front = NULL;
  back = NULL;
  size = 0;
}

template <class T>
GenDoublyLinkedList<T>::~GenDoublyLinkedList() {
  while(!isEmpty()) {
    ListNode<T> *current = front;
    while(current != NULL) {
      if(current == back) {
        delete back;
      } else {
        current = current->next;
        delete current->prev;
      }
    }
  }
}

template <class T>
void GenDoublyLinkedList<T>::insertFront(T d) {
  ListNode<T> *node = ListNode<T>(d);
  if(isEmpty()) {
    back = node;
  } else {
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++size;
}

template <class T>
void GenDoublyLinkedList<T>::insertBack(T d) {
  ListNode<T> *node = new ListNode<T>(d);
  if(isEmpty()) {
    front = node;
  } else {
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

template <class T>
T GenDoublyLinkedList<T>::removeFront() {
  if(!isEmpty()) {
    ListNode<T> *ft = front;
    if(front->next == NULL) {
      back = NULL;
    } else {
      front->next->prev = NULL;
    }
    T temp = front->data;
    front = front->next;
    ft->next = NULL;
    delete ft;
    --size;
    return temp;
  } else {
    throw range_error("empty list");
  }
}

template <class T>
T GenDoublyLinkedList<T>::removeBack() {
  if(!isEmpty()) {
    ListNode<T> *bk = back;
    if(back->prev == NULL) {
      front = NULL;
    } else {
      back->prev->next = NULL;
    }
    T temp = back->data;
    back = back->prev;
    bk->prev = NULL;
    delete bk;
    --size;
    return temp;
  } else {
    return nullptr;
  }
}

template <class T>
void GenDoublyLinkedList<T>::insertPos(T d, int p) {
  ListNode<T> *node = ListNode<T>(d);
  if(isEmpty()) {
    front = node;
    back = node;
  } else if(p > size) { // out of bounds
    return;
  } else {
    ListNode<T> *current = front;
    int count = 0;
    if(count == p) { // at insertion point
      if(p == 0) { // at front
        node->next = front;
        front->prev = node;
        front = node;
      } else if(p == size) { // at back
        node->prev = back;
        back->next = node;
        back = node;
      } else {
        current->prev = node;
        node->next = current;
      }
      ++size;
    }
    current = current->next;
    ++count;
  }
}

template <class T>
ListNode<T>* GenDoublyLinkedList<T>::remove(T d) {
  while(!isEmpty()) {
    ListNode<T> *current = front;
    while(current->data != d) {
      current = current->next;
      if(current == NULL) {
        return NULL; // value not found
      }
    }
    if(current == front) {
      front = current->next;
      current->next->prev = current->prev;
    } else if(current == back) {
      back = current->prev;
      current->prev->next = current->next;
    } else {
      current->next->prev = current->prev;
      current->prev->next = current->next;
    }
    current->next = NULL;
    current->prev = NULL;
    --size;
    return current;
  }
}

template <class T>
int GenDoublyLinkedList<T>::find(T d) {
  int idx = 0;
  ListNode<T> *current = front;
  while(current != NULL) {
    if(current->data == d) {
      break;
    }
    ++idx;
    current = current->next;
  }
  if(current == NULL) {
    idx = -1;
  }
  return idx;
}

template <class T>
bool GenDoublyLinkedList<T>::isEmpty() {
  if(size == 0) {
    return true;
  } else {
    return false;
  }
}

template <class T>
void GenDoublyLinkedList<T>::printList() {
  ListNode<T> *current = front;
  while(current != NULL) {
    cout << current->data << endl;
    current = current->next;
  }
}

template <class T>
unsigned int GenDoublyLinkedList<T>::getSize() {
  return size;
}
