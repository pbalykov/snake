#ifndef INTERFASE_HPP
#define INTERFASE_HPP

#include "snake.hpp"
#include "render.hpp"

class interface {
public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 25;
    interface();
    ~interface();
    int exec();
private:
    static constexpr std::string_view PAUSE[] = {" Pause ",
    "launch", "exit"};
    int _game();
    render* _render;
};

#endif
