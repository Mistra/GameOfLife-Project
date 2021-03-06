#ifndef POSITION_HH
#define POSITION_HH

#include <random>
#include <vector>

class position {

public:
  position();
  position(int x, int y);

  operator int() { return x+y*80; }

  position set_random(std::default_random_engine &dre);
  position get_direction(int);
  position get_close(std::default_random_engine &dre);
  std::vector<position> pos_around();

  int x, y;

private:
  bool is_inside();
  std::uniform_int_distribution<int> dice4, dice25, dice80;
};

#endif
