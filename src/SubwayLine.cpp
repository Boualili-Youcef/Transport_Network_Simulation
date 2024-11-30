#include <cstring>

#include "Iterator.hpp"
#include "SubwayLine.hpp"
#include "Train.hpp"
#include <limits.h>

SubwayLine::SubwayLine(const std::string name, unsigned int station_number, unsigned int train_number, float flip_duration) : station_number(station_number), stations(station_number), durations(station_number - 1), train_number(train_number),
                                                                                                                              flip_duration((int)(flip_duration * 60)), station_index(0)
{

  setName(name);
  for (unsigned int i = 0; i < train_number; ++i)
  {
    trains.add_first(std::make_shared<Train>(*this, 0, i, UP));
  }
}

void SubwayLine::add_station(const std::string name, float stop_duration, float duration)
{
  stations[station_index].setName(name); // Utilisation directe de std::string
  stations[station_index].setStopDuration((int)(stop_duration * 60));

  if (station_index < station_number - 1)
  {
    durations[station_index] = (int)(duration * 60);
  }
  station_index++;
}

unsigned int SubwayLine::get_total_duration() const
{
  unsigned int total = 0;
  unsigned int i;

  for (i = 0; i < station_number; ++i)
  {
    total += getStations()[i].getStopDuration();
    if (i < station_number - 1)
    {
      total += durations[i];
    }
  }
  total += 2 * flip_duration;
  return total;
}

List<Train> SubwayLine::get_trains(State state)
{
  List<Train> stopped_trains;
  Iterator<Train> it(trains, true);

  while (it.has_more())
  {
    if (it.current()->getState() == state)
    {
      stopped_trains.add_first(it.current());
    }
    it.next();
  }
  return stopped_trains;
}

unsigned int SubwayLine::run(unsigned int time)
{
  unsigned int min_next_time = INT_MAX;
  Iterator<Train> it(trains, true);

  while (it.has_more())
  {
    if (it.current()->getNextTime() == time)
    {
      // TODO: "Modification de ==STOP"
      it.current()->run(time);
      if (it.current()->getState() == STOP)
      {
        std::cout << time << " => ";
        it.current()->display();
        std::cout << std::endl;
      }
    }
    if (it.current()->getNextTime() < min_next_time)
    {
      min_next_time = it.current()->getNextTime();
    }
    it.next();
  }
  return min_next_time;
}

// ******************* GETTERS :  *************************
const std::valarray<Station> &SubwayLine::getStations() const
{
  return stations;
}

unsigned int SubwayLine::getTrainNumber() const
{
  return train_number;
}

unsigned int SubwayLine::getStationNumber() const
{
  return station_number;
}

const std::valarray<unsigned int> &SubwayLine::getDurations() const
{
  return durations;
}

unsigned int SubwayLine::getFlipDuration() const
{
  return flip_duration;
}

const std::string &SubwayLine::getName() const
{
  return name;
}

// ******************* SETTERS :  *************************

void SubwayLine::setName(const string &name)
{
  this->name = name;
}

SubwayLine::~SubwayLine()
{
}