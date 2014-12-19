//#include <iostream>
#include <algorithm>
#include "table.h"
#include "entity.h"
#include "settings.h"

typedef std::lock_guard<std::mutex> guard;

table::table() {
  unsigned const size = settings::get("base") *
                        settings::get("height");
  grid = new entity* [size];
  std::fill_n(grid, size, nullptr);
  mu_grid = new std::mutex[size];
}

table::~table(){
  delete[] grid;
  delete[] mu_grid;
}

entity*
table::get(position pos) const{
  return grid[pos];
}

bool
table::set(position pos, entity* ent) {
  guard locker(mu_grid[pos]);
  if ( ent->can_eat(grid[pos]) ) {
    grid[pos] = ent;
    return true;
  }
  return false;
}

bool
table::shift(position one, position two, entity* ent) {
  int s1 = one;
  int s2 = two;
  if (s1 > s2) std::swap(s1, s2);
  guard locker(mu_grid[s1]);
  guard locker2(mu_grid[s2]);
  if ( ent->is_killed() ) return true;
  if ( grid[one]->can_eat(grid[two]) ) {
    grid[two] = grid[one];
    grid[one] = nullptr;
    return true;
  }
  return false;
}

bool
table::erase(position pos, entity* ent) {
  guard locker(mu_grid[pos]);
  if ( ent->is_killed() ) return true;
  grid[pos] = nullptr;
  return true;
}
