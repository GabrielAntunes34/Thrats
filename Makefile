run: all
	./src/sfml-app

valgrind: all
	valgrind --leak-check=full --track-origins=yes ./src/sfml-app


all: 
	g++ -c ./src/Rat.cpp -o ./src/Rat.o
	g++ -c ./src/TileMap.cpp -o ./src/TileMap.o
	g++ -c ./src/Tile.cpp -o ./src/Tile.o


	g++ -c ./src/main.cpp -o ./src/main.o
	g++ ./src/main.o ./src/Rat.o ./src/Tile.o ./src/TileMap.o  -o ./src/sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm ./src/*.o
	rm ./src/sfml-app