#ifndef TRANSPORT_STATE_HPP
#define TRANSPORT_STATE_HPP

enum State
{
  WAIT_START, START, RUNNING, STOP, FLIP
};

const char *state_to_string(enum State state);

#endif //TRANSPORT_STATE_HPP
