#include <chrono>
#include <thread>
#include <iostream>

#include "painter.h"
#include "entity.h"
#include "table.h"
#include "settings.h"

using std::cout;
using std::endl;

painter::painter(const table* const grid):
                 grid(grid) {
}

void
painter::show() {
  do {
    n_threads = 0;
    n_sheeps = 0;
    n_wolfs = 0;
    show_table();
    show_stats();
  }
  while(n_threads != 0 and
    n_sheeps < 2000);
}

void
painter::show_table() {
  std::chrono::milliseconds dura(100);
  std::this_thread::sleep_for( dura );
  system("clear");

  for(int i = 0; i < settings::get("base")+2; ++i)
    cout<<"*";
  cout<<endl;

  for(int i=0;i<settings::get("height");++i){
    cout<<"*";
    for(int j=0;j<settings::get("base");++j){
      entity* ent = grid->get(position(j, i));
      if (ent == nullptr) {
        cout<<" ";
      }
      else {
        cout<<ent->get_sign();
        ++n_threads;
        if (ent->get_sign() == 's') ++n_sheeps;
        else ++n_wolfs;
      }
    }
    cout<<"*"<<endl;
  }
  for(int i = 0; i < settings::get("base")+2; ++i) {
    cout<<"*";
  }
  cout<<endl;
}

void
painter::show_stats() {
  cout<<"Sheeps: "<<n_sheeps<<endl;
  cout<<"Wolfs: "<<n_wolfs<<endl;
}
