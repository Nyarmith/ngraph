#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <unistd.h>
#include <functional>

namespace nutil {
  //factor out the scaffolding
  void init_curses(){
    setenv("TERM","xterm-1006",1);  //https://stackoverflow.com/questions/47256750/how-to-build-curses-program-that-supports-more-than-223-columns-of-mouse-input
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1002h\n");   //this is the one that tracks every mouse events, see http://invisible-island.net/xterm/ctlseqs/ctlseqs.html starting at section 1 0 0 0
    noecho();      //comment for testing
    curs_set(0);   //comment for testing
    if (has_colors() == TRUE){
      start_color();
    } else {
      mvprintw(1,1,"error, terminal does not support colors");
      refresh();
      usleep(200000);
    }

    clear();
  }
}

