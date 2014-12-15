#ifndef TABLE_H
#define TABLE_H

#include <semaphore.h>
#include "entity.h"
#include "position.h"

class entity;

class table{
public:
  table();
  ~table(){}
  void claim(position);
  void unclaim(position);
  entity* get(int x, int y) const;
  entity* get(position) const;
  void settle(position, entity*);
  void shift(position one, position two);

private:
  sem_t sem_grid[80][25];
  entity* grid[80][25];
};

#endif //COMMON_H
