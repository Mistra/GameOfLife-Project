#include <chrono>
#include <thread>

#include "position.h"

/*
#include <cstdlib>
#include <ctime>
#include <unistd.h>
*/

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

void
position::set_random(std::default_random_engine &dre) {
  //x=(rand()%80);
  //y=(rand()%25);
  x=dice80(dre);
  y=dice25(dre);
}

position
position::get_close(std::default_random_engine &dre){
  int x1 = x;
  int y1 = y;
  do {
    x1 = x;
    y1 = y;
    //rand()%4
    switch(dice4(dre)){ //0=N, 1=E, 2=S, 3=W
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
