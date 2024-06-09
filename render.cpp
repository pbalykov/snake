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
    return ;
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

bool render::game(const snake& game) {
    auto size_term = this->_terminal_size();
    auto width = game.get_width();
    auto height = game.get_height();
    if ( size_term.second < (width + 2) || size_term.second < (height + 2) ) 
        return false;

    int x = size_term.first / 2 - (width + 2) / 2;
    int y = size_term.second / 2 - (height + 2) / 2;
    this->_table(y, x, height, width);
    return true;
    auto sname_arr = game.arr_snake();
    this->_color.set_color(color::COLOR::BACKGROUND_GREEN);
    for (auto i : sname_arr) {
        move(y + i.first, x + i.second);
        printw(" ");
    }
    this->_color.set_color(color::COLOR::DEFAULT);
    auto apple = game.apple();
    move(y + apple.first, x + apple.second);
    printw("$");
    return true;
}
