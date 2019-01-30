
all:
	g++ --std=c++11 src/*.cpp -lncurses -o minefield

clean:
	rm minefield
