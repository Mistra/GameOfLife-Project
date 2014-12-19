#ifndef TABLE_H
#define TABLE_H

#include <mutex>
#include <vector>
#include "position.h"

class entity;

class table{
public:
  table();
  ~table();

  entity* get(int x, int y) const;
  entity* get(position) const;
  bool set(position, entity*);
  bool shift(position from, position to, entity*);
  bool erase(position, entity*);

private:
  entity** grid;
  std::mutex* mu_grid;
};

#endif //COMMON_H
