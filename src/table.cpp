//#include <iostream>
#include <algorithm>
#include "table.h"
#include "entity.h"

using namespace std;
table::table(): grid{nullptr}{}

entity*
table::get(position pos) const{
  return grid[pos];
}

bool
table::set(position pos, entity* ent) {
  if ( ent->can_eat(grid[pos]) ) {
    std::unique_lock<mutex> locker(mu_grid[pos]);
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
  std::unique_lock<mutex> locker(mu_grid[s1]);
  std::unique_lock<mutex> locker2(mu_grid[s2]);
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
  std::unique_lock<mutex> locker(mu_grid[pos]);
  if ( ent->is_killed() ) return true;
  grid[pos] = nullptr;
  return true;
}
