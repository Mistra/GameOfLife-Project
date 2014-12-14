#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "common.h"

using namespace std;

void resource::lock(int x, int y){
  sem_wait(&sem_table[x][y]);
}

void resource::unlock(int x, int y){
  sem_post(&sem_table[x][y]);
}

resource::resource(){
  for(int i=0;i<25;++i)
    for(int j=0;j<80;++j)
      sem_init(&sem_table[j][i],0,1);

  for(int i=0;i<25;++i)
    for(int j=0;j<80;++j)
      table[j][i].first=' ';
}



std::pair<int,int> resource::get_random_pos(char id, entity* p_thread){
    while(true){
      int x=(rand()%80);
      int y=(rand()%25);
      lock(x,y);
      if(table[x][y].first==' '){
	table[x][y].first=id;
	table[x][y].second=p_thread;
	unlock(x,y);
        pair <int,int> res=make_pair(x,y);
	return res;
      }
      unlock(x,y);
    }
  }


bool resource::inside(int x, int y){
  if(x<0 or x>79) return false;
  if(y<0 or y>24) return false;
  return true;
}

bool resource::look_around(std::pair<int,int> new_pos, char id){
  int x=new_pos.first;
  int y=new_pos.second;
  if(inside(x+1, y) and table[x+1][y].first==id) return true;
  if(inside(x-1, y) and table[x-1][y].first==id) return true;
  if(inside(x, y+1) and table[x][y+1].first==id) return true;
  if(inside(x, y-1) and table[x][y-1].first==id) return true;
  return false;
}

int resource::is_joinable(std::pair<int,int> new_pos, char id){
  int x=new_pos.first;
  int y=new_pos.second;
  if (!inside(x,y)) return 0;
  if (table[x][y].first==' ') return 1;
  if (table[x][y].first=='p' and id=='t') return 2;
  return 0;
}

bool resource::still_alive(std::pair<int, int> new_pos, entity* p_thread){
  if(table[new_pos.first][new_pos.second].second==p_thread)
    return true;
  return false;
}


void resource::get_position(std::pair<int,int> new_pos, char id, entity* p_thread){
  table[new_pos.first][new_pos.second].first=id;
  table[new_pos.first][new_pos.second].second=p_thread;
}

  void resource::switch_position(std::pair<int,int> position, std::pair<int,int> new_pos, char id, entity* p_thread){
  table[position.first][position.second].first=' ';
  table[position.first][position.second].second=NULL;
  table[new_pos.first][new_pos.second].first=id;
  table[new_pos.first][new_pos.second].second=p_thread;
}

void resource::remove_me(int x, int y){
  table[x][y].first=' ';
}

char resource::get_sign(int x, int y) const{
  return table[x][y].first;
}
