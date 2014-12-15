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

char
entity::get_sign() const{
  return 'e';
}

void
entity::live() {
  spawn();
  for (int i=0; i<life_steps; --life_steps) {
    shift();
    reproduce();
    rest();
  }
  die();
}

/*** PROTECTED ***/

void
entity::spawn() {
  if (r_spawn) {
    do {
      pos.set_random(dre);
      grid->claim(pos);
    }
    while(!is_eatable( grid->get(pos) ) and
      grid->unclaim(pos));
  }
  else {
    position next;
    do {
      next = pos.get_close(dre);
      grid->claim(next);
    }
    while(!is_eatable( grid->get(next) ) and
      grid->unclaim(next));
    pos = next;
  }
  grid->settle(pos, this);
  grid->unclaim(pos);
}

void
entity::shift() {
  position next;
  do {
    next = pos.get_close(dre);
    grid->claim(next);
  }
  while(!is_eatable( grid->get(next) ) and
        grid->unclaim(next)); //not eatable than unclaim

  grid->claim(pos);
  if (!i_was_killed()) grid->shift(pos, next);
  grid->unclaim(pos);
  grid->unclaim(next);
  pos = next;
}

void
entity::rest() {
  u_dice dice(1, 20);
  milliseconds ms(dice(dre)*100);
  sleep_for (ms);
}

void
entity::die() {
  grid->claim(pos);
  if (!i_was_killed())
    grid->settle(pos,nullptr);
  grid->unclaim(pos);
}

/*** HELPERS ***/

bool
entity::i_was_killed() {
  if (grid->get(pos) == nullptr or
    !(*grid->get(pos) == *this) ) {
    life_steps=0;
    return true;
  }
  return false;
}

bool
entity::similars_around(){
  std::vector<position> vec = pos.pos_around();
  for(unsigned i = 0; i < vec.size(); ++i) {
    if(!( grid->get(vec[i]) == nullptr )) {
      if( grid->get(vec[i])->get_sign()  ==
        get_sign() )
        return true;
    }
  }
  return false;
}

bool
entity::is_eatable(entity* other) {
  if (other == nullptr) return true;
  return false;
}

/*** EXTERN ***/

void routine(entity* ent) {
  ent->live();
}
