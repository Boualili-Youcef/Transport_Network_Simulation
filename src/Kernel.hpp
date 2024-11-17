#ifndef TRANSPORT_KERNEL_HPP
#define TRANSPORT_KERNEL_HPP

#include "Line.hpp"
#include "List.hpp"
#include "Train.hpp"

class Kernel {
private:
  List<Line> lines;

public:
  Kernel();

  void add_line(std::shared_ptr<Line> line);

  void run(unsigned int begin, unsigned int end);

  ~Kernel();
};

#endif //TRANSPORT_KERNEL_HPP
