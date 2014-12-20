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

position
position::get_direction(int n) {
  position next;
  switch(n){
    case north: return position(x, (y+1)%height);
    case east:  return position((x+1)%base, y);
    case south: return position(x, mod(y-1, height));
    case west:  return position(mod(x-1, base), y);
    default: throw "polo impossibile";
  }
}

std::vector<position>
position::horizon(int hrz) {
  std::vector<position> places;
  position next(x, y);
  if (hrz==0) places.push_back(position(x,y));

  for (int i=0; i<hrz; ++i) {//shift to extreme south-west
    next = next.get_direction(south);
    next = next.get_direction(west);
  }

  for(int dir=0; dir<4; ++dir) {
    for(int shift=0; shift<hrz*2; ++shift) {
      next = next.get_direction(dir);
      assert(next.is_ok());
      places.push_back(next);
    }
  }
  return places;
}

bool
position::is_ok() {
  return (x >= 0 and x < base and
          y >= 0 and y < height);
}
