#ifndef PAINTER_HH
#define PAINTER_HH

class resource;

class painter {
private:
  const resource* const table;
public:
  painter(const resource* const table);
  void show() const;
};

#endif
