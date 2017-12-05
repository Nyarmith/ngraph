#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <tuple>

namespace util {
    int translate(int x, int o){
      return x-o;
    }
    int reflect(int x, int o){
      return 2*o-x;
    }
    //factor out the scaffolding
    void initialize_ncurses(){
      initscr();
    }
}
