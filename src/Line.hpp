#ifndef TRANSPORT_LINE_HPP
#define TRANSPORT_LINE_HPP

#include "Station.hpp"

struct Line {
  char *name;
  unsigned int station_number;
  unsigned int *durations;
  Station *stations;
  unsigned int flip_duration;
  unsigned int station_index;
  unsigned int train_number;

  Line(const char *name, unsigned int station_number, unsigned int train_number, float flip_duration);

  void add_station(const char *name, float stop_duration, float duration);

  unsigned int get_total_duration();

  ~Line();
};

typedef struct Line *LinePtr;

#endif //TRANSPORT_LINE_HPP
