#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>

namespace {
    using ushort = unsigned short;
}

class snake {
public:
    enum class type_field {
        none = 0, snake = 1, apple = 2,
    };
    enum class type_step {
        left = -1, rauth = 1, up = -2 , down = 2,
    };
    enum class type_game {
        none = 0 , wing = 1, loss = -1,
    };
    snake(ushort width, ushort height);

    enum type_field is_cell(ushort i, ushort j) const;
    bool step();
    void set_step(enum type_step new_step);
    enum type_game game_statistics() const;
    ushort score_apple() const;
    const std::vector<std::pair<ushort, ushort> >& arr_snake() const;
    ushort get_width() const;
    ushort get_height() const;

    std::pair<ushort, ushort> apple() const;

private:
    static constexpr short LEFT = -1;
    static constexpr short RAUTH = 1;
    static constexpr short UP = -1;
    static constexpr short DOWN = 1;

    bool _generation_apple();
    std::pair<ushort, ushort> _new_index() const;

    ushort _score_apple;
    ushort _width;
    ushort _height;
    enum type_step _direction;
    bool _end_game;

    std::vector<std::pair<ushort, ushort> > _snake;
    std::vector<std::vector<type_field> > _field;
    std::pair<ushort, ushort> _apple;
};

#endif
