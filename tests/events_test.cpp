#include "window.hpp"

int main(){
  initscr(); //may not be necessary with the individual newwin()s and initscr()s

  ngl::window main_window(stdscr);

}
