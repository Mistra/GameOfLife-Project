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
    shift();
    reproduce();
    sleep_for (milliseconds (rest_dice(dre) ));
  }
  grid->erase(pos, this);
  sleep_for (milliseconds (1000));//last to be painted
}

/*** PROTECTED ***/

void
entity::spawn() {
  position next;
  std::vector<position> places = pos.horizon(1);
  while (true) {
    std::shuffle(std::begin(places), std::end(places), dre);
    //if (r_spawn) next = position(base_dice(dre), height_dice(dre));
    next = places[0]; //else
    if ( grid->set(next, this) ) break;
    sleep_for (milliseconds (100));
  }
  pos = next;
}

void
entity::shift() {
  position next;
  std::vector<position> places = pos.horizon(1);
  while (true) {
    std::shuffle(std::begin(places), std::end(places), dre);
    //next = pos.get_close(dre);
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

bool
entity::similars_around(){
  std::vector<position> places = pos.horizon(1);
  for(unsigned i = 0; i < places.size(); ++i) {
    if(grid->get(places[i]) != nullptr and
       grid->get(places[i])->get_sign() == get_sign() ) {
      return true;
    }
  }
  return false;
}

/*
position
entity::scan(int horizon) {
  for (int i=0; i<4; ++i){
    pos.get_direction(i);
  }
}*/

bool
entity::can_eat(entity* other) {
  if (other == nullptr) return true;
  return false;
}
