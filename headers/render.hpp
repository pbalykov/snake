#ifndef RENDER_HPP
#define RENDER_HPP

#include "color.hpp"
#include "snake.hpp"

#include <utility>
#include <string_view>

class render {
public:

    render() = default;
    ~render() = default;

    bool main_menu();
    bool game(const snake& game, unsigned short max_score);
    bool meny_YES_NO(const std::string_view NAME, int currsor);

    bool draw_seconds(short second);


private:
    static constexpr std::string_view STR_APPLE = "Apple";
    static constexpr std::string_view STR_MAX_APPLE = "Max apple";
    static constexpr int SIZE_TABLE_SCORE = 2;
    static constexpr int FRAME_SIZE = 2;

    void _repeat(int symbol, int quantity) const;
    void _table(int y, int x, int height, int width) const;    
    std::pair<int, int> _terminal_size() const;

    color _color;
};

#endif
