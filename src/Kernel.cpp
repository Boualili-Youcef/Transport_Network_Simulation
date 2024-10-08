#include "Iterator.hpp"
#include "Kernel.hpp"

#include <iostream>

Kernel::Kernel(Line *line) : line(line) {
  unsigned int i;

  for (i = 0; i < line->train_number; ++i) {
    trains.add_first(new Train(line, 0, i, UP));
  }
}

List Kernel::get_trains(State state) {
  List stopped_trains;
  Iterator it(&trains, true);

  while (it.has_more()) {
    if (it.current()->state == state) {
      stopped_trains.add_first(new Train(*it.current()));
    }
    it.next();
  }
  return stopped_trains;
}

unsigned int Kernel::run(unsigned int time) {
  unsigned int min_next_time = INT_MAX;
  Iterator it(&trains, true);

  while (it.has_more()) {
    if (it.current()->next_time == time) {
      it.current()->run(time);

//      std::cout << time << " => ";
//      it.current()->display();
//      std::cout << std::endl;

    }
    if (it.current()->next_time < min_next_time) {
      min_next_time = it.current()->next_time;
    }
    it.next();
  }
  return min_next_time;
}

void Kernel::run(unsigned int begin, unsigned int end) {
  unsigned int time = begin;

  while (time <= end) {
    time = run(time);

    List stopped_trains = get_trains(STOP);
    Iterator it(&stopped_trains, true);
    while (it.has_more()) {
      std::cout << time << " : " << it.current()->id << " in station " << it.current()->line->stations[it.current()->station_index].name << std::endl;
      it.next();
    }
  }
}

Kernel::~Kernel() {
}