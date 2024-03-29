#ifndef COLOR_HPP
#define COLOR_HPP


class color {
public:
    enum class COLOR {
        DEFAULT = 0,
        GREEN = 1,
        RED = 2,

        BACKGROUND_GREEN = 3,
    };
    color();
    COLOR get_color() const;
    void set_color(const COLOR value);
private:
    COLOR _color_current;
};

#endif
