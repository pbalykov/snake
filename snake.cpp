#include "snake.hpp"
#include <cstdlib>
#include <iterator>

bool snake::_generation_apple() {
    this->_apple = std::make_pair(this->_width, this->_height);
    if ( this->_score_apple == this->_width * this->_height ) {
        return true;
    }
    ushort value = 0;
    ushort rand_value = std::rand();
    rand_value %= (this->_width * this->_height - this->_snake.size());
    for (size_t i = 0; i < this->_field.size(); i++) {
        for (size_t j = 0; j < this->_field[i].size(); j++) {
            bool cell_is_none = this->_field[i][j] == type_field::none;
            if ( value == rand_value && cell_is_none ) {
                this->_field[i][j] = type_field::apple;
                this->_apple = std::make_pair(i, j);
                return false;
            }
            value += cell_is_none ? 1 : 0;
        }
    }
    return true;
}

std::pair<ushort, ushort> snake::_new_index() const {
    std::pair<short, short> index = *this->_snake.rbegin();
    switch ( this->_direction ) {
        case type_step::left :
            index.second += snake::LEFT ;
            break;
        case type_step::rauth :
            index.second += snake::RAUTH;
            break;
        case type_step::up:
            index.first += snake::UP;
            break;
        case type_step::down:
            index.first += snake::DOWN;
            break;
        default:
            return std::make_pair(this->_width, this->_height);
    }
    index.first = (index.first % this->_width + this->_width);
    index.first %= this->_width;
    index.second = (index.second % this->_height + this->_height);
    index.second %= this->_height;
    return index;
}


snake::snake(ushort width, ushort height) 
    : _width(width), _height(height), _score_apple(0), 
    _direction(type_step::rauth), _end_game(false), _snake(), 
    _field(width, std::vector<type_field>(height, type_field::none) )
{   
    this->_snake.push_back(std::make_pair(width / 2, 0));
    this->_field[width / 2][0] = type_field::snake;
    this->_generation_apple();
    return ; 
}

enum snake::type_field snake::is_cell(ushort i, ushort j) const {
    return this->_field[i][j];
}

bool snake::step() {
    auto index_tail = *this->_snake.begin();
    this->_field[index_tail.first][index_tail.second] = type_field::none;
    auto index = this->_new_index();
    switch ( this->_field[index.first][index.second] ) {
        case type_field::none:
            this->_snake.push_back(index);
            this->_snake.erase(this->_snake.begin());
            this->_field[index.first][index.second] = type_field::snake;
            break;
        case type_field::snake:
            this->_end_game = true;
            this->_field[index_tail.first][index_tail.second] = type_field::snake;  
            break;
        case type_field::apple:
            this->_score_apple++;
            this->_snake.push_back(index);
            this->_field[index_tail.first][index_tail.second] = type_field::snake;
            this->_end_game = this->_generation_apple();
            this->_field[index.first][index.second] = type_field::snake;
            break;  
    }
    return this->_end_game;
}

void snake::set_step(enum type_step new_step) {
    short step_value = static_cast<short>(this->_direction);
    step_value += static_cast<short>(new_step);
    if ( step_value ) {
        this->_direction = new_step;
    }
    return ;
}

enum snake::type_game snake::game_statistics() const {
    bool wing_game = this->_width * this->_height == this->_score_apple;
    if ( this->_end_game ) {
        return wing_game ? type_game::wing : type_game::loss;
    }
    return type_game::none;
}

ushort snake::score_apple() const {
    return this->_score_apple;
}

const std::vector<std::pair<ushort, ushort> >& snake::arr_snake() const {
    return this->_snake;
}

ushort snake::get_width() const {
    return this->_width;
}

ushort snake::get_height() const {
    return this->_height;
}

std::pair<ushort, ushort> snake::apple() const {
    return this->_apple;
}
