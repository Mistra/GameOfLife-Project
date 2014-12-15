#ifndef SHEEP_H
#define SHEEP_H

#include "entity.h"

class sheep: public entity {
public:
  sheep(table*);
  ~sheep(){}
  char get_sign() const;

};

#endif
