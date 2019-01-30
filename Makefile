
all:
	g++ src/*.cpp -lncurses -o minefield

clean:
	rm minefield