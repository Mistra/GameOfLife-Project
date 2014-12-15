#ifndef WOLF_H
#define WOLF_H

#include "entity.h"

class wolf: public entity {
public:
  wolf(table*);
  wolf(table*, position);
  ~wolf(){}
protected:
  void reproduce();
  char get_sign() const;
  bool is_eatable(entity*);
};

#endif
