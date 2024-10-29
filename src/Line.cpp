#include <cstring>

#include "Line.hpp"

Line::Line(const char *name, unsigned int station_number, unsigned int train_number, float flip_duration) :
  stations(station_number), durations(station_number - 1) {
  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);
  this->station_number = station_number;
  this->train_number = train_number;
  this->flip_duration = (int) (flip_duration * 60);
  station_index = 0;
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

Line::~Line() {
  unsigned int i;

  delete[] name;
  for (i = 0; i < station_number; ++i) {
    delete[] stations[i].name;
  }
}