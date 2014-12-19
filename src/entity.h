#ifndef ENTITY_H
#define ENTITY_H

#include <thread>

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
  bool is_killed();

protected:
  void spawn();
  void shift();
  virtual void reproduce()=0;
  void rest(int time = 0);
  void die();

  void claim_pos();
  void unclaim_pos();
  bool similars_around();

  table* grid;
  position pos;
  int life_steps;
  int fertility;
  bool r_spawn;
  int rate; //reproduction rate
private:
  std::default_random_engine dre;
};

#endif
