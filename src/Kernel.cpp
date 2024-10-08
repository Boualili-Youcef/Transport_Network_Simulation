#include "Kernel.hpp"

#include <iostream>

Kernel::Kernel(Line *line) : line(line)
{
  unsigned int i;

  trains = new Train*[line->train_number];
  for (i = 0; i < line->train_number; ++i) {
    trains[i] = new Train(line, 0, i, UP);
  }
}

void Kernel::run(unsigned int begin, unsigned int end)
{
  unsigned int time = begin;

  while (time <= end) {
    unsigned int min_next_time = INT_MAX;
    unsigned int i;

    for (i = 0; i < line->train_number; ++i) {
      if (trains[i]->next_time == time) {
        trains[i]->run(time);

        /* display */
        std::cout << time << " => ";
        trains[i]->display();
        std::cout << std::endl;
      }
      if (trains[i]->next_time < min_next_time) {
        min_next_time = trains[i]->next_time;
      }
    }
    time = min_next_time;
  }
}

/* Memory liberation of all trains */
Kernel::~Kernel()
{
  for (unsigned int i = 0; i < line->train_number; ++i) {
    delete trains[i];
  }
  delete[] trains;
}