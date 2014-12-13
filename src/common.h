#ifndef COMMON_H
#define COMMON_H

#include <semaphore.h>
#include <list>
#include "entity.h"

class entity;

void routine(entity* p_this);

class semaphor{
 public:
  semaphor();
  ~semaphor();
  void lock_list();
  void unlock_list();
  void lock(int x, int y);
  void unlock(int x, int y);

 private:
  sem_t list_sem;
  sem_t sem_table[80][25];
};


class resource{
 public:
  resource();
  ~resource(){}
  void draw_table();
  std::pair<int,int> get_random_pos(char, semaphor*, entity*);
  bool inside(int, int);
  bool look_around(std::pair<int,int>, char);
  int is_joinable(std::pair<int,int>, char);
  void get_position(std::pair<int,int>, char, entity*);
  bool still_alive(std::pair<int, int>, entity*);
  void switch_position(std::pair<int,int>, std::pair<int,int>, char, entity*);
  void remove_me(int, int);

 private:
  std::pair<char, entity*> table[80][25];
  std::list<entity*> pthread_list;
};

#endif //COMMON_H
