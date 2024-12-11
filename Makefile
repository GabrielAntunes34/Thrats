run: all
	./src/sfml-app

valgrind: all
	valgrind --leak-check=full --track-origins=yes ./src/sfml-app


all: 
	g++ -c ./src/Rat.cpp -o ./bin/Rat.o
	g++ -c ./src/TileMap.cpp -o ./bin/TileMap.o
	g++ -c ./src/Tile.cpp -o ./bin/Tile.o
	g++ -c ./src/Menu.cpp -o ./bin/Menu.o
	g++ -c ./src/Player.cpp -o ./bin/Player.o
	g++ -c ./src/main.cpp -o ./bin/main.o
	g++ -c ./src/Litter.cpp -o ./bin/Litter.o


	g++ -c ./src/main.cpp -o ./bin/main.o
	g++ ./bin/main.o ./bin/Rat.o ./bin/Tile.o ./bin/TileMap.o ./bin/Menu.o ./bin/Player.o ./bin/Litter.o -o ./src/sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm ./bin/*.o
	rm ./src/sfml-app