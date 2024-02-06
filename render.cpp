#include "render.hpp"

#include <ncurses.h>

void render::_repeat(int symbol, int quantity) const {
    for (int i = 0; i < quantity; i++) {
	    addch(symbol);
    }
    return ;
}

void render::_table(int y, int x, int height, int width) const {
    move(y - 1, x - 1);
    addch(ACS_ULCORNER);
    this->_repeat(ACS_HLINE, width);
    addch(ACS_URCORNER);
    for (int i = 0; i < height; i++) {
        move(y + i, x - 1);
        addch(ACS_VLINE);
        this->_repeat(' ', width);
        addch(ACS_VLINE);
    }
    move(y + height, x - 1);
    addch(ACS_LLCORNER);
    this->_repeat(ACS_HLINE, width);
    addch(ACS_LRCORNER);
    return ;
}

std::pair<int, int> render::_terminal_size() const {
    std::pair<int, int> size(0, 0);
    getmaxyx(stdscr, size.first, size.second);
    return size;
}


bool render::main_menu() {
    std::pair<int, int> size_term = this->_terminal_size();
    return true;
}
