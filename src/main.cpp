#include <stddef.h>

#include "Kernel.hpp"
#include "SubwayLine.hpp"
#include "BusLine.hpp"

int main()
{
  /* Build subWayLine */
  std::shared_ptr<SubwayLine> subWayLine = std::make_shared<SubwayLine>("L1", 6, 8, 4.f);
  subWayLine->add_station("1", 0.5f, 4.1f);
  subWayLine->add_station("2_1", 0.5f, 3.5f);
  subWayLine->add_station("3", 0.5f, 4.2f);
  subWayLine->add_station("4", 0.5f, 3.2f);
  subWayLine->add_station("5_1", 0.5f, 5.f);
  subWayLine->add_station("6", 0.5f, 0.f);

  /* Building the BUS Lines */
  std::shared_ptr<BusLine> busLine_1 = std::make_shared<BusLine>("A1", 10, 10, 5);
  std::shared_ptr<BusLine> busLine_2 = std::make_shared<BusLine>("A2", 10, 10, 7);

  busLine_1->add_bus_stop("1", 2, 1.7f);
  busLine_1->add_bus_stop("2", 2, 4.5f);
  busLine_1->add_bus_stop("3", 2, 6.9f);
  busLine_1->add_bus_stop("4", 2, 3.f);
  busLine_1->add_bus_stop("5", 2, 5.3f);
  busLine_1->add_bus_stop("6", 2, 6.1f);
  busLine_1->add_bus_stop("7", 2, 7.4f);
  busLine_1->add_bus_stop("8", 2, 3.4f);
  busLine_1->add_bus_stop("9", 2, 2.2f);
  busLine_1->add_bus_stop("10", 2, 0.f);
 

  busLine_2->add_bus_stop("11", 2, 3.2f);
  busLine_2->add_bus_stop("12", 2, 2.7f);
  busLine_2->add_bus_stop("13", 2, 4.9f);
  busLine_2->add_bus_stop("14", 2, 4.3f);
  busLine_2->add_bus_stop("15", 2, 7.6f);
  busLine_2->add_bus_stop("16", 2, 6.9f);
  busLine_2->add_bus_stop("17", 2, 1.2f);
  busLine_2->add_bus_stop("18", 2, 2.f);
  busLine_2->add_bus_stop("19", 2, 5.1f);
  busLine_2->add_bus_stop("20", 2, 0.f);


  Kernel kernel;

  kernel.add_subway_line(subWayLine);
  kernel.add_bus_line(busLine_1);
  kernel.add_bus_line(busLine_2);

  /* Loop simulation */
  kernel.run(0, 400);

  return 0;
}