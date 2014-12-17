//Game of Life, Universitay educational project
//Copyright (C) 2014 Giulio Mistrangelo
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor,
//Boston, MA  02110-1301, USA.

#include <iostream>
#include <thread>

#include "table.h"
#include "sheep.h"
#include "wolf.h"
#include "painter.h"

int main(){

  table field;

  for(int i=0; i<30; ++i){ //70
    wolf wf(&field);
    std::thread wolf( wf );
    wolf.detach();
  }

  for(int i=0; i<150; ++i){ //70
    sheep sp(&field);
    std::thread sheep( sp );
    sheep.detach();
  }

  painter paint(&field);
  paint.show();
  return 0;
}
