//Game of Life, Universitay educational project
//Copyright (C) 2011 os-project-game-of-life projet owners
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
#include "painter.h"

int main(){

  table field;
  for(int i=0; i<70; ++i){ //70
    entity* ent=new sheep(&field);
    std::thread sheep(routine, ent);
    sheep.detach();
  }

  painter paint(&field);
  paint.show();
  return 0;
}
