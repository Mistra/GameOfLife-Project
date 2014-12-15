#ifndef TABLE_H
#define TABLE_H

#include <mutex>
#include "position.h"

class entity;

class table{
public:
  table();
  ~table(){}
  bool claim(position);
  bool unclaim(position);
  entity* get(int x, int y) const;
  entity* get(position) const;
  void settle(position, entity*);
  void shift(position one, position two);

private:
  std::mutex mu_grid[80][25];
  entity* grid[80][25];
};

#endif //COMMON_H
