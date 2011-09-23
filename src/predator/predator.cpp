#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <list>

#include "predator.h"

using namespace std;

predator::predator(semaphor* sem, resource* res) {
  position.first=-1;
  position.second=-1;
  my_res=res;
  my_sem=sem;
  life_steps=40;
  fertility=0;
}

predator::predator(pair<int,int> pos, semaphor* sem, resource* res) {
  my_res=res;
  my_sem=sem;
  position=pos;
  life_steps=40;
  fertility=0;
}

predator::~predator(){
}

const bool predator::is_outside_box(pair<int,int> new_pos) const {
  if((new_pos.first<0) or (new_pos.first>79)) return true;
  if((new_pos.second<0) or (new_pos.second>24)) return true;
  return false;
}

const pair<int,int> 
predator::choose_next_pos() const {
  pair<int, int> new_pos;
  do {
    new_pos=position;
    switch(rand()%4){ //0=N, 1=E, 2=S, 3=W
    case 0: ++new_pos.second; break;
    case 1: ++new_pos.first; break;
    case 2: --new_pos.second; break;
    case 3: --new_pos.first; break;
    }
  }
  while (is_outside_box(new_pos));
  return new_pos;
}
  
void 
predator::set() {
  srand((unsigned)time(NULL));
  if(position.first==-1){
    position=my_res->get_random_pos('t', my_sem, this);
    return;
  }
  pair<int,int> new_pos;
  
  while (true){
    new_pos=choose_next_pos();
    my_sem->lock(new_pos.first, new_pos.second);
    int num=my_res->is_joinable(new_pos, 't');
    if (num==1 or num==2) break;
    else my_sem->unlock(new_pos.first, new_pos.second);
    usleep(rand()%1900001+100000);
  }
  my_res->get_position(new_pos, 't', this);
  position=new_pos;
  my_sem->unlock(new_pos.first, new_pos.second);
}

void 
predator::body() {
  int num=0;
  pair<int,int> new_pos;
  for (int i=0; i<life_steps; ++i) {
    usleep(rand()%1900001+100000);
    while (true){
      new_pos=choose_next_pos();
      my_sem->lock(new_pos.first, new_pos.second);
      num=my_res->is_joinable(new_pos, 't');
      if (num==1 or num==2) break;
      else my_sem->unlock(new_pos.first, new_pos.second);
      usleep(rand()%1900001+100000);
    }
    my_sem->lock(position.first, position.second);
    ////look if you are all right (just for prey)
    my_res->switch_position(position, new_pos, 't', this);
    my_sem->unlock(position.first, position.second);
    position=new_pos;
    
    if (fertility>0 and my_res->look_around(position, 't')) { 
      predator* newborn=new predator(position, my_sem, my_res);
      my_sem->lock_list();
      my_res->track(newborn);
      my_sem->unlock_list();
      newborn->begin();
      --fertility;
      //fertility=0;
    }
    if ((i+1)==life_steps) 
      my_res->remove_me(position.first, position.second);
    my_sem->unlock(position.first, position.second);
    if(num==2)
      ++fertility;
  }
}

const bool 
predator::is_ok() const {
  if (position.first<0 or position.first>79) return false;
  if (position.second<0 or position.second>24) return false;
  return true;
}
