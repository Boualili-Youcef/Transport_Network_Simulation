#include "Iterator.hpp"
#include "Kernel.hpp"

#include <iostream>
#include <limits.h>

Kernel::Kernel()
{
}

void Kernel::add_subway_line(std::shared_ptr<SubwayLine> subWayLine)
{
  subWayLines.add_first(subWayLine);
}

void Kernel::add_bus_line(std::shared_ptr<BusLine> busLine)
{
  busLines.add_first(busLine);
}

void Kernel::run(unsigned int begin, unsigned int end)
{
  unsigned int timeSubway = begin;
  unsigned int timeBus = begin;

  while (timeSubway <= end || timeBus <= end)
  {
    unsigned int min_next_time = INT_MAX;

    Iterator<SubwayLine> it_subWay(subWayLines, true);
    while (it_subWay.has_more())
    {
      unsigned int next_time = it_subWay.current()->run(timeSubway);

      List<Train> stopped_trains = it_subWay.current()->get_trains(STOP);
      Iterator<Train> it_train(stopped_trains, true);
      while (it_train.has_more())
      {

        it_train.next();
      }

      if (next_time < min_next_time)
      {
        min_next_time = next_time;
      }
      it_subWay.next();
    }

    Iterator<BusLine> it_bus_1(busLines, true);
    while (it_bus_1.has_more())
    {
      unsigned int next_time = it_bus_1.current()->run(timeBus);

      List<Bus> stopped_buses = it_bus_1.current()->get_buses(STOP);
      Iterator<Bus> it_bus(stopped_buses, true);
      while (it_bus.has_more())
      {

        it_bus.next();
      }

      if (next_time < min_next_time)
      {
        min_next_time = next_time;
      }
      it_bus_1.next();
    }

    if (timeSubway < min_next_time)
    {
      timeSubway = min_next_time;
    }
    if (timeBus < min_next_time)
    {
      timeBus = min_next_time;
    }
  }
}

Kernel::~Kernel()
{
}