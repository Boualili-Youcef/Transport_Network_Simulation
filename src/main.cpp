#include <stddef.h>

#include "Kernel.hpp"
#include "Line.hpp"

int main() {
  /* Build line */
  std::shared_ptr<Line> line = std::make_shared<Line>("L1", 6, 8, 4.f);
  line->add_station("1", 0.5f, 4.1f);
  line->add_station("2_1", 0.5f, 3.5f);
  line->add_station("3", 0.5f, 4.2f);
  line->add_station("4", 0.5f, 3.2f);
  line->add_station("5_1", 0.5f, 5.f);
  line->add_station("6", 0.5f, 0.f);

  Kernel kernel;

  kernel.add_line(line);

  /* Loop simulation */
  kernel.run(0, 5000);

  return 0;
}