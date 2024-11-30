#include "Iterator.hpp"
#include "Kernel.hpp"

#include <iostream>
#include <limits.h>

Kernel::Kernel() {
}

void Kernel::add_subway_line(std::shared_ptr<SubwayLine> subWayLine) {
  subWayLines.add_first(subWayLine);
}

void Kernel::add_bus_line(std::shared_ptr<BusLine> busLine){
  busLines.add_first(busLine);
}

void Kernel::run(unsigned int begin, unsigned int end) {
  unsigned int time = begin;

  while (time <= end) {
    unsigned int min_next_time = INT_MAX;
    Iterator<SubwayLine> it_subWay(subWayLines, true);

    Iterator<BusLine> it_bus_1(busLines, true);
    Iterator<BusLine> it_bus_2(busLines, true);

    while (it_subWay.has_more()) {
      unsigned int next_time = it_subWay.current()->run(time);

      {
        List<Train> stopped_trains = it_subWay.current()->get_trains(STOP);
        Iterator<Train> it_subWay(stopped_trains, true);
        while (it_subWay.has_more()) {
          // TODO: "Verification apres" 
          /*std::cout << time << " : " << it_subWay.current()->getId() << " in station "
                    << it_subWay.current()->getLine().getStations()[it_subWay.current()->getStationIndex()].getName() << std::endl;*/
          it_subWay.next();
        }
      }

      if (next_time < min_next_time) {
        min_next_time = next_time;
      }
      it_subWay.next();
    }

     while (it_bus_1.has_more()) {
      unsigned int next_time = it_bus_1.current()->run(time);

      {
        List<Bus> stopped_buses = it_bus_1.current()->get_buses(STOP);
        Iterator<Bus> it_bus_1(stopped_buses, true);
        while (it_bus_1.has_more()) {
          // TODO: "Verification apres" 
          /*std::cout << time << " : " << it_bus_1.current()->getId() << " in station "
                    << it_bus_1.current()->getLine().getStations()[it_bus_1.current()->getStationIndex()].getName() << std::endl;*/
          it_bus_1.next();
        }
      }

      if (next_time < min_next_time) {
        min_next_time = next_time;
      }
      it_bus_1.next();
      
    }

    while (it_bus_2.has_more()) {
      unsigned int next_time = it_bus_2.current()->run(time);

      {
        List<Bus> stopped_buses = it_bus_2.current()->get_buses(STOP);
        Iterator<Bus> it_bus_2(stopped_buses, true);
        while (it_bus_2.has_more()) {
          // TODO: "Verification apres" 
          /*std::cout << time << " : " << it_bus_2.current()->getId() << " in station "
                    << it_bus_2.current()->getLine().getStations()[it_bus_2.current()->getStationIndex()].getName() << std::endl;*/
          it_bus_2.next();
        }
      }

      if (next_time < min_next_time) {
        min_next_time = next_time;
      }
      it_bus_2.next();
      
    }

    

    time = min_next_time;
  }
}

Kernel::~Kernel() {
}