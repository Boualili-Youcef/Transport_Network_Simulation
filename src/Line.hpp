#ifndef TRANSPORT_LINE_HPP
#define TRANSPORT_LINE_HPP

#include "List.hpp"
#include "State.hpp"
#include "Station.hpp"

#include <valarray>

struct Train;

struct Line {
  char *name;
  unsigned int station_number;
  std::valarray<unsigned int> durations;
  std::valarray<Station> stations;
  unsigned int train_number;
  unsigned int flip_duration;
  unsigned int station_index;
  List<Train> trains;

  Line(const char *name, unsigned int station_number, unsigned int train_number, float flip_duration);

  void add_station(const char *name, float stop_duration, float duration);

  unsigned int get_total_duration() const;

  List<Train> get_trains(State state);

  unsigned int run(unsigned int time);

  ~Line();
};

#endif //TRANSPORT_LINE_HPP
