#ifndef BUS_LINE_HPP
#define BUS_LINE_HPP

#include "List.hpp"
#include "State.hpp"
#include "BusStop.hpp"

#include <valarray>
#include <string>

struct Bus;

class BusLine
{
private:
  std::string name;
  unsigned int station_number;
  std::valarray<unsigned int> durations;
  std::valarray<BusStop> stations;
  unsigned int bus_number;
  unsigned int flip_duration;
  unsigned int station_index;
  List<Bus> buses;

public:
  BusLine(const std::string name, unsigned int station_number, unsigned int bus_number, float flip_duration);
  List<Bus> get_buses(State state);

  unsigned int get_total_duration() const;

  void add_bus_stop(const std::string name, float stop_duration, float duration = 0);

  unsigned int run(unsigned int time);

  // ******************* GETTERS :  *************************
  const std::valarray<BusStop>& getStations() const;

  unsigned int getBusNumber() const;

  unsigned int getStationNumber() const;

  const std::valarray<unsigned int>& getDurations() const;

  unsigned int getFlipDuration() const;

  const std::string &getName() const;

  // ******************* SETTERS :  *************************
  void setName(const string &name);

  ~BusLine();
};

#endif
