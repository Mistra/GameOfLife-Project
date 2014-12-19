#include "position.h"
#include "settings.h"

enum poles {north,east,south,west};

position::position():
                  base(settings::get("base")),
                  height(settings::get("height")),
                  dice4(0,3),
                  dice25(0,height - 1),
                  dice80(0,base - 1){
}

position::position(int x, int y):
                   position(){
  position::x = x;
  position::y = y;
}

position
position::get_direction(int n) {
  switch(n){
    case north: return position(x, y+1);
    case east: return position(x+1, y);
    case south: return position(x, y-1);
    case west: return position(x-1, y);
    default: throw "polo impossibile";
  }
}

position
position::set_random(std::default_random_engine &dre) {
  x=dice80(dre);
  y=dice25(dre);
  return *this;
}

position
position::get_close(std::default_random_engine &dre){
  position next;
  do next = get_direction(dice4(dre));
  while (!next.is_inside());
  return next;
}

std::vector<position>
position::pos_around() {
  std::vector<position> vec;
  for(int i=0; i<4; ++i) {
    if(get_direction(i).is_inside())
      vec.push_back(get_direction(i));
  }
  return vec;
}

bool
position::is_inside() {
  if( (x<0) or (x > base - 1) or
      (y<0) or (y > height - 1)) return false;
  return true;
}
