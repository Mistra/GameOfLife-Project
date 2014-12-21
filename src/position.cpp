#include <cassert>

#include "position.h"
#include "settings.h"

int mod(int base, int modulo) {
  assert(modulo > 0);
  while (base < 0) {
    base+=modulo;
  }
  return base%modulo;
}

int absolute(int n) {
  if (n<0) return -n;
  return n;
}

int distance(int x1, int x2, int length) {
  int delta = x2 - x1;
  delta = absolute(delta);
  if (delta < length/2)
    return delta;
  else
    return absolute(delta-length);
}

position::position():
                  x(0), y(0),
                  base(settings::get("base")),
                  height(settings::get("height")){
}

position::position(int x, int y):
                   position(){
  position::x = x;
  position::y = y;
}

position::operator int() {
  return x+y*base;
}

std::vector<position>
position::get_positions_in_range(int distance) const {
  std::vector<position> places;
  position next(x, y);
  if (distance==0) places.push_back(position(x,y));

  for (int i=0; i<distance; ++i) {//shift to extreme south-west
    next = next.get_direction(south);
    next = next.get_direction(west);
  }

  for(int dir=0; dir<4; ++dir) {
    for(int shift=0; shift<distance*2; ++shift) {
      next = next.get_direction(dir);
      assert(next.is_ok());
      places.push_back(next);
    }
  }
  return places;
}

std::vector<position>
position::get_close_positions_in_path_to(const position& target) const {
  std::vector<position> places = this->get_positions_in_range(1);;
  std::vector<position> targets;

  for (unsigned i=0; i<places.size(); ++i) {
    if ( places[i].x_is_between(*this, target) and
         places[i].y_is_between(*this, target) ) {
      targets.push_back(places[i]);
    }
  }
  return targets;
}

std::vector<position>
position::get_close_positions_not_in_path_to(const position& target) const {
  std::vector<position> places = this->get_positions_in_range(1);;
  std::vector<position> targets;

  for (unsigned i=0; i<places.size(); ++i) {
    if ( !places[i].x_is_between(*this, target) and
         !places[i].y_is_between(*this, target) ) {
      targets.push_back(places[i]);
    }
  }
  return targets;
}

///PRIVATE

bool
position::x_is_between(const position& a, const position& c) const {
  const position& b = *this;

  int abx = distance(a.x, b.x, base);
  int bcx = distance(b.x, c.x, base);
  int acx = distance(a.x, c.x, base);
  return (abx+bcx==acx);
}

bool
position::y_is_between(const position& a, const position& c) const {
  const position& b = *this;

  int aby = distance(a.y, b.y, height);
  int bcy = distance(b.y, c.y, height);
  int acy = distance(a.y, c.y, height);
  return (aby+bcy == acy);
}

position
position::get_direction(int n) const {
  int x_dir=0;
  int y_dir=0;
  switch(n){
    case north: ++y_dir; break;
    case east:  ++x_dir; break;
    case south: --y_dir; break;
    case west:  --x_dir; break;
    default: throw "impossible";
  }
  position next(mod(x+x_dir, base), mod(y+y_dir, height));
  assert(next.is_ok());
  return next;
}

bool
position::is_ok() {
  return (x >= 0 and x < base and
          y >= 0 and y < height);
}
