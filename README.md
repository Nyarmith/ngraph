# ncurses app framework

### How it Works
1. Create a cursapp class
2. Create windows for that class
3. Add entities and handlers to your windows
4. .run() the cursapp class

### TODO:
1. Add points, clearing, piece-preview, lose-state to tetris test-case. Invert colors.
2. Make tests pass
3. Create conan package
4. Make the event-handler-in-separate-thread thing dima was talking about(it can refresh 30fps if it's a game)
5. Make real-time mode work well over ssh tunnel
6. Add optional global border[s] setting
7. Give some way for the user to define their own custom color pairs https://stackoverflow.com/questions/33985896/how-to-enable-32k-color-pairs-in-ncurses
8. Base functionality off of ncurses6 capabilities https://www.gnu.org/software/ncurses/
9. Change y,x coord system to x,y(maybe)
10. Function that accepts a window, makes a permanent border-window, and returns a new sub-window(or modifies the original window and keeps the border-window inaccessible)
11. Spatial data structure for window entities, esp for default placement of entities
12. Add "default or fixed selected window/entity" i.e. default or fixed global cursor positions
13. Add font-control(if possible) to force the user's term to have a certain font
