#include "State.hpp"

const char *state_to_string(enum State state) {
  switch (state) {
    case WAIT_START:
      return "WAIT_START";
    case START:
      return "START";
    case RUNNING:
      return "RUNNING";
    case STOP:
      return "STOP";
    case FLIP:
      return "FLIP";
    default:
      return "";
  }
}