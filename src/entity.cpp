#include <iostream>
//std::cout<<"REPRODUCE!!!!"<<std::endl;
#include <chrono>
#include <thread>
#include <algorithm>

#include "entity.h"
#include "settings.h"

using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

entity::entity(table* grid):
               grid(grid),
               life_steps(30),
               fertility(0),
               rest_dice(100, 2000),
               base_dice(0, settings::get("base") - 1),
               height_dice(0, settings::get("height") - 1){
  unsigned seed = steady_clock::now().time_since_epoch().count();
  dre.seed(seed);
  pos = position(base_dice(dre), height_dice(dre));
  heat = false;
}

entity::entity(table* grid, position p1):
               entity(grid){
  pos = p1;
}

entity::~entity(){
}

void
entity::operator()() {
  spawn();
  for (int i=0; i<life_steps; --life_steps) {
    std::vector<position> places = think();
    shift(places);
    reproduce();
    sleep_for(milliseconds( rest_dice( dre )));
  }
  grid->erase(pos, this);
  sleep_for( milliseconds (1000));//last to be painted
}

/*** PROTECTED ***/

void
entity::spawn() {
  position next;
  std::vector<position> places = pos.get_positions_in_range(1);
  while (true) {
    std::shuffle(std::begin(places), std::end(places), dre);
    next = places[0]; //else
    if ( grid->set(next, this) ) break;
    sleep_for (milliseconds (100));
  }
  pos = next;
}

void
entity::shift(std::vector<position>& places) {
  position next;
  while (true) {
    std::shuffle(std::begin(places), std::end(places), dre);
    next = places[0];
    if(grid->shift(pos, next, this)) break;
    sleep_for (milliseconds (100));
  }
  pos = next;
}
/*** HELPERS ***/

bool
entity::is_killed() {
  if (grid->get(pos) != this){
    life_steps = 0;
    return true;
  }
  else return false;
}

std::vector<position>
entity::find_in_range(int range, char sign) {
  for (int dept=1; dept<sight; ++dept){
    std::vector<position> places = pos.get_positions_in_range(dept);
    for(unsigned i = 0; i < places.size(); ++i) {
      if(grid->get(places[i]) != nullptr and
         grid->get(places[i])->get_sign() == sign ){
         return pos.get_close_positions_in_path_to(places[i]);
      }
    }
  }
  return std::vector<position>();
}

bool
entity::can_eat(entity* other) {
  if (other == nullptr) return true;
  return false;
}
