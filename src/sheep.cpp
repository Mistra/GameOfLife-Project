#include "sheep.h"

sheep::sheep(table* grid):
entity(grid){
}

char
sheep::get_sign() const{
  return 's';
}
