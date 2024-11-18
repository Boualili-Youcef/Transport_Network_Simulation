#ifndef TRANSPORT_STATE_HPP
#define TRANSPORT_STATE_HPP

#include <string>

enum State {
  WAIT_START, START, RUNNING, STOP, FLIP
};

const std::string state_to_string(enum State state);

#endif //TRANSPORT_STATE_HPP
