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
  //++fertility;
  if (fertility < 1) return;
  if (!similars_around() ) return;

  wolf wf(grid, pos);
  std::thread wolf(wf);
  wolf.detach();
  fertility -= 1;
}

bool
wolf::can_eat(entity* other) {
  if (other == nullptr) return true;
  if (other->get_sign() != get_sign()){
    ++fertility;
    return true;
  }
  return false;
}
