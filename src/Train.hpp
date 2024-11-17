#ifndef TRANSPORT_TRAIN_HPP
#define TRANSPORT_TRAIN_HPP

#include "Line.hpp"
#include "State.hpp"
#include "Way.hpp"

class Train
{

private:
  char *id;
  unsigned int position;
  unsigned int delay;
  const Line &line;
  unsigned int station_index;
  State state;
  Way way;
  unsigned int next_time;

public:
  Train(const Line &line, unsigned int start_time, unsigned int position, Way way);

  Train(const Train &other);

  void display();

  void run(unsigned int time);

  char *getId() const;

  unsigned int getNextTime() const;

  State getState() const;

  unsigned int getStationIndex() const;

  const Line &getLine() const;


  ~Train();
};

typedef struct Train *TrainPtr;

#endif // TRANSPORT_TRAIN_HPP
