.PHONY:  all run clean

NAME = Snake
NCURSES_HEADER = `pkg-config --cflags ncurses`
NCURSES_LD = `pkg-config --libs ncurses` 
OBJ = obj/
SRC = src/
FLAG_ASSEMBLY = -O2 -std=c++17 -Wall 

all: obj main

obj:
	mkdir -p obj

main: $(patsubst $(SRC)%.cpp,$(OBJ)%.o,$(wildcard $(SRC)*.cpp))
	c++ $^ -o $(NAME) $(NCURSES_LD) $(FLAG_ASSEMBLY)

$(OBJ)interface.o: $(SRC)interface.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) $(FLAG_ASSEMBLY) 

$(OBJ)render.o: $(SRC)render.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) $(FLAG_ASSEMBLY)

$(OBJ)color_game.o: $(SRC)color_game.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) $(FLAG_ASSEMBLY)



$(OBJ)%.o: src/%.cpp
	c++ -c $^ -o $@ $(FLAG_ASSEMBLY)

run: all
	./$(NAME)

clean:
	rm -rf obj 
