#ifndef TABLE_H
#define TABLE_H

#include <mutex>
#include "position.h"

class entity;

class table{
public:
  table();
  ~table(){}

  entity* get(int x, int y) const;
  entity* get(position) const;
  bool set(position, entity*);
  bool shift(position from, position to);
  bool erase(position);

private:
  entity* grid[2000];
  std::mutex mu_grid[2000];
};

#endif //COMMON_H
