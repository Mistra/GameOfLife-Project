#ifndef ENTITY_H
#define ENTITY_H

#include "table.h"
#include "position.h"

class table;

class entity{
public:
  entity(table*);
//  entity(std::pair<int,int>, resource*);
  ~entity();

  char get_sign() const;
  void live();

protected:
  void spawn();
  bool shift();
  void rest();
  void die();

protected:
  bool is_eatable(entity*);
//  const bool is_outside_box(std::pair<int,int> new_pos) const;
//  const std::pair<int,int> choose_next_pos() const;

private:
  std::default_random_engine dre;
  table* grid;
  position pos;
  int life_steps;
  int fertility;
};

void routine(entity* ent);

#endif
