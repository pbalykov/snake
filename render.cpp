#include "render.hpp"

render::render() {
    noecho();
    this->_color = new color;
    curs_set(0);
    return ;
}

render::~render() {
    curs_set(1);
    delete this->_color;
    return ;
}
