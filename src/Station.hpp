#ifndef TRANSPORT_STATION_HPP
#define TRANSPORT_STATION_HPP

class Station
{
private:
  char *name;
  unsigned int stop_duration;

public:
  char *getName()
  {
    return name;
  }
  unsigned int getStopDuration()
  {
    return stop_duration;
  }

  void setName(char *name)
  {
    this->name = name;
  }

  void setStopDuration(unsigned int stop_duration)
  {
    this->stop_duration = stop_duration;
  }
};

#endif // TRANSPORT_STATION_HPP
