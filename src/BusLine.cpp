#include <cstring>

#include "Iterator.hpp"
#include "BusLine.hpp"
#include "Bus.hpp"
#include <limits.h>

BusLine::BusLine(const std::string name, unsigned int station_number, unsigned int bus_number, float flip_duration) : station_number(station_number), stations(station_number), durations(station_number - 1), bus_number(bus_number),
                                                                                                                      flip_duration((int)(flip_duration * 60)), station_index(0)
{

    setName(name);
    for (unsigned int i = 0; i < bus_number / 2; ++i)
    {

        buses.add_first(std::make_shared<Bus>(*this, 0, i, UP));
    }
    
    for (unsigned int i = bus_number / 2; i < bus_number; ++i)
    {
        buses.add_first(std::make_shared<Bus>(*this, 0, i - (bus_number / 2), DOWN));
    }
}

void BusLine::add_bus_stop(const std::string name, float stop_duration, float duration)
{
    stations[station_index].setName(name); // Utilisation directe de std::string
    stations[station_index].setStopDuration((int)(stop_duration * 60));

    if (station_index < station_number - 1)
    {
        durations[station_index] = (int)(duration * 60);
    }
    station_index++;
}

unsigned int BusLine::get_total_duration() const
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

List<Bus> BusLine::get_buses(State state)
{
    List<Bus> stopped_trains;
    Iterator<Bus> it(buses, true);

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

unsigned int BusLine::run(unsigned int time)
{
    unsigned int min_next_time = INT_MAX;
    Iterator<Bus> it(buses, true);
    while (it.has_more())
    {
        if (it.current()->getNextTime() == time)
        {

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
const std::valarray<BusStop> &BusLine::getStations() const
{
    return stations;
}

unsigned int BusLine::getBusNumber() const
{
    return bus_number;
}

unsigned int BusLine::getStationNumber() const
{
    return station_number;
}

const std::valarray<unsigned int> &BusLine::getDurations() const
{
    return durations;
}

unsigned int BusLine::getFlipDuration() const
{
    return flip_duration;
}

const std::string &BusLine::getName() const
{
    return name;
}

// ******************* SETTERS :  *************************

void BusLine::setName(const string &name)
{
    this->name = name;
}

BusLine::~BusLine()
{
}