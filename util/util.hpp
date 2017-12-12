#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <unistd.h>

namespace nutil {
  //factor out the scaffolding
  void init_curses(){
    setenv("TERM","xterm-1006",1);  //https://stackoverflow.com/questions/47256750/how-to-build-curses-program-that-supports-more-than-223-columns-of-mouse-input
    initscr();
    //cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    //noecho();      //comment for testing
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    //curs_set(0);   //comment for testing
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

