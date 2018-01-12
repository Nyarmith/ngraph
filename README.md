# ncurses app framework

### How it Works
1. Create a cursapp class
2. Create windows for that class
3. Add entities and handlers to your windows
4. .run() the cursapp class

### TODO:
0. Create method of adding anonymous draw() method to a window
1. Create text input widget
2. Create widget grouped-logic(or a mechanism to handle relations between widgets groups)
3. Create general form() function
4. Create game-like test-cases
5. Make app instance a singleton
6. Make tests pass
7. Create conan package
8. Make the event-handler-in-separate-thread thing dima was talking about(it can refresh 30fps if it's a game)
9. Make test that shows ncurses bstates in hex side-by-side

