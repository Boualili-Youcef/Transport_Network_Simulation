#ifndef BUS_STATION_HPP
#define BUS_STATION_HPP


class BusStop
{
private:
  string name;
  unsigned int stop_duration;

public:
  // ******************* GETTERS :  *************************
  string getName() const
  {
    return name;
  }
  unsigned int getStopDuration() const 
  {
    return stop_duration;
  }

  // ******************* SETTERS :  *************************

  void setName(string name)
  {
    this->name = name;
  }

  void setStopDuration(unsigned int stop_duration)
  {
    this->stop_duration = stop_duration;
  }
};

#endif // BUS_STATION_HPP
