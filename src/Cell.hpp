#ifndef TRANSPORT_CELL_HPP
#define TRANSPORT_CELL_HPP

#include "Train.hpp"

#include <iostream>

struct Cell {
  Cell(Train *data, Cell *previous, Cell *next)
    : data(data), previous(previous), next(next) {

//    std::cout << "[Cell] constructor" << std::endl;

  }

  ~Cell() {

//    std::cout << "[Cell] destructor" << std::endl;

    delete data;
  }

  Train *data;
  Cell *next;
  Cell *previous;
};

#endif //TRANSPORT_CELL_HPP
