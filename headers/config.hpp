#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class config {
public:
    config(std::string name_file);
    unsigned short get_value() const;
    void set_value(int new_value);

private:
    std::string _name_file;
    unsigned short _value;
    std::string _folder;
    static constexpr const char* FOLDER = "/.cache/snake";
};

#endif
