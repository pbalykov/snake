#ifndef INTERFASE_HPP
#define INTERFASE_HPP

#include "snake.hpp"
#include "render.hpp"
#include "config.hpp"

class interface {
    static constexpr std::string_view PAUSE[] = {" Pause ",
    "launch", "exit"};
    
    static constexpr const char* NAME_FILE_RECORD = "record";

public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 25;
    interface();
    ~interface();
    int exec();
private:
    int _game();
    render* _render;
    config _record;
};

#endif
