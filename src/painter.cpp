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
  int n_sheeps = 0;
  int n_wolfs = 0;
  std::chrono::milliseconds dura(500);
  do {
    n_threads = 0;
    n_sheeps = 0;
    n_wolfs = 0;
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
        if (grid->get(position(j, i)) == nullptr) {
          cout<<" ";
        }
        else {
          cout<<grid->get(position(j, i))->get_sign();
          ++n_threads;

          if (grid->get(position(j, i))->get_sign() == 's') {
            ++n_sheeps;
          }
          else
            ++n_wolfs;
        }
      }
      cout<<"*"<<endl;
    }
    for(int i = 0; i < 82; ++i) {
      cout<<"*";
    }
    cout<<endl;
    cout<<"N. threads: "<<n_threads<<endl;
    cout<<".. of which"<<endl;
    cout<<"Sheeps: "<<n_sheeps<<endl;
    cout<<"Wolfs: "<<n_wolfs<<endl;
  }
  while(n_threads != 0);
}
