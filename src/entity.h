#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include "common.h"

class resource;

class entity{
public:
    entity(resource*);
    entity(std::pair<int,int>, resource*);
    ~entity();

    void set();
    void body();

protected:
    const bool is_outside_box(std::pair<int,int> new_pos) const;
    const std::pair<int,int> choose_next_pos() const;

private:
    const bool is_ok() const; //used for debugging
    std::pair<int,int> position;
    int fertility;
    int life_steps;
    resource* my_sem;
    resource* my_res;
};

void routine(entity* ent);

#endif
