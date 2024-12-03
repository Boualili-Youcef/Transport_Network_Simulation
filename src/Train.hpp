#ifndef TRANSPORT_TRAIN_HPP
#define TRANSPORT_TRAIN_HPP

#include "SubwayLine.hpp"
#include "State.hpp"
#include "Way.hpp"
#include <string>

class Train
{

private:
  std::string id;
  unsigned int position;
  unsigned int delay;
  const SubwayLine &subWayLine;
  unsigned int station_index;
  State state;
  Way way;
  unsigned int next_time;

public:
  Train(const SubwayLine &subWayLine, unsigned int start_time, unsigned int position, Way way);

  Train(const Train &other);

  void display();

  void run(unsigned int time);

  // ******************* GETTERS :  *************************
  const std::string &getId() const;

  unsigned int getNextTime() const;

  State getState() const;

  unsigned int getStationIndex() const;

  const SubwayLine &getLine() const;

  ~Train();
};

typedef struct Train *TrainPtr;

#endif // TRANSPORT_TRAIN_HPP
