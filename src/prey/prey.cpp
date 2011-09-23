#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include "prey.h"

using namespace std;

prey::prey(semaphor* sem, resource* res) {
  position.first=-1;
  position.second=-1;
  my_res=res;
  my_sem=sem;
  life_steps=30;
  fertility=0;
}

prey::prey(pair<int,int> pos, semaphor* sem, resource* res) {
  my_res=res;
  my_sem=sem;
  position=pos;
  life_steps=30;
  fertility=0;
}

prey::~prey(){
}

const bool 
prey::is_outside_box(pair<int,int> new_pos) const {
  if((new_pos.first<0) or (new_pos.first>79)) return true;
  if((new_pos.second<0) or (new_pos.second>24)) return true;
  return false;
}

const pair<int,int> 
prey::choose_next_pos() const {
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
prey::set() {
  srand((unsigned)time(NULL));
  if(position.first==-1){
    position=my_res->get_random_pos('p', my_sem, this);
    return;
  }
  pair<int,int> new_pos;
  
  while (true){
    new_pos=choose_next_pos();
    my_sem->lock(new_pos.first, new_pos.second);
    int num=my_res->is_joinable(new_pos, 'p');
    if (num==1) break;
    else my_sem->unlock(new_pos.first, new_pos.second);
    usleep(rand()%1900001+100000);
  }
  my_res->get_position(new_pos, 'p', this);
  position=new_pos;
  my_sem->unlock(new_pos.first, new_pos.second);
}

void 
prey::body() {
  pair<int,int> new_pos;
  for (int i=0; i<life_steps; ++i) {
    usleep(rand()%1900001+100000);
    while (true){
      new_pos=choose_next_pos();
      my_sem->lock(new_pos.first, new_pos.second);
      int num=my_res->is_joinable(new_pos, 'p');
      if (num==1) break;
      else my_sem->unlock(new_pos.first, new_pos.second);
      usleep(rand()%1900001+100000);
    }
    my_sem->lock(position.first, position.second);
    if(!(my_res->still_alive(position, this))){
      
      my_sem->unlock(new_pos.first, new_pos.second);
      my_sem->unlock(position.first, position.second);
      return;
    }
    my_res->switch_position(position, new_pos, 'p', this);
    my_sem->unlock(position.first, position.second);
    position=new_pos;
    if (fertility>10 and my_res->look_around(position, 'p')) { 
      prey* newborn=new prey(position, my_sem, my_res);
      my_sem->lock_list();
      my_res->track(newborn);
      my_sem->unlock_list();
      newborn->begin();
      fertility=0;
    }
    if ((i+1)==life_steps) 
      my_res->remove_me(position.first, position.second);
    my_sem->unlock(position.first, position.second);
    ++fertility;
  }
}

const bool 
prey::is_ok() const {
  if (position.first<0 or position.first>79) return false;
  if (position.second<0 or position.second>24) return false;
  return true;
}
