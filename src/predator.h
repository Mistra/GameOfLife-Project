#ifndef PREDATOR_H
#define PREDATOR_H

#include <utility>
#include "common.h"


class predator{
 public:
  predator(semaphor*, resource*);
  predator(std::pair<int,int>, semaphor*, resource*);
  ~predator();

 protected:
  const bool is_outside_box(std::pair<int,int> new_pos) const;
  const std::pair<int,int> choose_next_pos() const;
  void set();
  void body();

 private:
  const bool is_ok() const; //used for debugging
  std::pair<int,int> position;
  int fertility;
  int life_steps;
  semaphor* my_sem;
  resource* my_res;
};

#endif //PREDATOR_H
