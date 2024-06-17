#include "../headers/render.hpp"

#include <ncurses.h>

#include <cmath> /*потом перенести в одельную фаил*/

int number_signs(int number) {
    return number ? ((int)log10(number)) + 1 : 1;
}

void render::_repeat(int symbol, int quantity) const {
    for (int i = 0; i < quantity; i++) 
	    addch(symbol);
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

bool render::game(const snake& game) {
    auto size_term = this->_terminal_size();
    auto width = game.get_width();
    auto height = game.get_height();
    if ( size_term.first < (width + 6) || size_term.second < (height + 6) )  {
        return false;
    }
    
    int y = size_term.first / 2 - width / 2;
    int x = size_term.second / 2 - height / 2;
    int str_max_app = STR_MAX_APPLE.size();
    int str_app = STR_APPLE.size();
    int max_table = str_max_app > str_app ? str_max_app : str_app;

    this->_table(y - 4, x - 2, 2, max_table);
    move(y - 4, x - 2 + max_table / 2 - str_max_app / 2);
    printw("%s", STR_MAX_APPLE);
 
    this->_table(y - 4, x + height - 9, 2, max_table);
    move(y - 4, x + height - 9 + max_table / 2 - str_app / 2);
    printw("%s", STR_APPLE);

    ushort score = game.score_apple();
    move(y - 3, x + height - 9 + max_table / 2 - number_signs(score) / 2);
    printw("%d", score);


    this->_table(y, x, width, height);
    auto snake_arr = game.arr_snake();
    this->_color.set_color(color::COLOR::BACKGROUND_GREEN);
    for (int i = 0; i < snake_arr.size(); i++) {
        move(y + snake_arr[i].first, x + snake_arr[i].second);
        printw("%c", i + 1 != snake_arr.size() ? ' ' : '&');
    }
    auto apple = game.apple();
    this->_color.set_color(color::COLOR::BACKGROUND_RED);
    move(y + apple.first, x + apple.second);
    printw(" ");
    this->_color.set_color(color::COLOR::DEFAULT);
    return true;
}
