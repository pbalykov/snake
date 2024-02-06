#ifndef RENDER_HPP
#define RENDER_HPP

#include "color.hpp"
#include <utility>

class render {
public:
    render() = default;
    ~render() = default;

    bool main_menu();

//private:
    void _repeat(int symbol, int quantity) const;
    void _table(int y, int x, int height, int width) const;    
    std::pair<int, int> _terminal_size() const;

    color _color;
};

#endif
