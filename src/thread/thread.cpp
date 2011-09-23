#include <iostream>
#include <pthread.h>
#include "thread.h"

using namespace std;

thread::thread(){
  pro=new pthread_t;
  ready=false;
}

thread::~thread(){
  void* ret;
  pthread_join (*pro, &ret);
  delete pro;
}

int thread::begin(){
  return pthread_create(pro, NULL, rutine, (void*) this);
}

void* thread::rutine(void* class_pointer){
  thread* p_this=(thread*) class_pointer;
  p_this->set();
  p_this->body();
  p_this->ready=true;
  pthread_exit (0);
}
