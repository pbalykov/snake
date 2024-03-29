#include "interface.hpp"
#include <ncurses.h>
#include <chrono>
#include <cstdlib>
#include <unistd.h>

interface::interface() {
    initscr();
    noecho(); 
    this->_render = new render;
    keypad(stdscr, true);
    cbreak();
    curs_set(0);
    std::srand(std::time(nullptr));
    return ;
}

interface::~interface() {
    curs_set(1);
    endwin();
}

int interface::exec() {
    return this->_game();
}

int interface::_game() {
      snake game(10, 20);
 //   timeout(300);
    while ( game.game_statistics() == snake::type_game::none ) {
        wclear(stdscr);
        this->_render->_table(1, 1, 10, 20);
        for (short i = 0; i < 10; i++) {
            move(1 + i, 1);
            for (short j = 0; j < 20; j++) {
                switch ( game.is_cell(i, j) ) {
                    case snake::type_field::none:
                        printw(" ");
                        break;
                    case snake::type_field::apple:
                        printw("$");
                        break;
                    case snake::type_field::snake:
                        this->_render->_color.set_color(color::COLOR::BACKGROUND_GREEN);
                        printw(" ");
                        this->_render->_color.set_color(color::COLOR::DEFAULT);

                        break;
                }
            }
        }
        auto start = std::chrono::high_resolution_clock::now();
        halfdelay(3);
        auto key = getch();
        switch (key) {
            case KEY_UP :
                game.set_step(snake::type_step::up);
                break;
    	    case KEY_DOWN :
                game.set_step(snake::type_step::down);
    	        break;
    	    case KEY_LEFT :
                game.set_step(snake::type_step::left);
        		break;
    	    case KEY_RIGHT :
	            game.set_step(snake::type_step::rauth);
    	        break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count();
        if ( elapsed < 300 ) 
            usleep((300 - elapsed) * 1000);
        game.step();
        flushinp();
    }
    return 0;
}

