#ifndef PAINTER_HH
#define PAINTER_HH

class table;

class painter {
private:
  const table* const grid;
public:
  painter(const table* const grid);
  void show() const;
};

#endif
