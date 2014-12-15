#ifndef ENTITY_H
#define ENTITY_H

#include "table.h"
#include "position.h"

class table;

class entity{
public:
  entity(table*);
  entity(table*, position);
  virtual ~entity();

  bool operator==(entity& other) {
    return get_id() == other.get_id();
  }
  virtual char get_sign() const;
  void live();

protected:
  void spawn();
  void shift();
  virtual void reproduce()=0;
  void rest();
  void die();

protected:
  bool i_was_killed();
  bool is_eatable(entity*);
  bool similars_around();

protected:
  std::thread::id get_id() {
    return std::this_thread::get_id();
  }

  std::default_random_engine dre;
  table* grid;
  position pos;
  int life_steps;
  int fertility;
  bool r_spawn;
};

void routine(entity* ent);

#endif
