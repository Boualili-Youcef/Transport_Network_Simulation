#ifndef TRANSPORT_KERNEL_HPP
#define TRANSPORT_KERNEL_HPP

#include "Line.hpp"
#include "Train.hpp"

struct Kernel {
  Train** trains;
  Line* line;

  Kernel(Line* line);

  void run(unsigned int begin, unsigned int end);

  ~Kernel();
};

#endif //TRANSPORT_KERNEL_HPP
