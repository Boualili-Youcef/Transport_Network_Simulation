#ifndef TRANSPORT_ITERATOR_HPP
#define TRANSPORT_ITERATOR_HPP

#include "List.hpp"

using namespace std;

template <typename Data>
class Iterator
{

private:
  const List<Data> &list;
  shared_ptr<Cell<Data>> current_cell;
  bool forward;

public:
  explicit Iterator(const List<Data> &list, bool forward)
      : list(list), current_cell(forward ? list.getFirst() : list.getLast()), forward(forward) {}

public:
  shared_ptr<Data> current() const
  {
    // on fait une verification que current_cell n'est pas null
    if (current_cell)
    {
      return current_cell->getData();
    }
    return nullptr;
  }
  
  bool has_more() const { return current_cell != nullptr; }

  void next()
  {
    if (current_cell)
    {
      current_cell = forward ? current_cell->getNext() : current_cell->getPrevious();
    }
  }
};

#endif // TRANSPORT_ITERATOR_HPP
