#include <chrono>
#include <thread>
#include <iostream>

#include "painter.h"
#include "entity.h"
#include "table.h"

using std::cout;
using std::endl;

painter::painter(const table* const grid):
                 grid(grid) {}

void painter::show() const {
  int n_threads = 0;
  do {
    n_threads = 0;
    std::chrono::milliseconds dura(100);
    std::this_thread::sleep_for( dura );
    system("clear");
    for(int i = 0; i < 82; ++i) {
      cout<<"*";
    }
    cout<<endl;
    for(int i=0;i<25;++i){
      cout<<"*";
      for(int j=0;j<80;++j){
        if (grid->get(j, i) == nullptr) {
          cout<<" ";
        }
        else {
          cout<<grid->get(j, i)->get_sign();
          ++n_threads;
        }
      }
      cout<<"*"<<endl;
    }
    for(int i = 0; i < 82; ++i) {
      cout<<"*";
    }
    cout<<endl;
    cout<<"N. threads: "<<n_threads<<endl;
  }
  while(0 < n_threads);
}
