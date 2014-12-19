#include <iostream>
//std::cout<<"REPRODUCE!!!!"<<std::endl;
#include <chrono>
#include <thread>

#include "entity.h"

using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
typedef std::uniform_int_distribution<int> u_dice;

entity::entity(table* grid):
               grid(grid),
               life_steps(30),
               fertility(0) {
  unsigned seed = steady_clock::now().time_since_epoch().count();
  dre.seed(seed);
  r_spawn = true;
}

entity::entity(table* grid, position pos):
               entity(grid){
  entity::pos = pos;
  r_spawn = false;
}

entity::~entity(){
}

void
entity::operator()() {
  spawn();
  for (int i=0; i<life_steps; --life_steps) {
    shift();
    reproduce();
    rest();
  }
  die();
  rest(1000);//last to be painted
}

/*** PROTECTED ***/

void
entity::spawn() {
  position next;
  while (true) {
    if (r_spawn) next = pos.set_random(dre);
    else next = pos.get_close(dre);
    if ( grid->set(next, this) ) break;
    rest(100);
  }
  pos = next;
}

void
entity::shift() {
  position next;
  while (true) {
    next = pos.get_close(dre);
    if(grid->shift(pos, next, this)) break;
    rest(100);
  }
  pos = next;
}

void
entity::rest(int ms) {
  if (ms == 0) {
    u_dice dice(100, 2000);
    ms = dice(dre);
  }
  sleep_for (milliseconds(ms));
}

void
entity::die() {
  grid->erase(pos, this);
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
  std::vector<position> vec = pos.pos_around();
  for(unsigned i = 0; i < vec.size(); ++i) {
    if(grid->get(vec[i]) != nullptr and
       grid->get(vec[i])->get_sign() == get_sign() ) {
      return true;
    }
  }
  return false;
}

bool
entity::can_eat(entity* other) {
  if (other == nullptr) return true;
  return false;
}
