#include "../util/util.hpp"
#pragma once

//Drawing Interface
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

