#ifndef TRANSPORT_KERNEL_HPP
#define TRANSPORT_KERNEL_HPP

#include "SubwayLine.hpp"
#include "List.hpp"
#include "Train.hpp"

class Kernel {
private:
  List<SubwayLine> subWayLines;

public:
  Kernel();

  void add_line(std::shared_ptr<SubwayLine> subWayLine);

  void run(unsigned int begin, unsigned int end);

  ~Kernel();
};

#endif //TRANSPORT_KERNEL_HPP
