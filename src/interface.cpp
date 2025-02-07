#include "../headers/interface.hpp"
#include <ncurses.h>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>

interface::interface() : _record(NAME_FILE_RECORD) {
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
    snake game(WIDTH, HEIGHT);
    while ( game.game_statistics() == snake::type_game::none ) {
        wclear(stdscr);
        this->_render->game(game, this->_record.get_value());
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
            case 'q' :
                return 0;
        }
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count();
        if ( elapsed < 300 ) 
            usleep((300 - elapsed) * 1000);
        game.step();
        int max_record = std::max(game.score_apple(), this->_record.get_value());
        this->_record.set_value(max_record); 
        flushinp();
    }
    return 0;
}
