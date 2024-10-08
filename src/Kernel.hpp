#ifndef TRANSPORT_KERNEL_HPP
#define TRANSPORT_KERNEL_HPP

#include "Line.hpp"
#include "List.hpp"
#include "Train.hpp"

struct Kernel {
  List trains;
  Line *line;

  Kernel(Line *line);

  List get_trains(State state);

  unsigned int run(unsigned int time);

  void run(unsigned int begin, unsigned int end);

  ~Kernel();
};

#endif //TRANSPORT_KERNEL_HPP
