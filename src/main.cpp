#include <stdlib.h>
#include <grapher.hpp>
#include "../util/util.hpp"

int main(){
  setenv("TERM","xterm-1006",1);
  initscr();
  grapher g(stdscr);
  g.run();
}
