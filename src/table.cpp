//#include <iostream>
#include "table.h"
#include "entity.h"

using namespace std;

table::table(){
  for(int i=0;i<25;++i)
    for(int j=0;j<80;++j)
      grid[j][i]=nullptr;
}

bool table::claim(position pos){
  mu_grid[pos.x][pos.y].lock();
  return true;
}

bool table::unclaim(position pos){
  mu_grid[pos.x][pos.y].unlock();
  return true;
}

entity*
table::get(int x, int y) const{
  return grid[x][y];
}

entity*
table::get(position pos) const{
  return grid[pos.x][pos.y];
}

void
table::settle(position pos, entity* ent) {
  grid[pos.x][pos.y] = ent;
}
void
table::shift(position one, position two) {
  grid[two.x][two.y] = grid[one.x][one.y];
  grid[one.x][one.y] = nullptr;
}
