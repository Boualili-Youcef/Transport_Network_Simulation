#include "Iterator.hpp"
#include "Kernel.hpp"

#include <iostream>
#include <limits.h>

Kernel::Kernel() {
}

void Kernel::add_line(std::shared_ptr<Line> line) {
  lines.add_first(line);
}

void Kernel::run(unsigned int begin, unsigned int end) {
  unsigned int time = begin;

  while (time <= end) {
    unsigned int min_next_time = INT_MAX;
    Iterator<Line> it(lines, true);

    while (it.has_more()) {
      unsigned int next_time = it.current()->run(time);

      {
        List<Train> stopped_trains = it.current()->get_trains(STOP);
        Iterator<Train> it(stopped_trains, true);
        while (it.has_more()) {
          std::cout << time << " : " << it.current()->getId() << " in station "
                    << it.current()->getLine().getStations()[it.current()->getStationIndex()].getName() << std::endl;
          it.next();
        }
      }

      if (next_time < min_next_time) {
        min_next_time = next_time;
      }
      it.next();
    }
    time = min_next_time;
  }
}

Kernel::~Kernel() {
}