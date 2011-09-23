#include <iostream>
#include <cstdlib>
#include <ctime>
#include "common.h"

using namespace std;

semaphor::semaphor(){
  for(int i=0;i<25;++i)
    for(int j=0;j<80;++j)
      sem_init(&sem_table[j][i],0,1);
  sem_init(&list_sem,0,1);
}
semaphor::~semaphor(){}

void semaphor::lock_list(){
  sem_wait(&list_sem);
}
void semaphor::unlock_list(){
  sem_post(&list_sem);
}
void semaphor::lock(int x, int y){
  //std::cout<<"Locked "<<x<<" "<<y<<std::endl;
  sem_wait(&sem_table[x][y]);
}
void semaphor::unlock(int x, int y){
  //std::cout<<"Unlocked "<<x<<" "<<y<<std::endl;
  sem_post(&sem_table[x][y]);
}

resource::resource(){
  for(int i=0;i<25;++i)
    for(int j=0;j<80;++j)
      table[j][i].first=' ';
}
void resource::draw_table(){
  usleep(100000);
  system("clear");
  for(int i=0;i<25;++i){
    for(int j=0;j<80;++j){
      cout<<table[j][i].first;
    }
    cout<<"|"<<endl;
  }
  cout<<"---------------------------------------------------------------------------------"<<endl;
  cout<<"N. threads: "<<pthread_list.size()<<endl;
}

void resource::track(thread* pthread){
  pthread_list.push_back(pthread);
}

std::pair<int,int> resource::get_random_pos(char id, semaphor* sem, thread* p_thread){
    while(true){
      int x=(rand()%80);
      int y=(rand()%25);
      sem->lock(x,y);
      if(table[x][y].first==' '){
	table[x][y].first=id;
	table[x][y].second=p_thread;
	sem->unlock(x,y);
        pair <int,int> res=make_pair(x,y);
	return res;
      }
      sem->unlock(x,y);
    }	
  }

void resource::garbage_collector(semaphor* my_sem){
  my_sem->lock_list();
  list<thread*>::iterator list_it; //iterator to list<*thread>
  list_it=pthread_list.begin(); //iterator points the beginning
  while(list_it!=pthread_list.end()){ //while not at end
    if( (*list_it)->ready ){ //if the thread is ready
      delete *list_it; //destroy it
      list_it=pthread_list.erase(list_it); //and delete the pointer
    }
    else ++list_it; //else go on
  }
  my_sem->unlock_list();
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
  if (!inside(x,y))
    return 0;
  if (table[x][y].first==' ')
    return 1;
  if (table[x][y].first=='p' and id=='t')
    return 2;
  return 0;
}

bool resource::still_alive(std::pair<int, int> new_pos, thread* p_thread){
  if(table[new_pos.first][new_pos.second].second==p_thread)
    return true;
  return false;
}
    

void resource::get_position(std::pair<int,int> new_pos, char id, thread* p_thread){
  table[new_pos.first][new_pos.second].first=id;
  table[new_pos.first][new_pos.second].second=p_thread;
}

  void resource::switch_position(std::pair<int,int> position, std::pair<int,int> new_pos, char id, thread* p_thread){
  table[position.first][position.second].first=' ';
  table[position.first][position.second].second=NULL;
  table[new_pos.first][new_pos.second].first=id;
  table[new_pos.first][new_pos.second].second=p_thread;
}

void resource::remove_me(int x, int y){
  table[x][y].first=' ';
}
