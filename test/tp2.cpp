#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "iterator.hpp"
#include "line.hpp"
#include "list.hpp"

TEST_CASE("create list", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  {
    List list;

    REQUIRE(list.first == nullptr);
    REQUIRE(list.last == nullptr);
    REQUIRE(list.size() == 0);
  }
  std::cout.rdbuf(old);
}

TEST_CASE("add train to list", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  {
    Line *line = new Line("L1", 6, 8, 4);

    line->add_station("1", 2, 4.1f);
    line->add_station("2_1", 2, 3.5f);
    line->add_station("3", 2, 4.2f);
    line->add_station("4", 2, 3.2f);
    line->add_station("5_1", 2, 5);
    line->add_station("6", 2, 0);

    Train *train = new Train(line, 0, 0, UP);

    List list;

    list.add_first(train);

    REQUIRE(list.first != nullptr);
    REQUIRE(list.last != nullptr);
    REQUIRE(list.first == list.last);
    REQUIRE(list.size() == 1);
    REQUIRE(list.first->next == nullptr);
    REQUIRE(list.first->previous == nullptr);
    REQUIRE(list.last->next == nullptr);
    REQUIRE(list.last->previous == nullptr);
    REQUIRE(strcmp(list.first->train->id, "L1_1") == 0);

    delete line;
  }
  std::cout.rdbuf(old);
}

TEST_CASE("add two trains to list (add_first)", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  {
    Line *line = new Line("L1", 6, 8, 4);

    line->add_station("1", 2, 4.1f);
    line->add_station("2_1", 2, 3.5f);
    line->add_station("3", 2, 4.2f);
    line->add_station("4", 2, 3.2f);
    line->add_station("5_1", 2, 5);
    line->add_station("6", 2, 0);

    Train *train_1 = new Train(line, 0, 0, UP);
    Train *train_2 = new Train(line, 0, 1, UP);

    List list;

    list.add_first(train_1);
    list.add_first(train_2);

    REQUIRE(list.first != nullptr);
    REQUIRE(list.last != nullptr);
    REQUIRE(list.first != list.last);
    REQUIRE(list.size() == 2);
    REQUIRE(list.first->next == list.last);
    REQUIRE(list.first->previous == nullptr);
    REQUIRE(list.last->next == nullptr);
    REQUIRE(list.last->previous == list.first);
    REQUIRE(strcmp(list.first->train->id, "L1_2") == 0);
    REQUIRE(strcmp(list.first->next->train->id, "L1_1") == 0);

    delete line;
  }
  std::cout.rdbuf(old);
}

TEST_CASE("add two trains to list (add_last)", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  {
    Line *line = new Line("L1", 6, 8, 4);

    line->add_station("1", 2, 4.1f);
    line->add_station("2_1", 2, 3.5f);
    line->add_station("3", 2, 4.2f);
    line->add_station("4", 2, 3.2f);
    line->add_station("5_1", 2, 5);
    line->add_station("6", 2, 0);

    Train *train_1 = new Train(line, 0, 0, UP);
    Train *train_2 = new Train(line, 0, 1, UP);

    List list;

    list.add_last(train_1);
    list.add_last(train_2);

    REQUIRE(list.first != nullptr);
    REQUIRE(list.last != nullptr);
    REQUIRE(list.first != list.last);
    REQUIRE(list.size() == 2);
    REQUIRE(list.first->next == list.last);
    REQUIRE(list.first->previous == nullptr);
    REQUIRE(list.last->next == nullptr);
    REQUIRE(list.last->previous == list.first);
    REQUIRE(strcmp(list.first->train->id, "L1_1") == 0);
    REQUIRE(strcmp(list.first->next->train->id, "L1_2") == 0);

    delete line;
  }
  std::cout.rdbuf(old);
}

TEST_CASE("add/remove three trains to list (add_first)", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  {
    Line *line = new Line("L1", 6, 8, 4);

    line->add_station("1", 2, 4.1f);
    line->add_station("2_1", 2, 3.5f);
    line->add_station("3", 2, 4.2f);
    line->add_station("4", 2, 3.2f);
    line->add_station("5_1", 2, 5);
    line->add_station("6", 2, 0);

    Train* train_1 = new Train(line, 0, 0, UP);
    Train* train_2 = new Train(line, 0, 1, UP);
    Train* train_3 = new Train(line, 0, 2, UP);

    List list;

    list.add_first(train_1);
    list.add_first(train_2);
    list.add_first(train_3);

    list.remove_first();

    REQUIRE(list.first != nullptr);
    REQUIRE(list.last != nullptr);
    REQUIRE(list.first != list.last);
    REQUIRE(list.size() == 2);
    REQUIRE(list.first->next == list.last);
    REQUIRE(list.first->previous == nullptr);
    REQUIRE(list.last->next == nullptr);
    REQUIRE(list.last->previous == list.first);
    REQUIRE(strcmp(list.first->train->id, "L1_2") == 0);
    REQUIRE(strcmp(list.first->next->train->id, "L1_1") == 0);

    list.remove_first();

    REQUIRE(list.first != nullptr);
    REQUIRE(list.last != nullptr);
    REQUIRE(list.first == list.last);
    REQUIRE(list.size() == 1);
    REQUIRE(list.first->next == nullptr);
    REQUIRE(list.first->previous == nullptr);
    REQUIRE(list.last->next == nullptr);
    REQUIRE(list.last->previous == nullptr);
    REQUIRE(strcmp(list.first->train->id, "L1_1") == 0);

    list.remove_first();

    REQUIRE(list.first == nullptr);
    REQUIRE(list.last == nullptr);
    REQUIRE(list.size() == 0);

    delete line;
  }
  std::cout.rdbuf(old);
}

TEST_CASE("iterator - forward", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  {
    Line *line = new Line("L1", 6, 8, 4);

    line->add_station("1", 2, 4.1f);
    line->add_station("2_1", 2, 3.5f);
    line->add_station("3", 2, 4.2f);
    line->add_station("4", 2, 3.2f);
    line->add_station("5_1", 2, 5);
    line->add_station("6", 2, 0);

    Train* train_1 = new Train(line, 0, 0, UP);
    Train* train_2 = new Train(line, 0, 1, UP);

    List list;

    list.add_first(train_1);
    list.add_first(train_2);

    Iterator it(list, true);

    REQUIRE(it.has_more());
    REQUIRE(strcmp(it.current().id, "L1_2") == 0);

    it.next();

    REQUIRE(it.has_more());
    REQUIRE(strcmp(it.current().id, "L1_1") == 0);

    it.next();

    REQUIRE(not it.has_more());

    delete line;
  }
  std::cout.rdbuf(old);
}

TEST_CASE("iterator - backward", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
  {
    Line *line = new Line("L1", 6, 8, 4);

    line->add_station("1", 2, 4.1f);
    line->add_station("2_1", 2, 3.5f);
    line->add_station("3", 2, 4.2f);
    line->add_station("4", 2, 3.2f);
    line->add_station("5_1", 2, 5);
    line->add_station("6", 2, 0);

    Train* train_1 = new Train(line, 0, 0, UP);
    Train* train_2 = new Train(line, 0, 1, UP);

    List list;

    list.add_first(train_1);
    list.add_first(train_2);

    Iterator it(list, false);

    REQUIRE(it.has_more());
    REQUIRE(strcmp(it.current().id, "L1_1") == 0);

    it.next();

    REQUIRE(it.has_more());
    REQUIRE(strcmp(it.current().id, "L1_2") == 0);

    it.next();

    REQUIRE(not it.has_more());

    delete line;
  }
  std::cout.rdbuf(old);
}

// *** Question 2.2 ***

TEST_CASE("create list with display", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  {
    List list;
  }

  REQUIRE(buffer.str() == "[List] - constructor\n"
                          "[List] - destructor\n");

  std::cout.rdbuf(old);
}

TEST_CASE("add train to list with display", "tp2")
{
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  {
    Line *line = new Line("L1", 6, 8, 4);

    line->add_station("1", 2, 4.1f);
    line->add_station("2_1", 2, 3.5f);
    line->add_station("3", 2, 4.2f);
    line->add_station("4", 2, 3.2f);
    line->add_station("5_1", 2, 5);
    line->add_station("6", 2, 0);

    Train* train = new Train(line, 0, 0, UP);

    List list;

    list.add_first(train);

    delete line;
  }

  REQUIRE(buffer.str() == "[List] - constructor\n"
                          "[Line] - constructor\n"
                          "[Train] - constructor - L1_1\n"
                          "[List] - constructor\n"
                          "[Cell] - constructor\n"
                          "[Line] - destructor\n"
                          "[List] - destructor\n"
                          "[Train] - destructor - L1_1\n"
                          "[Cell] - destructor\n"
                          "[List] - destructor\n");

  std::cout.rdbuf(old);
}