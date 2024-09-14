#include <stddef.h>

#include "transport.h"

int main()
{
  unsigned int time;
  struct Line *line = NULL;
  struct Train **trains = NULL;

  /* Build line and trains */
  line  = create_line("L1", 6, 8, 4.f);
  add_station_to_line(line, "1", 2, 4.1f);
  add_station_to_line(line, "2_1", 2, 3.5f);
  add_station_to_line(line, "3", 2, 4.2f);
  add_station_to_line(line, "4", 2, 3.2f);
  add_station_to_line(line, "5_1", 2, 5.f);
  add_station_to_line(line, "6", 2, 0.f);
  trains = create_trains(line);

  /* Loop simulation */
  time = 0;
  while (time < 1500) {
    time = run_trains(trains, line, time);
  }

  /* Destroy all lines and trains */
  destroy_trains(line, trains);
  destroy_line(line);
  return 0;
}