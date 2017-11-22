#include "../util/util.hpp"
#pragma once

namespace ngl {
    class canvas {
      public:
        virtual ~canvas() = 0;
        //interface
        virtual void stroke(int y1, int x1, int y2, int x2) ;
        virtual void square(int y, int x, int height, int width);
        //void ellipse(int y, int x, int height, int width);
        virtual void text(int y, int x, std::string str, int just=0);
        virtual void set_hl(int pair);
        virtual void clear_hl();
    };
}



//init_pair(1, COLOR_CYAN, COLOR_BLACK);
//init_pair(2, COLOR_YELLOW, COLOR_MAGENTA);
//init_pair(3, COLOR_YELLOW, COLOR_BLUE);
//init_pair(4, COLOR_YELLOW, COLOR_RED);
//init_pair(5, COLOR_BLACK, COLOR_WHITE);
//init_pair(6, COLOR_BLACK, COLOR_YELLOW);
//init_pair(7, COLOR_BLACK, COLOR_CYAN);
