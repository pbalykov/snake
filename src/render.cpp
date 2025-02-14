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
 //   std::pair<int, int> size_term = this->_terminal_size();
    return true;
}


bool render::meny_YES_NO(const std::string_view NAME, int currsor) {
    auto value = this->_terminal_size(); 
    int y = value.first / 2 - 1, 
        x = value.second / 2 - NAME.size() / 2;
    this->_table(y, x, 2, NAME.size());
    move(y - 1, x);
    printw("%s", NAME.data());
    move(y + 1, x);    
    this->_color.set_color(!currsor? COLOR::GREY : COLOR::DEFAULT);
    printw(" Yes ");
    this->_color.set_color(!currsor ? COLOR::DEFAULT : COLOR::GREY);
    move(y + 1, x + NAME.size() - 4);
    printw(" No ");
    this->_color.set_color(COLOR::DEFAULT);
    refresh();
    return true;
}

bool render::draw_seconds(short second) {
    auto value = this->_terminal_size(); 
    int y = value.first / 2 - 1, 
        x = value.second / 2 - 2;
    this->_color.set_color(COLOR::GREY);
    for (int i = 0; i < 3; i++) {
        move(y + i, x);
        _repeat(' ', 5);
    }
    move(y + 1, x + 2);
    printw("%d", second);
    this->_color.set_color(COLOR::DEFAULT);
    refresh();
    return true;
}



bool render::game(const snake& game, unsigned short max_score) {
    auto size_term = this->_terminal_size();
    auto width = game.get_width(); 
    width += SIZE_TABLE_SCORE;
    auto height = game.get_height();
  
    int y = size_term.first / 2 - (width + 4) / 2;
    int x = size_term.second / 2 - height / 2;
    int str_max_app = STR_MAX_APPLE.size();
    int str_app = STR_APPLE.size();
    int max_table = str_max_app > str_app ? str_max_app : str_app;

    this->_table(y, x, SIZE_TABLE_SCORE, max_table);
    this->_color.set_color(COLOR::YELLOW);
    move(y, x + max_table / 2 - str_max_app / 2);
    printw("%s", STR_MAX_APPLE);
    move(y + 1, x + max_table / 2 - number_signs(max_score) / 2);
    printw("%d", max_score);
    this->_color.set_color(COLOR::DEFAULT);


    this->_table(y, x + height - 9, SIZE_TABLE_SCORE, max_table);
    move(y, x + height - 9 + max_table / 2 - str_app / 2);
    this->_color.set_color(COLOR::YELLOW);
    printw("%s", STR_APPLE);
    ushort score = game.score_apple();
    move(y + 1, x + height - 9 + max_table / 2 - number_signs(score) / 2);
    printw("%d", score);
    this->_color.set_color(COLOR::DEFAULT);
    
    y += SIZE_TABLE_SCORE + FRAME_SIZE;
    this->_table(y, x, game.get_width(), game.get_height());
    auto snake_arr = game.arr_snake();
    this->_color.set_color(COLOR::BACKGROUND_GREEN);
    for (int i = 0; i < snake_arr.size(); i++) {
        move(y + snake_arr[i].first, x + snake_arr[i].second);
        printw("%c", i + 1 != snake_arr.size() ? ' ' : '&');
    }
    auto apple = game.apple();
    this->_color.set_color(COLOR::BACKGROUND_RED);
    move(y + apple.first, x + apple.second);
    printw(" ");
    this->_color.set_color(COLOR::DEFAULT);
    refresh();
    return true;
}
