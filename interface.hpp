#ifndef INTERFASE_HPP
#define INTERFASE_HPP

#include "snake.hpp"
#include "render.hpp"

class interface {
public:
    interface();
    ~interface();
    int exec();
private:
    int _game();
    render* _render;
};

#endif
