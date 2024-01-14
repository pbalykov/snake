#ifndef INTERFASE_HPP
#define INTERFASE_HPP

#include "snake.hpp"

class interface {
public:
    interface();
    ~interface();
    int exec();
private:
    int _game();
};

#endif
