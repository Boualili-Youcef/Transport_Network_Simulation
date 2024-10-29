#ifndef TRANSPORT_CELL_HPP
#define TRANSPORT_CELL_HPP

#include <iostream>
#include <memory>

template<typename Data>
struct Cell {
  Cell(const std::shared_ptr<Data>& data, const std::shared_ptr<Cell>& previous, const std::shared_ptr<Cell>& next)
    : data(data), previous(previous), next(next) {

//    std::cout << "[Cell] constructor" << std::endl;

  }

  ~Cell() {

//    std::cout << "[Cell] destructor" << std::endl;

  }

  std::shared_ptr<Data> data;
  std::shared_ptr<Cell> next;
  std::shared_ptr<Cell> previous;
};

#endif //TRANSPORT_CELL_HPP
