#ifndef POSITION_HH
#define POSITION_HH

#include <random>

class position {
public:
  position();
  position(int x, int y);

  void set_random(std::default_random_engine &dre);
  position get_close(std::default_random_engine &dre);
  bool is_outside(int x, int y);

  int x, y;

private:
  std::uniform_int_distribution<int> dice4, dice25, dice80;
};

#endif
