#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "transport.h"

/* Convert State to string */
const char *state_to_string(enum State state)
{
  switch (state) {
  case WAIT_START: return "WAIT_START";
  case START: return "START";
  case RUNNING: return "RUNNING";
  case STOP: return "STOP";
  case FLIP: return "FLIP";
  default: return "";
  }
}

/* Creation of Line -> constructor */
struct Line *create_line(const char *name,
                         unsigned int station_number,
                         unsigned int train_number,
                         float flip_duration)
{
  struct Line *line = (struct Line *) malloc(sizeof(struct Line));

  line->name = (char *) malloc(sizeof(char) * (strlen(name)) + 1);
  strcpy(line->name, name);
  line->station_number = station_number;
  line->stations = (struct Station *) malloc(station_number * sizeof(struct Station));
  line->durations = (unsigned int *) malloc((station_number - 1) * sizeof(unsigned int));
  line->train_number = train_number;
  line->flip_duration = (int) (flip_duration * 60);
  line->station_index = 0;
  return line;
}

/* Add a new Station to Line -> Line method */
void add_station_to_line(struct Line *line, const char *name, float stop_duration, float duration)
{
  line->stations[line->station_index].name = (char *) malloc(sizeof(char) * (strlen(name)) + 1);
  strcpy(line->stations[line->station_index].name, name);
  line->stations[line->station_index].stop_duration = (int) (stop_duration * 60);
  if (line->station_index < line->station_number - 1) {
    line->durations[line->station_index] = (int) (duration * 60);
  }
  line->station_index++;
}

/* Compute the total duration of travel of Line (round trip) -> Line method */
unsigned int get_total_duration_of_line(struct Line *line)
{
  unsigned int total = 0;
  unsigned int i;

  for (i = 0; i < line->station_number; ++i) {
    total += line->stations[i].stop_duration;
    if (i < line->station_number - 1) {
      total += line->durations[i];
    }
  }
  total += 2 * line->flip_duration;
  return total;
}

/* Memory liberation of Line -> destructor */
void destroy_line(struct Line *line)
{
  unsigned int i;

  free(line->name);
  for (i = 0; i < line->station_number; ++i) {
    free(line->stations[i].name);
  }
  free(line->stations);
  free(line->durations);
  free(line);
}

/* Creation of Train -> constructor */
struct Train *create_train(struct Line *line,
                           unsigned int start_time,
                           unsigned int position,
                           enum Way way)
{
  struct Train *train = (struct Train *) malloc(sizeof(struct Train));

  train->id = (char *) malloc(sizeof(char) * (strlen(line->name) + 4));
  train->id[0] = 0;
  train->position = position;
  train->way = way;
  train->line = line;
  train->delay = floor((double) get_total_duration_of_line(line) / (double) line->train_number);
  if (train->position == 0) {
    train->state = START;
    train->next_time = start_time;
  } else {
    train->state = WAIT_START;
    train->next_time = start_time + train->position * train->delay;
  }
  if (train->way == UP) {
    train->station_index = 0;
  } else {
    train->station_index = train->line->station_number - 1;
  }
  sprintf(train->id, "%s_%d", line->name, train->position + 1);
  return train;
}

/* Display description and state of a train */
void display_train(struct Train *train)
{
  printf("train %s: %s %s %s of line %s in way %s",
         train->id,
         state_to_string(train->state),
         train->state == RUNNING ? "to station" : "in station",
         train->line->stations[train->station_index].name,
         train->line->name,
         train->way == UP ? "UP" : "DOWN");
}

/* Dynamics of Train: state automata */
/* Next time: date of next state change */
void run_train(struct Train *train, unsigned int time)
{
  if (train->state == WAIT_START) {
    train->state = START;
    train->next_time = time;
  } else if (train->state == START || train->state == STOP) {
    if ((train->station_index < train->line->station_number - 1 && train->way == UP)
        || (train->station_index > 0 && train->way == DOWN)) {
      train->state = RUNNING;
      train->next_time = time + (train->way == UP ? train->line->durations[train->station_index] :
                                 train->line->durations[train->station_index - 1]);
      train->station_index += train->way == UP ? 1 : -1;
    } else {
      train->state = FLIP;
      train->next_time = time + train->line->flip_duration;
      train->way = train->way == UP ? DOWN : UP;
    }
  } else if (train->state == RUNNING || train->state == FLIP) {
    train->state = STOP;
    train->next_time = time + train->line->stations[train->station_index].stop_duration;
  }
}

/* Memory liberation of Train -> destructor */
void destroy_train(struct Train *train)
{
  free(train->id);
  free(train);
}

/*** Simulation kernel ***/
/* Creation of all trains of a line */
struct Train **create_trains(struct Line *line)
{
  struct Train **trains;
  unsigned int i;

  trains = (struct Train **) malloc(sizeof(TrainPtr) * line->train_number);
  for (i = 0; i < line->train_number; ++i) {
    trains[i] = create_train(line, 0, i, UP);
  }
  return trains;
}

/* Compute next state of train which the next time is equal to time */
/* Display state of trains with a new state */
/* Return next time of the earliest state change */
unsigned int run_trains(struct Train **trains, struct Line *line, unsigned int time)
{
  unsigned int min_next_time = INT_MAX;
  unsigned int i;

  for (i = 0; i < line->train_number; ++i) {
    if (trains[i]->next_time == time) {
      run_train(trains[i], time);

      /* display */
      printf("%d => ", time);
      display_train(trains[i]);
      printf("\n");
    }
    if (trains[i]->next_time < min_next_time) {
      min_next_time = trains[i]->next_time;
    }
  }
  return min_next_time;
}

/* Memory liberation of all trains */
void destroy_trains(struct Line *line, struct Train **trains)
{
  unsigned int i;

  for (i = 0; i < line->train_number; ++i) {
    destroy_train(trains[i]);
  }
  free(trains);
}