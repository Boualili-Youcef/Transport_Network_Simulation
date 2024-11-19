#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "Bus.hpp"

Bus::Bus(const BusLine &subWayLine, unsigned int start_time, unsigned int position, Way way) : subWayLine(subWayLine)
{
  setId("");
  this->position = position;
  this->way = way;
  delay = std::floor((double)subWayLine.get_total_duration() / (double)subWayLine.getBusNumber());
  if (position == 0)
  {
    state = START;
    next_time = start_time;
  }
  else
  {
    state = WAIT_START;
    next_time = start_time + position * delay;
  }
  if (way == UP)
  {
    station_index = 0;
  }
  else
  {
    station_index = subWayLine.getStationNumber() - 1;
  }
  setId("ID_" + subWayLine.getName() + "_" + std::to_string(position + 1)); // la partie importante std::to_string mettre un numerique en string

  //  std::cout << "[Bus] constructor - " << id << std::endl;
}

Bus::Bus(const Bus &other) : subWayLine(other.subWayLine)
{
  setId(other.id);
  position = other.position;
  way = other.way;
  delay = other.delay;
  state = other.state;
  next_time = other.next_time;
  station_index = other.station_index;

  //  std::cout << "[Bus] copy constructor - " << id << std::endl;
}

void Bus::display()
{
  std::cout << "train " << id << ": " << state_to_string(state) << " " << (state == RUNNING ? "to station" : "in station") << " " << subWayLine.getStations()[station_index].getName() << " " << subWayLine.getName() << " " << (way == UP ? "UP" : "DOWN");
}

void Bus::run(unsigned int time)
{
  if (state == WAIT_START)
  {
    state = START;
    next_time = time;
  }
  else if (state == START or state == STOP)
  {
    if ((station_index < subWayLine.getStationNumber() - 1 and way == UP) or (station_index > 0 and way == DOWN))
    {
      state = RUNNING;
      next_time = time + (way == UP ? subWayLine.getDurations()[station_index] : subWayLine.getDurations()[station_index - 1]);
      station_index += way == UP ? 1 : -1;
    }
    else
    {
      state = FLIP;
      next_time = time + subWayLine.getFlipDuration();
      way = way == UP ? DOWN : UP;
    }
  }
  else if (state == RUNNING or state == FLIP)
  {
    state = STOP;
    next_time = time + subWayLine.getStations()[station_index].getStopDuration();
  }
}

// ******************* GETTERS :  *************************
const std::string &Bus::getId() const
{
  return id;
}

unsigned int Bus::getNextTime() const
{
  return next_time;
}

State Bus::getState() const
{
  return state;
}

unsigned int Bus::getStationIndex() const
{
  return station_index;
}

const BusLine &Bus::getLine() const
{
  return subWayLine;
}

// ******************* SETTERS :  *************************
void Bus::setId(const std::string &id)
{
  this->id = id;
}

Bus::~Bus()
{

  //  std::cout << "[Bus] destructor - " << id << std::endl;
}