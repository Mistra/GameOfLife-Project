//#include <iostream>
#include "table.h"
#include "entity.h"

using namespace std;

table::table(){
  for(int i=0;i<25;++i)
    for(int j=0;j<80;++j)
      grid[j][i]=nullptr;
}

void table::claim(position pos){
  mu_grid[pos.x][pos.y].lock();
}

void table::unclaim(position pos){
  mu_grid[pos.x][pos.y].unlock();
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


/*

bool table::inside(int x, int y){
  if(x<0 or x>79) return false;
  if(y<0 or y>24) return false;
  return true;
}

bool table::look_around(std::pair<int,int> new_pos, char id){
  int x=new_pos.first;
  int y=new_pos.second;
  if(inside(x+1, y) and table[x+1][y].first==id) return true;
  if(inside(x-1, y) and table[x-1][y].first==id) return true;
  if(inside(x, y+1) and table[x][y+1].first==id) return true;
  if(inside(x, y-1) and table[x][y-1].first==id) return true;
  return false;
}

int table::is_joinable(std::pair<int,int> new_pos, char id){
  int x=new_pos.first;
  int y=new_pos.second;
  if (!inside(x,y)) return 0;
  if (table[x][y].first==' ') return 1;
  if (table[x][y].first=='p' and id=='t') return 2;
  return 0;
}

bool table::still_alive(std::pair<int, int> new_pos, entity* p_thread){
  if(table[new_pos.first][new_pos.second].second==p_thread)
    return true;
  return false;
}


void table::get_position(std::pair<int,int> new_pos, char id, entity* p_thread){
  table[new_pos.first][new_pos.second].first=id;
  table[new_pos.first][new_pos.second].second=p_thread;
}

void table::switch_position(std::pair<int,int> position, std::pair<int,int> new_pos, char id, entity* p_thread){
  table[position.first][position.second].first=' ';
  table[position.first][position.second].second=NULL;
  table[new_pos.first][new_pos.second].first=id;
  table[new_pos.first][new_pos.second].second=p_thread;
}

void table::remove_me(int x, int y){
  table[x][y].first=' ';
}

*/
