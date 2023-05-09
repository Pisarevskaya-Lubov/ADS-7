// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>
#include <string>

template <typename T>
class TPQueue {
 public:
  TPQueue() : head(nullptr), tail(nullptr) { }
  ~TPQueue();
  void push(const T&);
  T pop();
  void print();

 private:
  struct Item {
    T data;
    Item* next;
    Item* previous;
  };
  Item* head;
  Item* tail;
  TPQueue::Item* create(const T&);
};

template <typename T>
void TPQueue<T>::print() {
  Item* temp = head;
  while (temp) {
    std::cout << temp->data << '\t';
    temp = temp->next;
  }
    std::cout << std::endl;
}

template <typename T>
TPQueue<T>::~TPQueue() {
  while (head) {
    pop();
  }
}

template <typename T>
void TPQueue<T>::push(const T& arg) {
  if (head == nullptr) {
    head = create(arg);
    tail = head;
  } else if (tail->data.prior >= arg.prior) {
    if (tail->data.ch == arg.ch) {
      tail->data = arg;
    } else {
      tail->next = create(arg);
      tail->next->previous = tail;
      tail = tail->next;
    }
  } else if (head == tail) {
    tail->previous = create(arg);
    head = tail->previous;
    head->next = tail;
  } else {
    Item* temp = tail;
    while (temp != head && temp->data.prior < arg.prior) {
      temp = temp->previous;
    }
    if (temp->data.prior > arg.prior) {
      Item* cage = new Item;
      cage->next = temp->next;
      cage->previous = temp;
      cage->data = arg;
      temp->next->previous = cage;
      temp->next = cage;
    }
    if (temp == head && temp->data.prior < arg.prior) {
      head->previous = create(arg);
      head = head->previous;
      head->next = temp;
    }
  }
}

template <typename T>
T TPQueue<T>::pop() {
  if (!head) {
    throw std::string("Empty!");
  } else {
    Item* temp = head->next;
    T data = head->data;
    delete head;
    head = temp;
    return data;
  }
}

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
  Item* item = new Item;
  item->data = data;
  item->next = nullptr;
  item->previous = nullptr;
  return item;
}

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
