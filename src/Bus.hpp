#ifndef TRANSPORT_TRAIN_HPP
#define TRANSPORT_TRAIN_HPP

#include "BusLine.hpp"
#include "State.hpp"
#include "Way.hpp"
#include <string>

class Bus
{

private:
  std::string id;
  unsigned int position;
  unsigned int delay;
  const BusLine &subWayLine;
  unsigned int station_index;
  State state;
  Way way;
  unsigned int next_time;

public:
  Bus(const BusLine &subWayLine, unsigned int start_time, unsigned int position, Way way);

  Bus(const Bus &other);

  void display();

  void run(unsigned int time);

  // ******************* GETTERS :  *************************
  const std::string &getId() const;

  unsigned int getNextTime() const;

  State getState() const;

  unsigned int getStationIndex() const;

  const BusLine &getLine() const;

  // ******************* SETTERS :  *************************
  void setId(const std::string &id);

  ~Bus();
};

typedef struct Bus *TrainPtr;

#endif // TRANSPORT_TRAIN_HPP
