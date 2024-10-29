#ifndef TRANSPORT_LIST_HPP
#define TRANSPORT_LIST_HPP

#include "Cell.hpp"

#include <iostream>

struct List {
  List() : first(nullptr), last(nullptr) {

//    std::cout << "[List] constructor" << std::endl;

  }

  List(const List &other) {
    std::shared_ptr<Cell> current = first;

    while (current != nullptr) {
      add_last(current->data);
      current = current->next;
    }

//    std::cout << "[List] copy constructor" << std::endl;

  }

  void add_first(const std::shared_ptr<Train> &data) {
    std::shared_ptr<Cell> new_cell = std::make_shared<Cell>(data, nullptr, first);

    if (first != nullptr) {
      first->previous = new_cell;
    }
    first = new_cell;
    last = last == nullptr ? first : last;
  }

  void add_last(const std::shared_ptr<Train> &data) {
    std::shared_ptr<Cell> new_cell = std::make_shared<Cell>(data, last, nullptr);

    if (last != nullptr) {
      last->next = new_cell;
    }
    last = new_cell;
    first = first == nullptr ? last : first;
  }

  void append(List &list) {
    std::shared_ptr<Cell> current = list.first;

    while (current != nullptr) {
      add_last(current->data);
      current = current->next;
    }
  }

  unsigned int size() {
    unsigned int size = 0;
    std::shared_ptr<Cell> current = first;

    while (current != last) {
      ++size;
      current = current->next;
    }
    return size;
  }

  void remove_first() {
    if (first != nullptr) {
      first = first->next;
      if (first == nullptr) {
        last = nullptr;
      }
    }
  }

  void remove_last() {
    if (last != nullptr) {
      last = last->previous;
      if (last == nullptr) {
        first = nullptr;
      }
    }
  }

  ~List() {

//    std::cout << "[List] destructor" << std::endl;

  }

  std::shared_ptr<Cell> first;
  std::shared_ptr<Cell> last;
};

#endif //TRANSPORT_LIST_HPP
