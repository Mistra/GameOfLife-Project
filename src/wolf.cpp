#include "wolf.h"
#include <thread>

wolf::wolf(table* grid):
entity(grid){
}

wolf::wolf(table* grid, position pos):
entity(grid, pos){
}

char
wolf::get_sign() const{
  return 'w';
}

void
wolf::reproduce() {
  ++fertility;
  if (fertility < 15) return;
  if (!similars_around() ) return;
  entity* ent=new wolf(grid, pos); //POS
  std::thread wolf(routine, ent);
  wolf.detach();
  fertility = 0;
}

bool
wolf::is_eatable(entity* other) {
  if (other == nullptr or
      other->get_sign() != get_sign()) return true;
  return false;
}
