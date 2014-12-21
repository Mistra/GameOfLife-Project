#ifndef POSITION_HH
#define POSITION_HH

#include <vector>

enum poles {north,east,south,west};

class position {

public:
  position();
  position(int x, int y);

  operator
  int();

  std::vector<position>
  get_positions_in_range(int distance) const;

  std::vector<position>
  get_close_positions_in_path_to(const position& target) const;

  std::vector<position>
  get_close_positions_not_in_path_to(const position& target) const;

  int x, y;

private:
  bool
  x_is_between(const position& a, const position& c) const;

  bool
  y_is_between(const position& a, const position& c) const;

  position
  get_direction(int) const;

  bool is_ok();
  int base, height;
};

#endif
