#include <stddef.h>

#include "Kernel.hpp"
#include "SubwayLine.hpp"

int main() {
  /* Build subWayLine */
  std::shared_ptr<SubwayLine> subWayLine = std::make_shared<SubwayLine>("L1", 6, 8, 4.f);
  subWayLine->add_station("1", 0.5f, 4.1f);
  subWayLine->add_station("2_1", 0.5f, 3.5f);
  subWayLine->add_station("3", 0.5f, 4.2f);
  subWayLine->add_station("4", 0.5f, 3.2f);
  subWayLine->add_station("5_1", 0.5f, 5.f);
  subWayLine->add_station("6", 0.5f, 0.f);

  Kernel kernel;

  kernel.add_line(subWayLine);

  /* Loop simulation */
  kernel.run(0, 5000);

  return 0;
}