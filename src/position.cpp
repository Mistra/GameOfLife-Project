#include "position.h"

position::position():
                  dice4(0,3),
                  dice25(0,24),
                  dice80(0,79){
}

position::position(int x, int y):
                   position(){
  position::x = x;
  position::y = y;
}

position
position::get_direction(pole n) {
  switch(n){
    case north: return position(x, y+1);
    case east: return position(x+1, y);
    case south: return position(x, y-1);
    case west: return position(x-1, y);
    default: throw "polo impossibile";
  }
}

void
position::set_random(std::default_random_engine &dre) {
  x=dice80(dre);
  y=dice25(dre);
}

position
position::get_close(std::default_random_engine &dre){
  position next;
  do next = get_direction(dice4(dre));
  while (next.is_outside());
  return next;
}

std::vector<position>
position::pos_around() {
  std::vector<position> vec;
  for(int i=0; i<4; i++) {
    if(!get_direction(i).is_outside())
      vec.push_back(get_direction(i));
  }
  return vec;
}

bool
position::is_outside() {
  if((x<0) or (x>79)) return true;
  if((y<0) or (y>24)) return true;
  return false;
}
