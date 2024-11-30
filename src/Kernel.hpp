#ifndef TRANSPORT_KERNEL_HPP
#define TRANSPORT_KERNEL_HPP

#include "SubwayLine.hpp"
#include "BusLine.hpp"
#include "List.hpp"
#include "Train.hpp"

class Kernel {
private:
  List<SubwayLine> subWayLines;
  List<BusLine> busLines;

public:
  Kernel();

  void add_subway_line(std::shared_ptr<SubwayLine> subWayLine);
  void add_bus_line(std::shared_ptr<BusLine> busLine);

  void run(unsigned int begin, unsigned int end);

  ~Kernel();
};

#endif //TRANSPORT_KERNEL_HPP
