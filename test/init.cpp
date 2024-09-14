#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "transport.hpp"

TEST_CASE("create line", "init")
{
  struct Line *line = create_line("L1", 6, 8, 4);

  REQUIRE(strcmp(line->name, "L1") == 0);
  REQUIRE(line->station_number == 6);
  REQUIRE(line->station_index == 0);
  REQUIRE(line->stations != 0);
  REQUIRE(line->train_number == 8);
  REQUIRE(line->durations != 0);
  REQUIRE(line->flip_duration == 240);

  destroy_line(line);
}

TEST_CASE("create line and stations", "init")
{
  struct Line *line = create_line("L1", 6, 8, 4);

  add_station_to_line(line, "1", 2, 4.1f);
  add_station_to_line(line, "2_1", 2, 3.5f);
  add_station_to_line(line, "3", 2, 4.2f);
  add_station_to_line(line, "4", 2, 3.2f);
  add_station_to_line(line, "5_1", 2, 5);
  add_station_to_line(line, "6", 2, 0);

  REQUIRE(line->station_index == 6);
  REQUIRE(strcmp(line->stations[0].name, "1") == 0);
  REQUIRE(strcmp(line->stations[1].name, "2_1") == 0);
  REQUIRE(strcmp(line->stations[2].name, "3") == 0);
  REQUIRE(strcmp(line->stations[3].name, "4") == 0);
  REQUIRE(strcmp(line->stations[4].name, "5_1") == 0);
  REQUIRE(strcmp(line->stations[5].name, "6") == 0);
  for (unsigned int i = 0; i < 6; ++i) {
    REQUIRE(line->stations[i].stop_duration == 120);
  }
  REQUIRE(line->durations[0] == 246);
  REQUIRE(line->durations[1] == 210);
  REQUIRE(line->durations[2] == 252);
  REQUIRE(line->durations[3] == 192);
  REQUIRE(line->durations[4] == 300);

  destroy_line(line);
}

TEST_CASE("get total duration of line", "init")
{
  struct Line *line = create_line("L1", 6, 8, 4);

  add_station_to_line(line, "1", 2, 4.1f);
  add_station_to_line(line, "2_1", 2, 3.5f);
  add_station_to_line(line, "3", 2, 4.2f);
  add_station_to_line(line, "4", 2, 3.2f);
  add_station_to_line(line, "5_1", 2, 5);
  add_station_to_line(line, "6", 2, 0);

  REQUIRE(get_total_duration_of_line(line) == 2400);

  destroy_line(line);
}

TEST_CASE("create line, stations and trains", "init")
{
  struct Line *line = create_line("L1", 6, 8, 4);
  struct Train **trains = NULL;

  add_station_to_line(line, "1", 2, 4.1f);
  add_station_to_line(line, "2_1", 2, 3.5f);
  add_station_to_line(line, "3", 2, 4.2f);
  add_station_to_line(line, "4", 2, 3.2f);
  add_station_to_line(line, "5_1", 2, 5);
  add_station_to_line(line, "6", 2, 0);

  trains = create_trains(line);

  REQUIRE(trains != NULL);
  for (unsigned int i = 0; i < line->train_number; ++i) {
    REQUIRE(strcmp(trains[i]->id, (std::string("L1_") + std::to_string(i + 1)).c_str()) == 0);
    REQUIRE(trains[i]->position == i);
    REQUIRE(trains[i]->line == line);
    REQUIRE(trains[i]->station_index == 0);
    if (trains[i]->position == 0) {
      REQUIRE(trains[i]->state == START);
    } else {
      REQUIRE(trains[i]->state == WAIT_START);
    }
    REQUIRE(trains[i]->way == UP);
    REQUIRE(trains[i]->delay == 300);
    REQUIRE(trains[i]->next_time == i * 300);
  }

  destroy_trains(line, trains);
  destroy_line(line);
}

TEST_CASE("display trains", "init")
{
  struct Line *line = create_line("L1", 6, 8, 4);
  struct Train **trains = NULL;

  add_station_to_line(line, "1", 2, 4.1f);
  add_station_to_line(line, "2_1", 2, 3.5f);
  add_station_to_line(line, "3", 2, 4.2f);
  add_station_to_line(line, "4", 2, 3.2f);
  add_station_to_line(line, "5_1", 2, 5);
  add_station_to_line(line, "6", 2, 0);

  trains = create_trains(line);

  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  display_train(trains[0]);
  REQUIRE(buffer.str() == "Train L1_1: START in station 1 of L1 to UP");

  for (unsigned int i = 1; i < line->train_number; ++i) {
    buffer.str("");
    display_train(trains[i]);
    REQUIRE(buffer.str() == std::string("Train L1_") + std::to_string(i + 1) + ": WAIT_START in station 1 of L1 to UP");
  }

  std::cout.rdbuf(old);

  destroy_trains(line, trains);
  destroy_line(line);
}

TEST_CASE("simulation", "init")
{
  struct Line *line = create_line("L1", 6, 8, 4);
  struct Train **trains = NULL;

  add_station_to_line(line, "1", 2, 4.1f);
  add_station_to_line(line, "2_1", 2, 3.5f);
  add_station_to_line(line, "3", 2, 4.2f);
  add_station_to_line(line, "4", 2, 3.2f);
  add_station_to_line(line, "5_1", 2, 5);
  add_station_to_line(line, "6", 2, 0);

  trains = create_trains(line);

  unsigned int time = 0;

  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  while (time < 10000) {
    time = run_trains(trains, line, time);
  }

  REQUIRE(buffer.str() == "0 => Train L1_1: RUNNING to station 2_1 of L1 to UP\n"
                          "246 => Train L1_1: STOP in station 2_1 of L1 to UP\n"
                          "300 => Train L1_2: START in station 1 of L1 to UP\n"
                          "300 => Train L1_2: RUNNING to station 2_1 of L1 to UP\n"
                          "366 => Train L1_1: RUNNING to station 3 of L1 to UP\n"
                          "546 => Train L1_2: STOP in station 2_1 of L1 to UP\n"
                          "576 => Train L1_1: STOP in station 3 of L1 to UP\n"
                          "600 => Train L1_3: START in station 1 of L1 to UP\n"
                          "600 => Train L1_3: RUNNING to station 2_1 of L1 to UP\n"
                          "666 => Train L1_2: RUNNING to station 3 of L1 to UP\n"
                          "696 => Train L1_1: RUNNING to station 4 of L1 to UP\n"
                          "846 => Train L1_3: STOP in station 2_1 of L1 to UP\n"
                          "876 => Train L1_2: STOP in station 3 of L1 to UP\n"
                          "900 => Train L1_4: START in station 1 of L1 to UP\n"
                          "900 => Train L1_4: RUNNING to station 2_1 of L1 to UP\n"
                          "948 => Train L1_1: STOP in station 4 of L1 to UP\n"
                          "966 => Train L1_3: RUNNING to station 3 of L1 to UP\n"
                          "996 => Train L1_2: RUNNING to station 4 of L1 to UP\n"
                          "1068 => Train L1_1: RUNNING to station 5_1 of L1 to UP\n"
                          "1146 => Train L1_4: STOP in station 2_1 of L1 to UP\n"
                          "1176 => Train L1_3: STOP in station 3 of L1 to UP\n"
                          "1200 => Train L1_5: START in station 1 of L1 to UP\n"
                          "1200 => Train L1_5: RUNNING to station 2_1 of L1 to UP\n"
                          "1248 => Train L1_2: STOP in station 4 of L1 to UP\n"
                          "1260 => Train L1_1: STOP in station 5_1 of L1 to UP\n"
                          "1266 => Train L1_4: RUNNING to station 3 of L1 to UP\n"
                          "1296 => Train L1_3: RUNNING to station 4 of L1 to UP\n"
                          "1368 => Train L1_2: RUNNING to station 5_1 of L1 to UP\n"
                          "1380 => Train L1_1: RUNNING to station 6 of L1 to UP\n"
                          "1446 => Train L1_5: STOP in station 2_1 of L1 to UP\n"
                          "1476 => Train L1_4: STOP in station 3 of L1 to UP\n"
                          "1500 => Train L1_6: START in station 1 of L1 to UP\n"
                          "1500 => Train L1_6: RUNNING to station 2_1 of L1 to UP\n"
                          "1548 => Train L1_3: STOP in station 4 of L1 to UP\n"
                          "1560 => Train L1_2: STOP in station 5_1 of L1 to UP\n"
                          "1566 => Train L1_5: RUNNING to station 3 of L1 to UP\n"
                          "1596 => Train L1_4: RUNNING to station 4 of L1 to UP\n"
                          "1668 => Train L1_3: RUNNING to station 5_1 of L1 to UP\n"
                          "1680 => Train L1_1: STOP in station 6 of L1 to UP\n"
                          "1680 => Train L1_2: RUNNING to station 6 of L1 to UP\n"
                          "1746 => Train L1_6: STOP in station 2_1 of L1 to UP\n"
                          "1776 => Train L1_5: STOP in station 3 of L1 to UP\n"
                          "1800 => Train L1_1: FLIP in station 6 of L1 to DOWN\n"
                          "1800 => Train L1_7: START in station 1 of L1 to UP\n"
                          "1800 => Train L1_7: RUNNING to station 2_1 of L1 to UP\n"
                          "1848 => Train L1_4: STOP in station 4 of L1 to UP\n"
                          "1860 => Train L1_3: STOP in station 5_1 of L1 to UP\n"
                          "1866 => Train L1_6: RUNNING to station 3 of L1 to UP\n"
                          "1896 => Train L1_5: RUNNING to station 4 of L1 to UP\n"
                          "1968 => Train L1_4: RUNNING to station 5_1 of L1 to UP\n"
                          "1980 => Train L1_2: STOP in station 6 of L1 to UP\n"
                          "1980 => Train L1_3: RUNNING to station 6 of L1 to UP\n"
                          "2040 => Train L1_1: STOP in station 6 of L1 to DOWN\n"
                          "2046 => Train L1_7: STOP in station 2_1 of L1 to UP\n"
                          "2076 => Train L1_6: STOP in station 3 of L1 to UP\n"
                          "2100 => Train L1_2: FLIP in station 6 of L1 to DOWN\n"
                          "2100 => Train L1_8: START in station 1 of L1 to UP\n"
                          "2100 => Train L1_8: RUNNING to station 2_1 of L1 to UP\n"
                          "2148 => Train L1_5: STOP in station 4 of L1 to UP\n"
                          "2160 => Train L1_1: RUNNING to station 5_1 of L1 to DOWN\n"
                          "2160 => Train L1_4: STOP in station 5_1 of L1 to UP\n"
                          "2166 => Train L1_7: RUNNING to station 3 of L1 to UP\n"
                          "2196 => Train L1_6: RUNNING to station 4 of L1 to UP\n"
                          "2268 => Train L1_5: RUNNING to station 5_1 of L1 to UP\n"
                          "2280 => Train L1_3: STOP in station 6 of L1 to UP\n"
                          "2280 => Train L1_4: RUNNING to station 6 of L1 to UP\n"
                          "2340 => Train L1_2: STOP in station 6 of L1 to DOWN\n"
                          "2346 => Train L1_8: STOP in station 2_1 of L1 to UP\n"
                          "2376 => Train L1_7: STOP in station 3 of L1 to UP\n"
                          "2400 => Train L1_3: FLIP in station 6 of L1 to DOWN\n"
                          "2448 => Train L1_6: STOP in station 4 of L1 to UP\n"
                          "2460 => Train L1_1: STOP in station 5_1 of L1 to DOWN\n"
                          "2460 => Train L1_2: RUNNING to station 5_1 of L1 to DOWN\n"
                          "2460 => Train L1_5: STOP in station 5_1 of L1 to UP\n"
                          "2466 => Train L1_8: RUNNING to station 3 of L1 to UP\n"
                          "2496 => Train L1_7: RUNNING to station 4 of L1 to UP\n"
                          "2568 => Train L1_6: RUNNING to station 5_1 of L1 to UP\n"
                          "2580 => Train L1_1: RUNNING to station 4 of L1 to DOWN\n"
                          "2580 => Train L1_4: STOP in station 6 of L1 to UP\n"
                          "2580 => Train L1_5: RUNNING to station 6 of L1 to UP\n"
                          "2640 => Train L1_3: STOP in station 6 of L1 to DOWN\n"
                          "2676 => Train L1_8: STOP in station 3 of L1 to UP\n"
                          "2700 => Train L1_4: FLIP in station 6 of L1 to DOWN\n"
                          "2748 => Train L1_7: STOP in station 4 of L1 to UP\n"
                          "2760 => Train L1_2: STOP in station 5_1 of L1 to DOWN\n"
                          "2760 => Train L1_3: RUNNING to station 5_1 of L1 to DOWN\n"
                          "2760 => Train L1_6: STOP in station 5_1 of L1 to UP\n"
                          "2772 => Train L1_1: STOP in station 4 of L1 to DOWN\n"
                          "2796 => Train L1_8: RUNNING to station 4 of L1 to UP\n"
                          "2868 => Train L1_7: RUNNING to station 5_1 of L1 to UP\n"
                          "2880 => Train L1_2: RUNNING to station 4 of L1 to DOWN\n"
                          "2880 => Train L1_5: STOP in station 6 of L1 to UP\n"
                          "2880 => Train L1_6: RUNNING to station 6 of L1 to UP\n"
                          "2892 => Train L1_1: RUNNING to station 3 of L1 to DOWN\n"
                          "2940 => Train L1_4: STOP in station 6 of L1 to DOWN\n"
                          "3000 => Train L1_5: FLIP in station 6 of L1 to DOWN\n"
                          "3048 => Train L1_8: STOP in station 4 of L1 to UP\n"
                          "3060 => Train L1_3: STOP in station 5_1 of L1 to DOWN\n"
                          "3060 => Train L1_4: RUNNING to station 5_1 of L1 to DOWN\n"
                          "3060 => Train L1_7: STOP in station 5_1 of L1 to UP\n"
                          "3072 => Train L1_2: STOP in station 4 of L1 to DOWN\n"
                          "3144 => Train L1_1: STOP in station 3 of L1 to DOWN\n"
                          "3168 => Train L1_8: RUNNING to station 5_1 of L1 to UP\n"
                          "3180 => Train L1_3: RUNNING to station 4 of L1 to DOWN\n"
                          "3180 => Train L1_6: STOP in station 6 of L1 to UP\n"
                          "3180 => Train L1_7: RUNNING to station 6 of L1 to UP\n"
                          "3192 => Train L1_2: RUNNING to station 3 of L1 to DOWN\n"
                          "3240 => Train L1_5: STOP in station 6 of L1 to DOWN\n"
                          "3264 => Train L1_1: RUNNING to station 2_1 of L1 to DOWN\n"
                          "3300 => Train L1_6: FLIP in station 6 of L1 to DOWN\n"
                          "3360 => Train L1_4: STOP in station 5_1 of L1 to DOWN\n"
                          "3360 => Train L1_5: RUNNING to station 5_1 of L1 to DOWN\n"
                          "3360 => Train L1_8: STOP in station 5_1 of L1 to UP\n"
                          "3372 => Train L1_3: STOP in station 4 of L1 to DOWN\n"
                          "3444 => Train L1_2: STOP in station 3 of L1 to DOWN\n"
                          "3474 => Train L1_1: STOP in station 2_1 of L1 to DOWN\n"
                          "3480 => Train L1_4: RUNNING to station 4 of L1 to DOWN\n"
                          "3480 => Train L1_7: STOP in station 6 of L1 to UP\n"
                          "3480 => Train L1_8: RUNNING to station 6 of L1 to UP\n"
                          "3492 => Train L1_3: RUNNING to station 3 of L1 to DOWN\n"
                          "3540 => Train L1_6: STOP in station 6 of L1 to DOWN\n"
                          "3564 => Train L1_2: RUNNING to station 2_1 of L1 to DOWN\n"
                          "3594 => Train L1_1: RUNNING to station 1 of L1 to DOWN\n"
                          "3600 => Train L1_7: FLIP in station 6 of L1 to DOWN\n"
                          "3660 => Train L1_5: STOP in station 5_1 of L1 to DOWN\n"
                          "3660 => Train L1_6: RUNNING to station 5_1 of L1 to DOWN\n"
                          "3672 => Train L1_4: STOP in station 4 of L1 to DOWN\n"
                          "3744 => Train L1_3: STOP in station 3 of L1 to DOWN\n"
                          "3774 => Train L1_2: STOP in station 2_1 of L1 to DOWN\n"
                          "3780 => Train L1_5: RUNNING to station 4 of L1 to DOWN\n"
                          "3780 => Train L1_8: STOP in station 6 of L1 to UP\n"
                          "3792 => Train L1_4: RUNNING to station 3 of L1 to DOWN\n"
                          "3840 => Train L1_1: STOP in station 1 of L1 to DOWN\n"
                          "3840 => Train L1_7: STOP in station 6 of L1 to DOWN\n"
                          "3864 => Train L1_3: RUNNING to station 2_1 of L1 to DOWN\n"
                          "3894 => Train L1_2: RUNNING to station 1 of L1 to DOWN\n"
                          "3900 => Train L1_8: FLIP in station 6 of L1 to DOWN\n"
                          "3960 => Train L1_1: FLIP in station 1 of L1 to UP\n"
                          "3960 => Train L1_6: STOP in station 5_1 of L1 to DOWN\n"
                          "3960 => Train L1_7: RUNNING to station 5_1 of L1 to DOWN\n"
                          "3972 => Train L1_5: STOP in station 4 of L1 to DOWN\n"
                          "4044 => Train L1_4: STOP in station 3 of L1 to DOWN\n"
                          "4074 => Train L1_3: STOP in station 2_1 of L1 to DOWN\n"
                          "4080 => Train L1_6: RUNNING to station 4 of L1 to DOWN\n"
                          "4092 => Train L1_5: RUNNING to station 3 of L1 to DOWN\n"
                          "4140 => Train L1_2: STOP in station 1 of L1 to DOWN\n"
                          "4140 => Train L1_8: STOP in station 6 of L1 to DOWN\n"
                          "4164 => Train L1_4: RUNNING to station 2_1 of L1 to DOWN\n"
                          "4194 => Train L1_3: RUNNING to station 1 of L1 to DOWN\n"
                          "4200 => Train L1_1: STOP in station 1 of L1 to UP\n"
                          "4260 => Train L1_2: FLIP in station 1 of L1 to UP\n"
                          "4260 => Train L1_7: STOP in station 5_1 of L1 to DOWN\n"
                          "4260 => Train L1_8: RUNNING to station 5_1 of L1 to DOWN\n"
                          "4272 => Train L1_6: STOP in station 4 of L1 to DOWN\n"
                          "4320 => Train L1_1: RUNNING to station 2_1 of L1 to UP\n"
                          "4344 => Train L1_5: STOP in station 3 of L1 to DOWN\n"
                          "4374 => Train L1_4: STOP in station 2_1 of L1 to DOWN\n"
                          "4380 => Train L1_7: RUNNING to station 4 of L1 to DOWN\n"
                          "4392 => Train L1_6: RUNNING to station 3 of L1 to DOWN\n"
                          "4440 => Train L1_3: STOP in station 1 of L1 to DOWN\n"
                          "4464 => Train L1_5: RUNNING to station 2_1 of L1 to DOWN\n"
                          "4494 => Train L1_4: RUNNING to station 1 of L1 to DOWN\n"
                          "4500 => Train L1_2: STOP in station 1 of L1 to UP\n"
                          "4560 => Train L1_3: FLIP in station 1 of L1 to UP\n"
                          "4560 => Train L1_8: STOP in station 5_1 of L1 to DOWN\n"
                          "4566 => Train L1_1: STOP in station 2_1 of L1 to UP\n"
                          "4572 => Train L1_7: STOP in station 4 of L1 to DOWN\n"
                          "4620 => Train L1_2: RUNNING to station 2_1 of L1 to UP\n"
                          "4644 => Train L1_6: STOP in station 3 of L1 to DOWN\n"
                          "4674 => Train L1_5: STOP in station 2_1 of L1 to DOWN\n"
                          "4680 => Train L1_8: RUNNING to station 4 of L1 to DOWN\n"
                          "4686 => Train L1_1: RUNNING to station 3 of L1 to UP\n"
                          "4692 => Train L1_7: RUNNING to station 3 of L1 to DOWN\n"
                          "4740 => Train L1_4: STOP in station 1 of L1 to DOWN\n"
                          "4764 => Train L1_6: RUNNING to station 2_1 of L1 to DOWN\n"
                          "4794 => Train L1_5: RUNNING to station 1 of L1 to DOWN\n"
                          "4800 => Train L1_3: STOP in station 1 of L1 to UP\n"
                          "4860 => Train L1_4: FLIP in station 1 of L1 to UP\n"
                          "4866 => Train L1_2: STOP in station 2_1 of L1 to UP\n"
                          "4872 => Train L1_8: STOP in station 4 of L1 to DOWN\n"
                          "4896 => Train L1_1: STOP in station 3 of L1 to UP\n"
                          "4920 => Train L1_3: RUNNING to station 2_1 of L1 to UP\n"
                          "4944 => Train L1_7: STOP in station 3 of L1 to DOWN\n"
                          "4974 => Train L1_6: STOP in station 2_1 of L1 to DOWN\n"
                          "4986 => Train L1_2: RUNNING to station 3 of L1 to UP\n"
                          "4992 => Train L1_8: RUNNING to station 3 of L1 to DOWN\n"
                          "5016 => Train L1_1: RUNNING to station 4 of L1 to UP\n"
                          "5040 => Train L1_5: STOP in station 1 of L1 to DOWN\n"
                          "5064 => Train L1_7: RUNNING to station 2_1 of L1 to DOWN\n"
                          "5094 => Train L1_6: RUNNING to station 1 of L1 to DOWN\n"
                          "5100 => Train L1_4: STOP in station 1 of L1 to UP\n"
                          "5160 => Train L1_5: FLIP in station 1 of L1 to UP\n"
                          "5166 => Train L1_3: STOP in station 2_1 of L1 to UP\n"
                          "5196 => Train L1_2: STOP in station 3 of L1 to UP\n"
                          "5220 => Train L1_4: RUNNING to station 2_1 of L1 to UP\n"
                          "5244 => Train L1_8: STOP in station 3 of L1 to DOWN\n"
                          "5268 => Train L1_1: STOP in station 4 of L1 to UP\n"
                          "5274 => Train L1_7: STOP in station 2_1 of L1 to DOWN\n"
                          "5286 => Train L1_3: RUNNING to station 3 of L1 to UP\n"
                          "5316 => Train L1_2: RUNNING to station 4 of L1 to UP\n"
                          "5340 => Train L1_6: STOP in station 1 of L1 to DOWN\n"
                          "5364 => Train L1_8: RUNNING to station 2_1 of L1 to DOWN\n"
                          "5388 => Train L1_1: RUNNING to station 5_1 of L1 to UP\n"
                          "5394 => Train L1_7: RUNNING to station 1 of L1 to DOWN\n"
                          "5400 => Train L1_5: STOP in station 1 of L1 to UP\n"
                          "5460 => Train L1_6: FLIP in station 1 of L1 to UP\n"
                          "5466 => Train L1_4: STOP in station 2_1 of L1 to UP\n"
                          "5496 => Train L1_3: STOP in station 3 of L1 to UP\n"
                          "5520 => Train L1_5: RUNNING to station 2_1 of L1 to UP\n"
                          "5568 => Train L1_2: STOP in station 4 of L1 to UP\n"
                          "5574 => Train L1_8: STOP in station 2_1 of L1 to DOWN\n"
                          "5580 => Train L1_1: STOP in station 5_1 of L1 to UP\n"
                          "5586 => Train L1_4: RUNNING to station 3 of L1 to UP\n"
                          "5616 => Train L1_3: RUNNING to station 4 of L1 to UP\n"
                          "5640 => Train L1_7: STOP in station 1 of L1 to DOWN\n"
                          "5688 => Train L1_2: RUNNING to station 5_1 of L1 to UP\n"
                          "5694 => Train L1_8: RUNNING to station 1 of L1 to DOWN\n"
                          "5700 => Train L1_1: RUNNING to station 6 of L1 to UP\n"
                          "5700 => Train L1_6: STOP in station 1 of L1 to UP\n"
                          "5760 => Train L1_7: FLIP in station 1 of L1 to UP\n"
                          "5766 => Train L1_5: STOP in station 2_1 of L1 to UP\n"
                          "5796 => Train L1_4: STOP in station 3 of L1 to UP\n"
                          "5820 => Train L1_6: RUNNING to station 2_1 of L1 to UP\n"
                          "5868 => Train L1_3: STOP in station 4 of L1 to UP\n"
                          "5880 => Train L1_2: STOP in station 5_1 of L1 to UP\n"
                          "5886 => Train L1_5: RUNNING to station 3 of L1 to UP\n"
                          "5916 => Train L1_4: RUNNING to station 4 of L1 to UP\n"
                          "5940 => Train L1_8: STOP in station 1 of L1 to DOWN\n"
                          "5988 => Train L1_3: RUNNING to station 5_1 of L1 to UP\n"
                          "6000 => Train L1_1: STOP in station 6 of L1 to UP\n"
                          "6000 => Train L1_2: RUNNING to station 6 of L1 to UP\n"
                          "6000 => Train L1_7: STOP in station 1 of L1 to UP\n"
                          "6060 => Train L1_8: FLIP in station 1 of L1 to UP\n"
                          "6066 => Train L1_6: STOP in station 2_1 of L1 to UP\n"
                          "6096 => Train L1_5: STOP in station 3 of L1 to UP\n"
                          "6120 => Train L1_1: FLIP in station 6 of L1 to DOWN\n"
                          "6120 => Train L1_7: RUNNING to station 2_1 of L1 to UP\n"
                          "6168 => Train L1_4: STOP in station 4 of L1 to UP\n"
                          "6180 => Train L1_3: STOP in station 5_1 of L1 to UP\n"
                          "6186 => Train L1_6: RUNNING to station 3 of L1 to UP\n"
                          "6216 => Train L1_5: RUNNING to station 4 of L1 to UP\n"
                          "6288 => Train L1_4: RUNNING to station 5_1 of L1 to UP\n"
                          "6300 => Train L1_2: STOP in station 6 of L1 to UP\n"
                          "6300 => Train L1_3: RUNNING to station 6 of L1 to UP\n"
                          "6300 => Train L1_8: STOP in station 1 of L1 to UP\n"
                          "6360 => Train L1_1: STOP in station 6 of L1 to DOWN\n"
                          "6366 => Train L1_7: STOP in station 2_1 of L1 to UP\n"
                          "6396 => Train L1_6: STOP in station 3 of L1 to UP\n"
                          "6420 => Train L1_2: FLIP in station 6 of L1 to DOWN\n"
                          "6420 => Train L1_8: RUNNING to station 2_1 of L1 to UP\n"
                          "6468 => Train L1_5: STOP in station 4 of L1 to UP\n"
                          "6480 => Train L1_1: RUNNING to station 5_1 of L1 to DOWN\n"
                          "6480 => Train L1_4: STOP in station 5_1 of L1 to UP\n"
                          "6486 => Train L1_7: RUNNING to station 3 of L1 to UP\n"
                          "6516 => Train L1_6: RUNNING to station 4 of L1 to UP\n"
                          "6588 => Train L1_5: RUNNING to station 5_1 of L1 to UP\n"
                          "6600 => Train L1_3: STOP in station 6 of L1 to UP\n"
                          "6600 => Train L1_4: RUNNING to station 6 of L1 to UP\n"
                          "6660 => Train L1_2: STOP in station 6 of L1 to DOWN\n"
                          "6666 => Train L1_8: STOP in station 2_1 of L1 to UP\n"
                          "6696 => Train L1_7: STOP in station 3 of L1 to UP\n"
                          "6720 => Train L1_3: FLIP in station 6 of L1 to DOWN\n"
                          "6768 => Train L1_6: STOP in station 4 of L1 to UP\n"
                          "6780 => Train L1_1: STOP in station 5_1 of L1 to DOWN\n"
                          "6780 => Train L1_2: RUNNING to station 5_1 of L1 to DOWN\n"
                          "6780 => Train L1_5: STOP in station 5_1 of L1 to UP\n"
                          "6786 => Train L1_8: RUNNING to station 3 of L1 to UP\n"
                          "6816 => Train L1_7: RUNNING to station 4 of L1 to UP\n"
                          "6888 => Train L1_6: RUNNING to station 5_1 of L1 to UP\n"
                          "6900 => Train L1_1: RUNNING to station 4 of L1 to DOWN\n"
                          "6900 => Train L1_4: STOP in station 6 of L1 to UP\n"
                          "6900 => Train L1_5: RUNNING to station 6 of L1 to UP\n"
                          "6960 => Train L1_3: STOP in station 6 of L1 to DOWN\n"
                          "6996 => Train L1_8: STOP in station 3 of L1 to UP\n"
                          "7020 => Train L1_4: FLIP in station 6 of L1 to DOWN\n"
                          "7068 => Train L1_7: STOP in station 4 of L1 to UP\n"
                          "7080 => Train L1_2: STOP in station 5_1 of L1 to DOWN\n"
                          "7080 => Train L1_3: RUNNING to station 5_1 of L1 to DOWN\n"
                          "7080 => Train L1_6: STOP in station 5_1 of L1 to UP\n"
                          "7092 => Train L1_1: STOP in station 4 of L1 to DOWN\n"
                          "7116 => Train L1_8: RUNNING to station 4 of L1 to UP\n"
                          "7188 => Train L1_7: RUNNING to station 5_1 of L1 to UP\n"
                          "7200 => Train L1_2: RUNNING to station 4 of L1 to DOWN\n"
                          "7200 => Train L1_5: STOP in station 6 of L1 to UP\n"
                          "7200 => Train L1_6: RUNNING to station 6 of L1 to UP\n"
                          "7212 => Train L1_1: RUNNING to station 3 of L1 to DOWN\n"
                          "7260 => Train L1_4: STOP in station 6 of L1 to DOWN\n"
                          "7320 => Train L1_5: FLIP in station 6 of L1 to DOWN\n"
                          "7368 => Train L1_8: STOP in station 4 of L1 to UP\n"
                          "7380 => Train L1_3: STOP in station 5_1 of L1 to DOWN\n"
                          "7380 => Train L1_4: RUNNING to station 5_1 of L1 to DOWN\n"
                          "7380 => Train L1_7: STOP in station 5_1 of L1 to UP\n"
                          "7392 => Train L1_2: STOP in station 4 of L1 to DOWN\n"
                          "7464 => Train L1_1: STOP in station 3 of L1 to DOWN\n"
                          "7488 => Train L1_8: RUNNING to station 5_1 of L1 to UP\n"
                          "7500 => Train L1_3: RUNNING to station 4 of L1 to DOWN\n"
                          "7500 => Train L1_6: STOP in station 6 of L1 to UP\n"
                          "7500 => Train L1_7: RUNNING to station 6 of L1 to UP\n"
                          "7512 => Train L1_2: RUNNING to station 3 of L1 to DOWN\n"
                          "7560 => Train L1_5: STOP in station 6 of L1 to DOWN\n"
                          "7584 => Train L1_1: RUNNING to station 2_1 of L1 to DOWN\n"
                          "7620 => Train L1_6: FLIP in station 6 of L1 to DOWN\n"
                          "7680 => Train L1_4: STOP in station 5_1 of L1 to DOWN\n"
                          "7680 => Train L1_5: RUNNING to station 5_1 of L1 to DOWN\n"
                          "7680 => Train L1_8: STOP in station 5_1 of L1 to UP\n"
                          "7692 => Train L1_3: STOP in station 4 of L1 to DOWN\n"
                          "7764 => Train L1_2: STOP in station 3 of L1 to DOWN\n"
                          "7794 => Train L1_1: STOP in station 2_1 of L1 to DOWN\n"
                          "7800 => Train L1_4: RUNNING to station 4 of L1 to DOWN\n"
                          "7800 => Train L1_7: STOP in station 6 of L1 to UP\n"
                          "7800 => Train L1_8: RUNNING to station 6 of L1 to UP\n"
                          "7812 => Train L1_3: RUNNING to station 3 of L1 to DOWN\n"
                          "7860 => Train L1_6: STOP in station 6 of L1 to DOWN\n"
                          "7884 => Train L1_2: RUNNING to station 2_1 of L1 to DOWN\n"
                          "7914 => Train L1_1: RUNNING to station 1 of L1 to DOWN\n"
                          "7920 => Train L1_7: FLIP in station 6 of L1 to DOWN\n"
                          "7980 => Train L1_5: STOP in station 5_1 of L1 to DOWN\n"
                          "7980 => Train L1_6: RUNNING to station 5_1 of L1 to DOWN\n"
                          "7992 => Train L1_4: STOP in station 4 of L1 to DOWN\n"
                          "8064 => Train L1_3: STOP in station 3 of L1 to DOWN\n"
                          "8094 => Train L1_2: STOP in station 2_1 of L1 to DOWN\n"
                          "8100 => Train L1_5: RUNNING to station 4 of L1 to DOWN\n"
                          "8100 => Train L1_8: STOP in station 6 of L1 to UP\n"
                          "8112 => Train L1_4: RUNNING to station 3 of L1 to DOWN\n"
                          "8160 => Train L1_1: STOP in station 1 of L1 to DOWN\n"
                          "8160 => Train L1_7: STOP in station 6 of L1 to DOWN\n"
                          "8184 => Train L1_3: RUNNING to station 2_1 of L1 to DOWN\n"
                          "8214 => Train L1_2: RUNNING to station 1 of L1 to DOWN\n"
                          "8220 => Train L1_8: FLIP in station 6 of L1 to DOWN\n"
                          "8280 => Train L1_1: FLIP in station 1 of L1 to UP\n"
                          "8280 => Train L1_6: STOP in station 5_1 of L1 to DOWN\n"
                          "8280 => Train L1_7: RUNNING to station 5_1 of L1 to DOWN\n"
                          "8292 => Train L1_5: STOP in station 4 of L1 to DOWN\n"
                          "8364 => Train L1_4: STOP in station 3 of L1 to DOWN\n"
                          "8394 => Train L1_3: STOP in station 2_1 of L1 to DOWN\n"
                          "8400 => Train L1_6: RUNNING to station 4 of L1 to DOWN\n"
                          "8412 => Train L1_5: RUNNING to station 3 of L1 to DOWN\n"
                          "8460 => Train L1_2: STOP in station 1 of L1 to DOWN\n"
                          "8460 => Train L1_8: STOP in station 6 of L1 to DOWN\n"
                          "8484 => Train L1_4: RUNNING to station 2_1 of L1 to DOWN\n"
                          "8514 => Train L1_3: RUNNING to station 1 of L1 to DOWN\n"
                          "8520 => Train L1_1: STOP in station 1 of L1 to UP\n"
                          "8580 => Train L1_2: FLIP in station 1 of L1 to UP\n"
                          "8580 => Train L1_7: STOP in station 5_1 of L1 to DOWN\n"
                          "8580 => Train L1_8: RUNNING to station 5_1 of L1 to DOWN\n"
                          "8592 => Train L1_6: STOP in station 4 of L1 to DOWN\n"
                          "8640 => Train L1_1: RUNNING to station 2_1 of L1 to UP\n"
                          "8664 => Train L1_5: STOP in station 3 of L1 to DOWN\n"
                          "8694 => Train L1_4: STOP in station 2_1 of L1 to DOWN\n"
                          "8700 => Train L1_7: RUNNING to station 4 of L1 to DOWN\n"
                          "8712 => Train L1_6: RUNNING to station 3 of L1 to DOWN\n"
                          "8760 => Train L1_3: STOP in station 1 of L1 to DOWN\n"
                          "8784 => Train L1_5: RUNNING to station 2_1 of L1 to DOWN\n"
                          "8814 => Train L1_4: RUNNING to station 1 of L1 to DOWN\n"
                          "8820 => Train L1_2: STOP in station 1 of L1 to UP\n"
                          "8880 => Train L1_3: FLIP in station 1 of L1 to UP\n"
                          "8880 => Train L1_8: STOP in station 5_1 of L1 to DOWN\n"
                          "8886 => Train L1_1: STOP in station 2_1 of L1 to UP\n"
                          "8892 => Train L1_7: STOP in station 4 of L1 to DOWN\n"
                          "8940 => Train L1_2: RUNNING to station 2_1 of L1 to UP\n"
                          "8964 => Train L1_6: STOP in station 3 of L1 to DOWN\n"
                          "8994 => Train L1_5: STOP in station 2_1 of L1 to DOWN\n"
                          "9000 => Train L1_8: RUNNING to station 4 of L1 to DOWN\n"
                          "9006 => Train L1_1: RUNNING to station 3 of L1 to UP\n"
                          "9012 => Train L1_7: RUNNING to station 3 of L1 to DOWN\n"
                          "9060 => Train L1_4: STOP in station 1 of L1 to DOWN\n"
                          "9084 => Train L1_6: RUNNING to station 2_1 of L1 to DOWN\n"
                          "9114 => Train L1_5: RUNNING to station 1 of L1 to DOWN\n"
                          "9120 => Train L1_3: STOP in station 1 of L1 to UP\n"
                          "9180 => Train L1_4: FLIP in station 1 of L1 to UP\n"
                          "9186 => Train L1_2: STOP in station 2_1 of L1 to UP\n"
                          "9192 => Train L1_8: STOP in station 4 of L1 to DOWN\n"
                          "9216 => Train L1_1: STOP in station 3 of L1 to UP\n"
                          "9240 => Train L1_3: RUNNING to station 2_1 of L1 to UP\n"
                          "9264 => Train L1_7: STOP in station 3 of L1 to DOWN\n"
                          "9294 => Train L1_6: STOP in station 2_1 of L1 to DOWN\n"
                          "9306 => Train L1_2: RUNNING to station 3 of L1 to UP\n"
                          "9312 => Train L1_8: RUNNING to station 3 of L1 to DOWN\n"
                          "9336 => Train L1_1: RUNNING to station 4 of L1 to UP\n"
                          "9360 => Train L1_5: STOP in station 1 of L1 to DOWN\n"
                          "9384 => Train L1_7: RUNNING to station 2_1 of L1 to DOWN\n"
                          "9414 => Train L1_6: RUNNING to station 1 of L1 to DOWN\n"
                          "9420 => Train L1_4: STOP in station 1 of L1 to UP\n"
                          "9480 => Train L1_5: FLIP in station 1 of L1 to UP\n"
                          "9486 => Train L1_3: STOP in station 2_1 of L1 to UP\n"
                          "9516 => Train L1_2: STOP in station 3 of L1 to UP\n"
                          "9540 => Train L1_4: RUNNING to station 2_1 of L1 to UP\n"
                          "9564 => Train L1_8: STOP in station 3 of L1 to DOWN\n"
                          "9588 => Train L1_1: STOP in station 4 of L1 to UP\n"
                          "9594 => Train L1_7: STOP in station 2_1 of L1 to DOWN\n"
                          "9606 => Train L1_3: RUNNING to station 3 of L1 to UP\n"
                          "9636 => Train L1_2: RUNNING to station 4 of L1 to UP\n"
                          "9660 => Train L1_6: STOP in station 1 of L1 to DOWN\n"
                          "9684 => Train L1_8: RUNNING to station 2_1 of L1 to DOWN\n"
                          "9708 => Train L1_1: RUNNING to station 5_1 of L1 to UP\n"
                          "9714 => Train L1_7: RUNNING to station 1 of L1 to DOWN\n"
                          "9720 => Train L1_5: STOP in station 1 of L1 to UP\n"
                          "9780 => Train L1_6: FLIP in station 1 of L1 to UP\n"
                          "9786 => Train L1_4: STOP in station 2_1 of L1 to UP\n"
                          "9816 => Train L1_3: STOP in station 3 of L1 to UP\n"
                          "9840 => Train L1_5: RUNNING to station 2_1 of L1 to UP\n"
                          "9888 => Train L1_2: STOP in station 4 of L1 to UP\n"
                          "9894 => Train L1_8: STOP in station 2_1 of L1 to DOWN\n"
                          "9900 => Train L1_1: STOP in station 5_1 of L1 to UP\n"
                          "9906 => Train L1_4: RUNNING to station 3 of L1 to UP\n"
                          "9936 => Train L1_3: RUNNING to station 4 of L1 to UP\n"
                          "9960 => Train L1_7: STOP in station 1 of L1 to DOWN\n");

  std::cout.rdbuf(old);

  destroy_trains(line, trains);
  destroy_line(line);
}