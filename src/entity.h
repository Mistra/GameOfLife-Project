#ifndef ENTITY_H
#define ENTITY_H

#include <thread>
#include <random>
//#include <vector>

#include "table.h"
#include "position.h"

class table;

class entity{
public:
  entity(table*);
  entity(table*, position);
  virtual ~entity();

  virtual void operator()();
  virtual char get_sign() const =0;
  virtual bool can_eat(entity*);
  virtual bool is_killed();

protected:
  void spawn();
  void shift();
  virtual void reproduce()=0;

  std::vector<position> scan(int sight);
  bool similars_around(int horizon = 1);

  table* grid;
  position pos;
  int life_steps;
  bool heat;
  int fertility;
  int rate; //reproduction rate
private:
  std::default_random_engine dre;
  std::uniform_int_distribution<int> rest_dice, base_dice, height_dice;
};

#endif
