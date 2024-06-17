#include "../headers/color.hpp"
#include <ncurses.h>

color::color() : _color_current(COLOR::DEFAULT) {
    if ( has_colors() ) {
        start_color();
    }
    use_default_colors();
    init_pair(static_cast<int>(COLOR::GREEN), COLOR_GREEN, -1);
    init_pair(static_cast<int>(COLOR::RED), COLOR_RED, -1);

    init_pair(static_cast<int>(COLOR::BACKGROUND_GREEN), COLOR_BLACK, COLOR_GREEN);
    init_pair(static_cast<int>(COLOR::BACKGROUND_RED),  -1, COLOR_RED);
    return ;
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
