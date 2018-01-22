#include "../util/util.hpp"
#pragma once

//abstract class != pure virtual class

//Drawing Interface
namespace ngl {
    class canvas {
      public:
        virtual ~canvas() = 0;

        //standard ncursed functions
        virtual void add_char(int y, int x, int c) = 0;

        //newer interface
        virtual void stroke(int y1, int x1, int y2, int x2, int ch='x') = 0;
        virtual void rect(int y, int x, int height, int width, int ch='#') = 0;
        virtual void box(int y, int x, int height, int width, int btype=0) = 0;
        //void ellipse(int y, int x, int height, int width);
        virtual void text(int y, int x, std::string str, int just=0) = 0;
        virtual void set_hl(int pair) = 0;
        virtual void set_attr(unsigned long attrs, bool on=true) = 0;
        virtual void clear_hl() = 0;
    };

    canvas::~canvas() {
    }
}

