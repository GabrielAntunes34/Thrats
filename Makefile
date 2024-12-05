run: all
	./src/sfml-app

all: 
	g++ -c ./src/Rat.cpp -o ./src/Rat.o


	g++ -c ./src/main.cpp -o ./src/main.o
	g++ ./src/main.o ./src/Rat.o  -o ./src/sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm ./src/*.o
	rm ./src/sfml-app