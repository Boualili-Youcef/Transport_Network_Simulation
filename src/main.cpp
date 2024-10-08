#include <stddef.h>

#include "Kernel.hpp"
#include "Line.hpp"

int main()
{
  /* Build line */
  Line* line  = new Line("L1", 6, 8, 4.f);
  line->add_station("1", 2, 4.1f);
  line->add_station("2_1", 2, 3.5f);
  line->add_station("3", 2, 4.2f);
  line->add_station("4", 2, 3.2f);
  line->add_station("5_1", 2, 5.f);
  line->add_station("6", 2, 0.f);

  Kernel kernel(line);

  /* Loop simulation */
  kernel.run(0, 1500);

  delete line;
  return 0;
}