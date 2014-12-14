#ifndef COMMON_H
#define COMMON_H

#include <semaphore.h>
#include <list>
#include "entity.h"

class entity;

class resource{
 public:
  resource();
  ~resource(){}
  void lock(int x, int y);
  void unlock(int x, int y);
  void draw_table();
  std::pair<int,int> get_random_pos(char, entity*);
  bool inside(int, int);
  bool look_around(std::pair<int,int>, char);
  int is_joinable(std::pair<int,int>, char);
  void get_position(std::pair<int,int>, char, entity*);
  bool still_alive(std::pair<int, int>, entity*);
  void switch_position(std::pair<int,int>, std::pair<int,int>, char, entity*);
  void remove_me(int, int);
  char get_sign(int x, int y) const;

 private:
     sem_t sem_table[80][25];
  std::pair<char, entity*> table[80][25];
};

#endif //COMMON_H
