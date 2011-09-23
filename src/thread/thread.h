#ifndef THREAD_H
#define THREAD_H

class thread{
 public:
  thread();
  virtual ~thread();
  int begin();
  bool ready;

 protected:
  static void* rutine(void*);
  virtual void set()=0; 
  virtual void body()=0;
  
 private:
  pthread_t* pro;  
};

#endif //THREAD_H
