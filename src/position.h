#ifndef POSITION_HH
#define POSITION_HH

#include <random>
#include <vector>

typedef int pole;
enum poles {north,east,south,west};

class position {

public:
  position();
  position(int x, int y);

  void set_random(std::default_random_engine &dre);
  position get_direction(pole);
  position get_close(std::default_random_engine &dre);
  std::vector<position> pos_around();

  int x, y;

private:
  bool is_outside();
  std::uniform_int_distribution<int> dice4, dice25, dice80;
};

#endif
