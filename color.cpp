#include "color.hpp"
#include <ncurses.h>

color::color() : _color_current(COLOR::DEFAULT) {
    if ( has_colors() ) {
        start_color();
    }
    use_default_colors();

}

color::COLOR color::get_color() const {
    return this->_color_current;
}

void color::set_color(const COLOR value) {
    if ( value == COLOR::DEFAULT ) {
        attroff(COLOR_PAIR(static_cast<int>(this->_color_current)));
    } else {
        attron(COLOR_PAIR(static_cast<int>(value)));
    }
    this->_color_current = value;
    return ;
}
