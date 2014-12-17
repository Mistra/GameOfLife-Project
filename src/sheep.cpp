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
  if (fertility < 10) return;
  if (!similars_around() ) return;

  sheep sp(grid);
  std::thread sheep(sp);
  sheep.detach();
  fertility = 0;
}
