#ifndef TRANSPORT_TRAIN_HPP
#define TRANSPORT_TRAIN_HPP

#include "Line.hpp"
#include "State.hpp"
#include "Way.hpp"

struct Train {
  char *id;
  unsigned int position;
  unsigned int delay;
  Line *line;
  unsigned int station_index;
  State state;
  Way way;
  unsigned int next_time;

  Train(Line *line, unsigned int start_time, unsigned int position, Way way);

  Train(const Train& other);

  void display();

  void run(unsigned int time);

  ~Train();
};

typedef struct Train *TrainPtr;

#endif //TRANSPORT_TRAIN_HPP
