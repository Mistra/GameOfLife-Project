#ifndef PAINTER_HH
#define PAINTER_HH

class table;

class painter {
public:
  painter(const table* const grid);
  void show();
  void show_table();
  void show_stats();

protected:

private:
  const table* const grid;
  int n_threads;
  int n_sheeps;
  int n_wolfs;
};

#endif
