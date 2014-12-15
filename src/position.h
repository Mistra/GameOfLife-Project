#ifndef POSITION_HH
#define POSITION_HH

class position {
public:
  position();
  position(int x, int y);

  void set_random();
  position get_close();
  bool is_outside(int x, int y);

  int x, y;
};

#endif
