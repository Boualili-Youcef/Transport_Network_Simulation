#ifndef TRANSPORT_ITERATOR_HPP
#define TRANSPORT_ITERATOR_HPP

#include "List.hpp"

struct Iterator {

  Iterator(const List &list, bool forward)
    : list(list), current_cell(forward ? list.first : list.last), forward(forward) {}

  const std::shared_ptr<Train> &current() { return current_cell->data; }

  bool has_more() { return current_cell != nullptr; }

  void next() { current_cell = forward ? current_cell->next : current_cell->previous; }

  const List &list;
  std::shared_ptr<Cell> current_cell;
  bool forward;
};

#endif //TRANSPORT_ITERATOR_HPP
