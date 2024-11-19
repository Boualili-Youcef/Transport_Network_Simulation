#ifndef TRANSPORT_STATION_HPP
#define TRANSPORT_STATION_HPP

#include <string>

class BusStop
{
private:
  std::string name;
  unsigned int stop_duration;

public:
  // ******************* GETTERS :  *************************
  std::string getName() const
  {
    return name;
  }
  unsigned int getStopDuration() const 
  {
    return stop_duration;
  }

  // ******************* SETTERS :  *************************

  void setName(std::string name)
  {
    this->name = name;
  }

  void setStopDuration(unsigned int stop_duration)
  {
    this->stop_duration = stop_duration;
  }
};

#endif // TRANSPORT_STATION_HPP
