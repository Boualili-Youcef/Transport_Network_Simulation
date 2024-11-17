#ifndef TRANSPORT_CELL_HPP
#define TRANSPORT_CELL_HPP

#include <iostream>
#include <memory>

using namespace std;

template <typename Data>
class Cell
{
private:
  shared_ptr<Data> data;
  shared_ptr<Cell> next;
  shared_ptr<Cell> previous;

public:
  // Ici j'ai utiliser explicite pour eviter d'être invoquées par erreur via une conversion implicite
  // normalement on le fait quand le constructeur a un seul argument mais je pense c'est une bonne pratique
  explicit Cell(const shared_ptr<Data> &data, const shared_ptr<Cell> &previous, const shared_ptr<Cell> &next)
      : data(data), previous(previous), next(next)
  {

    //    cout << "[Cell] constructor" << endl;
  }

  shared_ptr<Data> getData() const
  {
    return data;
  }

  shared_ptr<Cell> getNext() const
  {
    return next;
  }

  shared_ptr<Cell> getPrevious() const
  {
    return previous;
  }

  void setNext(const shared_ptr<Cell> &next)
  {
    this->next = next;
  }

  void setPrevious(const shared_ptr<Cell> &previous)
  {
    this->previous = previous;
  }

  ~Cell()
  {

    //    cout << "[Cell] destructor" << endl;
  }
};

#endif // TRANSPORT_CELL_HPP
