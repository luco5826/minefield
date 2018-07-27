# Minefield
Hi! This is a simple Mine Field creation engine (as the description says).

#### Goals
I just wanted to refresh some c++ I learned some times ago, my goal 
is to create a simple app based on this engine, maybe with a GUI.
Anyone who wants to collaborate is very welcome!

### Actual Features
* Create a field with user-defined size
* Mark with numbers cells that are nearby a mine

### To be implemented
* Smart revealing of the field around the selected cell
* GUI

### Compiling
By now, you don't need additional libraries in order to compile sources, any compiler
should work as well. 
Inside src/ folder, run:
```
g++ *.cpp -o mine-field
./mine-field
```
