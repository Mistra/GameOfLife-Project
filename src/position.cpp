#include "position.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

position::position(){}

position::position(int x, int y):
                   x(x), y(y){}

void
position::set_random() {
  x=(rand()%80);
  y=(rand()%25);
}

position
position::get_close(){
  int x1 = x;
  int y1 = y;
  do {
    x1 = x;
    y1 = y;
    switch(rand()%4){ //0=N, 1=E, 2=S, 3=W
      case 0: y1 = y+1; break;
      case 1: x1 = x+1; break;
      case 2: y1 = y-1; break;
      case 3: x1 = x-1; break;
    }
  }
  while(is_outside(x1, y1));
  return position(x1, y1);
}

bool
position::is_outside(int x, int y){
  if((x<0) or (x>79)) return true;
  if((y<0) or (y>24)) return true;
  return false;
}
