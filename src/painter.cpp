#include <chrono>
#include <thread>
#include <iostream>

#include "painter.h"
#include "common.h"

using std::cout;
using std::endl;

painter::painter(const resource* const table):
table(table) {}

void painter::show() const {
  int n_threads = 0;
  do {
    n_threads = 0;
    std::chrono::milliseconds dura(100);
    std::this_thread::sleep_for( dura );
    system("clear");
    for(int i=0;i<25;++i){
      for(int j=0;j<80;++j){
        if (table->get_sign(j, i) != ' ') ++n_threads;
        cout<<table->get_sign(j, i);
      }
      cout<<"|"<<endl;
    }
    for(int i = 0; i < 80; ++i) {
      cout<<"_";
    }
    cout<<endl;
    cout<<"N. threads: "<<n_threads<<endl;
  }
  while(0 < n_threads);
}
