#ifndef TRANSPORT_LIST_HPP
#define TRANSPORT_LIST_HPP

#include "Cell.hpp"

#include <iostream>

struct List {
  List() : first(nullptr), last(nullptr) {

//    std::cout << "[List] constructor" << std::endl;

  }

  List(const List& other) {
    Cell* current = first;

    while (current != nullptr) {
      add_last(current->data);
      current = current->next;
    }

//    std::cout << "[List] copy constructor" << std::endl;

  }

  void add_first(Train *data) {
    Cell *new_cell = new Cell(data, nullptr, first);

    if (first != nullptr) {
      first->previous = new_cell;
    }
    first = new_cell;
    last = last == nullptr ? first : last;
  }

  void add_last(Train *data) {
    Cell *new_cell = new Cell(data, last, nullptr);

    if (last != nullptr) {
      last->next = new_cell;
    }
    last = new_cell;
    first = first == nullptr ? last : first;
  }

  void append(List &list) {
    Cell *current = list.first;

    while (current != nullptr) {
      add_last(current->data);
      current = current->next;
    }
  }

  unsigned int size() {
    unsigned int size = 0;
    Cell *current = first;

    while (current != last) {
      ++size;
      current = current->next;
    }
    return size;
  }

  void remove_first() {
    if (first != nullptr) {
      Cell *removed_cell = first;

      first = first->next;
      if (first == nullptr) {
        last = nullptr;
      }
      delete removed_cell;
    }
  }

  void remove_last() {
    if (last != nullptr) {
      Cell *removed_cell = last;

      last = last->previous;
      if (last == nullptr) {
        first = nullptr;
      }
      delete removed_cell;
    }
  }

  ~List() {

//    std::cout << "[List] destructor" << std::endl;

    while (first != nullptr) {
      Cell *next = first->next;

      delete first;
      first = next;
    }
  }

  Cell *first;
  Cell *last;
};

#endif //TRANSPORT_LIST_HPP
