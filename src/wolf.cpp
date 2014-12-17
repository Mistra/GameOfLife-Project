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
  wolf wf(grid, pos); //POS
  std::thread wolf(wf);
  wolf.detach();
  fertility = 0;
}

bool
wolf::is_eatable(entity* other) {
  if (other == nullptr or
      other->get_sign() != get_sign()) return true;
  return false;
}
