#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "Train.hpp"

Train::Train(struct Line *line, unsigned int start_time, unsigned int position, Way way) {
  id = new char[strlen(line->name) + 4];
  id[0] = 0;
  this->position = position;
  this->way = way;
  this->line = line;
  delay = std::floor((double) line->get_total_duration() / (double) line->train_number);
  if (position == 0) {
    state = START;
    next_time = start_time;
  } else {
    state = WAIT_START;
    next_time = start_time + position * delay;
  }
  if (way == UP) {
    station_index = 0;
  } else {
    station_index = line->station_number - 1;
  }
  sprintf(id, "%s_%d", line->name, position + 1);

//  std::cout << "[Train] constructor - " << id << std::endl;

}

Train::Train(const Train &other) {
  id = new char[strlen(other.id) + 1];
  strcpy(id, other.id);
  position = other.position;
  way = other.way;
  line = other.line;
  delay = other.delay;
  state = other.state;
  next_time = other.next_time;
  station_index = other.station_index;

  //  std::cout << "[Train] copy constructor - " << id << std::endl;

}

void Train::display() {
  std::cout << "train " << id << ": " << state_to_string(state) << " " <<
            (state == RUNNING ? "to station" : "in station") << " " <<
            line->stations[station_index].name << " " <<
            line->name << " " << (
              way == UP ? "UP" : "DOWN");
}

void Train::run(unsigned int time) {
  if (state == WAIT_START) {
    state = START;
    next_time = time;
  } else if (state == START || state == STOP) {
    if ((station_index < line->station_number - 1 && way == UP)
        || (station_index > 0 && way == DOWN)) {
      state = RUNNING;
      next_time = time + (way == UP ? line->durations[station_index] :
                          line->durations[station_index - 1]);
      station_index += way == UP ? 1 : -1;
    } else {
      state = FLIP;
      next_time = time + line->flip_duration;
      way = way == UP ? DOWN : UP;
    }
  } else if (state == RUNNING || state == FLIP) {
    state = STOP;
    next_time = time + line->stations[station_index].stop_duration;
  }
}

Train::~Train() {

//  std::cout << "[Train] destructor - " << id << std::endl;

  delete[] id;
}