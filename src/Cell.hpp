#ifndef TRANSPORT_CELL_HPP
#define TRANSPORT_CELL_HPP

#include "Train.hpp"

#include <iostream>
#include <memory>

struct Cell {
  Cell(const std::shared_ptr<Train>& data, const std::shared_ptr<Cell>& previous, const std::shared_ptr<Cell>& next)
    : data(data), previous(previous), next(next) {

//    std::cout << "[Cell] constructor" << std::endl;

  }

  ~Cell() {

//    std::cout << "[Cell] destructor" << std::endl;

  }

  std::shared_ptr<Train> data;
  std::shared_ptr<Cell> next;
  std::shared_ptr<Cell> previous;
};

#endif //TRANSPORT_CELL_HPP
