#include <cstring>

#include "Iterator.hpp"
#include "Line.hpp"
#include "Train.hpp"

Line::Line(const char *name, unsigned int station_number, unsigned int train_number, float flip_duration) :
  station_number(station_number), stations(station_number), durations(station_number - 1), train_number(train_number),
  flip_duration((int) (flip_duration * 60)), station_index(0) {
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
  for (unsigned int i = 0; i < train_number; ++i) {
    trains.add_first(std::make_shared<Train>(*this, 0, i, UP));
  }
}

void Line::add_station(const char *name, float stop_duration, float duration) {
  stations[station_index].name = new char[strlen(name)];
  strcpy(stations[station_index].name, name);
  stations[station_index].stop_duration = (int) (stop_duration * 60);
  if (station_index < station_number - 1) {
    durations[station_index] = (int) (duration * 60);
  }
  station_index++;
}

unsigned int Line::get_total_duration() const {
  unsigned int total = 0;
  unsigned int i;

  for (i = 0; i < station_number; ++i) {
    total += stations[i].stop_duration;
    if (i < station_number - 1) {
      total += durations[i];
    }
  }
  total += 2 * flip_duration;
  return total;
}

List<Train> Line::get_trains(State state) {
  List<Train> stopped_trains;
  Iterator<Train> it(trains, true);

  while (it.has_more()) {
    if (it.current()->state == state) {
      stopped_trains.add_first(it.current());
    }
    it.next();
  }
  return stopped_trains;
}

unsigned int Line::run(unsigned int time) {
  unsigned int min_next_time = INT_MAX;
  Iterator<Train> it(trains, true);

  while (it.has_more()) {
    if (it.current()->next_time == time) {
      it.current()->run(time);

      std::cout << time << " => ";
      it.current()->display();
      std::cout << std::endl;

    }
    if (it.current()->next_time < min_next_time) {
      min_next_time = it.current()->next_time;
    }
    it.next();
  }
  return min_next_time;
}

Line::~Line() {
  unsigned int i;

  delete[] name;
  for (i = 0; i < station_number; ++i) {
    delete[] stations[i].name;
  }
}