#ifndef TRANSPORT_TRANSPORT_H
#define TRANSPORT_TRANSPORT_H

/* enum State */
enum State
{
  WAIT_START, START, RUNNING, STOP, FLIP
};

/* enum Way */
enum Way
{
  UP, DOWN
};

/* struct Station */
struct Station
{
  char *name;
  unsigned int stop_duration;
};

/* struct Line */
struct Line
{
  char *name;
  unsigned int station_number;
  unsigned int *durations;
  struct Station *stations;
  unsigned int flip_duration;
  unsigned int station_index;
  unsigned int train_number;
};

typedef struct Line *LinePtr;

/* struct Train */
struct Train
{
  char *id;
  unsigned int position;
  unsigned int delay;
  struct Line *line;
  unsigned int station_index;
  enum State state;
  enum Way way;
  unsigned int next_time;
};

typedef struct Train *TrainPtr;

const char *state_to_string(enum State state);

struct Line *create_line(const char *name,
                         unsigned int station_number,
                         unsigned int train_number,
                         float flip_duration);

void add_station_to_line(struct Line *line, const char *name, float stop_duration, float duration);

unsigned int get_total_duration_of_line(struct Line *line);

void destroy_line(struct Line *line);

struct Train *create_train(struct Line *line,
                           unsigned int start_time,
                           unsigned int position,
                           enum Way way);

void display_train(struct Train *train);

void run_train(struct Train *train, unsigned int time);

void destroy_train(struct Train *train);

struct Train **create_trains(struct Line *line);

unsigned int run_trains(struct Train **trains, struct Line *line, unsigned int time);

void destroy_trains(struct Line *line, struct Train **trains);

#endif //TRANSPORT_TRANSPORT_H
