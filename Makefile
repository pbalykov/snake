.PHONY:  all run clean

NAME = snake
NCURSES_HEADER = `pkg-config --cflags ncurses`
NCURSES_LD = `pkg-config --libs ncurses`
OBJ = obj/

all: bin obj main

bin: 
	mkdir -p bin
obj:
	mkdir -p obj

main: $(patsubst %.cpp,$(OBJ)%.o,$(wildcard *.cpp))
	c++ $^ -o bin/$(NAME) $(NCURSES_LD) -O3 -std=c++17

$(OBJ)interface.o: interface.cpp
	c++ -c $^ -o $@  $(NCURSES_HEADER) -O3 -std=c++17


$(OBJ)%.o: %.cpp
	c++ -c $^ -o $@ -O3 -std=c++17

run: all
	./bin/$(NAME)

clean:
	rm -rf bin obj 
