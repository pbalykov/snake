#include "../headers/config.hpp"

#include <fstream>
#include <filesystem>

#include <iostream>

config::config(std::string name_file) 
    : _name_file(name_file), _value(0) {
    
    this->_folder = std::string(std::getenv("HOME")) + std::string(FOLDER);

    std::fstream fin(this->_folder + "/" + this->_name_file, 
            std::ios::in);
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
    if ( !std::filesystem::exists(this->_folder) ) {
        std::filesystem::create_directories(this->_folder);
    }
    std::fstream fin(this->_folder + "/" + this->_name_file, 
                std::ios::out);
    if ( fin.is_open() ) {
        fin << _value;
    }
    fin.close();
}
