
all:
	g++ --std=c++11 src/*.cpp -lncurses -o minefield

pot:
	xgettext --keyword=_ --language=C++ --add-comments --sort-output -o po/minefield.pot src/*.cpp src/*.hpp

clean:
	rm minefield

