# Minefield 
[![Build Status](https://travis-ci.com/luco5826/minefield.svg?branch=master)](https://travis-ci.org/luco5826/minefield)

Hi! This is a simple Mine Field creation engine (as the description says).

#### Goals
I just wanted to refresh some c++ I learned some times ago, my goal 
is to create a simple app based on this engine, maybe with a GUI.
Anyone who wants to collaborate is very welcome!

### Collab \w me!
You are free to partecipate! Everything in the code is well commented and documented, 
I tried to follow an OOP pattern in order to keep the mess away. If you have questions 
about anything I'd be glad to explain it to you in a better way!

### Actual Features
* Create a field with user-defined size
* Mark with numbers cells that are nearby a mine
* Ask for selection and consequent cells' revelation

### To be implemented
* GUI

### Compiling
For the simple GUI to work, you will need `ncurses` installed, then you can simply run:
```
make && make clean
./minefield
```
Otherwise you can compile all the .cpp files however you want!
