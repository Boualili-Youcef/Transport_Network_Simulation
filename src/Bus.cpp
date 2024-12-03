#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "Bus.hpp"

Bus::Bus(const BusLine &busLine, unsigned int start_time, unsigned int position, Way way) : busLine(busLine)
{
  this->position = position;
  this->way = way;
  delay = std::floor((double)busLine.get_total_duration() / (double)busLine.getBusNumber());
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
    station_index = busLine.getStationNumber() - 1;
  }
  this->id = "ID_" + busLine.getName() + "_" + std::to_string(way == UP ? position + 1 : position + (busLine.getBusNumber() / 2) + 1);

  //  std::cout << "[Bus] constructor - " << id << std::endl;
}

Bus::Bus(const Bus &other) : busLine(other.busLine)
{
  id = other.id;
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
  if (state == STOP)
    std::cout << "bus " << id << ": " << state_to_string(state) << " " << (state == RUNNING ? "to station" : "in station") << " " << busLine.getStations()[station_index].getName() << " of bus line " << busLine.getName() << " (heading " << (way == UP ? "UP)" : "DOWN)");
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
    if ((station_index < busLine.getStationNumber() - 1 and way == UP) or (station_index > 0 and way == DOWN))
    {
      state = RUNNING;
      next_time = time + (way == UP ? busLine.getDurations()[station_index] : busLine.getDurations()[station_index - 1]);
      station_index += way == UP ? 1 : -1;
    }
    else
    {
      state = FLIP;
      next_time = time + busLine.getFlipDuration();
      way = way == UP ? DOWN : UP;
    }
  
  }
  else if (state == RUNNING or state == FLIP)
  {
    state = STOP;
    next_time = time + busLine.getStations()[station_index].getStopDuration();
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
  return busLine;
}

Bus::~Bus()
{

  //  std::cout << "[Bus] destructor - " << id << std::endl;
}