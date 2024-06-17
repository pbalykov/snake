#include "../headers/config.hpp"

#include <fstream>
#include <iostream>

config::config(std::string name_file) 
    : _name_file(name_file), _value(0) {

    std::fstream fin(this->_name_file, std::ios::in);
   // fin.open(_name_file, std::ios::in);
    if ( fin.is_open() ) {
        fin >> _value;
    }
    fin.close();
}

unsigned short config::get_value() const {
    return _value;
}

void config::set_value(int new_value) {
    this->_value = new_value;
    std::fstream fin(this->_name_file, std::ios::in);;
 //   fin.open(_name_file, std::ios::out);
    if ( fin.is_open() ) {
        fin << _value;
    }
    fin.close();
}
