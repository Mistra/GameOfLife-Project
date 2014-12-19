#include "wolf.h"
#include <thread>
#include "settings.h"

wolf::wolf(table* grid):
entity(grid){
  life_steps = settings::get("wolf_life");
  rate = settings::get("wolf_rate");
}

wolf::wolf(table* grid, position pos):
entity(grid, pos){
  life_steps = settings::get("wolf_life");
  rate = settings::get("wolf_rate");
}

char
wolf::get_sign() const{
  return 'w';
}

void
wolf::reproduce() {
  if (fertility < rate) return;
  if (!similars_around() ) return;

  wolf wf(grid, pos);
  std::thread wolf(wf);
  wolf.detach();
  fertility -= rate;
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
