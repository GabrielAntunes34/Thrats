run: all
	./src/sfml-app

all:
	g++ -c ./src/main.cpp
	g++ ./src/main.o -o ./src/sfml-app -lsfml-graphics -lsfml-window -lsfml-system
