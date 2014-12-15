#include "sheep.h"
#include <thread>

sheep::sheep(table* grid):
entity(grid){
}

sheep::sheep(table* grid, position pos):
entity(grid, pos){
}

char
sheep::get_sign() const{
  return 's';
}

void
sheep::reproduce() {
  ++fertility;
  if (fertility < 15) return;
  if (!similars_around() ) return;
  entity* ent=new sheep(grid, pos); //POS
  std::thread sheep(routine, ent);
  sheep.detach();
  fertility = 0;
}
