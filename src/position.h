#ifndef POSITION_HH
#define POSITION_HH

#include <vector>

enum poles {north,east,south,west};

class position {

public:
  position();
  position(int x, int y);

  operator int();
  std::vector<position> horizon(int hrz_line);
  int x, y;

private:
  position get_direction(int);
  bool is_ok();

  int base, height;
  bool is_inside();

};

#endif
