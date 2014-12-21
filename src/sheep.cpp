#include "sheep.h"
#include <thread>
#include "settings.h"

sheep::sheep(table* grid):
entity(grid){
  life_steps = settings::get("sheep_life");
  rate = settings::get("sheep_rate");
}

sheep::sheep(table* grid, position pos):
entity(grid, pos){
  life_steps = settings::get("sheep_life");
  rate = settings::get("sheep_rate");
}

char
sheep::get_sign() const{
  return 's';
}

std::vector<position>
sheep::think() {
std::vector<position> places = scan(6, 's');
if (places.size()==0)
  places = pos.get_positions_in_range(1);
}

void
sheep::reproduce() {
  ++fertility;
  if (fertility < rate) return;
  if (!similars_around() ) return;

  sheep sp(grid, pos);
  std::thread sheep(sp);
  sheep.detach();
  fertility -= rate;
}
