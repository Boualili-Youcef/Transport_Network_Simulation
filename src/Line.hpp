#ifndef TRANSPORT_LINE_HPP
#define TRANSPORT_LINE_HPP

#include "List.hpp"
#include "State.hpp"
#include "Station.hpp"

#include <valarray>

struct Train;

class Line
{
private:
  char *name;
  unsigned int station_number;
  std::valarray<unsigned int> durations;
  std::valarray<Station> stations;
  unsigned int train_number;
  unsigned int flip_duration;
  unsigned int station_index;
  List<Train> trains;

public:
  Line(const char *name, unsigned int station_number, unsigned int train_number, float flip_duration);
  List<Train> get_trains(State state);

  unsigned int get_total_duration() const;

  void add_station(const char *name, float stop_duration, float duration);

  unsigned int run(unsigned int time);

  std::valarray<Station> getStations() const;

  unsigned int getTrainNumber() const;

  unsigned int getStationNumber() const;

  std::valarray<unsigned int> getDurations() const;

  unsigned int getFlipDuration() const;

  char *getName() const;

  ~Line();
};

#endif // TRANSPORT_LINE_HPP
