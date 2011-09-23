#ifndef COMMON_H
#define COMMON_H

#include <list>
#include <semaphore.h>
#include "../thread/thread.h"

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
  void track(thread*);
  std::pair<int,int> get_random_pos(char, semaphor*, thread*);
  void garbage_collector(semaphor*);
  bool inside(int, int);
  bool look_around(std::pair<int,int>, char);
  int is_joinable(std::pair<int,int>, char);
  void get_position(std::pair<int,int>, char, thread*);
  bool still_alive(std::pair<int, int>, thread*);
  void switch_position(std::pair<int,int>, std::pair<int,int>, char, thread*);
  void remove_me(int, int);
    
 private:
  std::pair<char, thread*> table[80][25];
  std::list<thread*> pthread_list;
};

#endif //COMMON_H
