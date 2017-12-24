#include "../util/util.hpp"
#include "canvas.hpp"
#include "handler.hpp"
#include "entity.hpp"
#pragma once

namespace ngl {
  class window : public canvas {
    public:
      window(int y, int x, int h, int w) : y_(y), x_(x), h_(h), w_(w) { };
      ~window() {
      }
      window& operator=(const window& o);

      //drawing
      void add_char(int y, int x, int c);
      void stroke(int y1, int x1, int y2, int x2);
      void square(int y, int x, int height, int width);
      void text(int y, int x, std::string str, int just=0);
      void set_hl(int pair);
      void clear_hl();

      //interface
      void update(event &e, int y, int x);    //actions to do every frame
      void draw();
      void clear();
      void refresh();

      void add_handler(handler* h){ callbacks_.push_back(h); }
      void add_entity(entity* h){ entities_.push_back(h); }

      bool isIntersect(int y, int x);  //coord in this window?

      //adding other widnows
      void split(window& o);
    protected:
      //void poll();
      int y_, x_;
      int h_, w_;

      //std::vector<entity*> ents_;
      std::vector<handler*> callbacks_;
      std::vector<entity*> entities_;
  };
}


//definitions
bool ngl::window::isIntersect(int y, int x){
  if (y_ <= y && y < y_+ h_ && x_ <= x && x < x_ + w_)
    return true;

  return false;
}

void ngl::window::update(event &e, int y, int x){
  typedef std::vector<handler*>::size_type st;
  y -= y_;
  x -= x_;

  for (st i=0; i < callbacks_.size(); ++i){ 
    if (callbacks_[i]->intersect(y,x))
      callbacks_[i]->handle(e); 
  }

  for (st i=0; i < entities_.size(); ++i){
    if (entities_[i]->intersect(y,x))
        entities_[i]->update(e);
        }
        }

        void ngl::window::draw(){
        typedef std::vector<entity*>::size_type s_t;
        for (s_t i=0; i<entities_.size(); ++i){
        entities_[i]->draw(*this);
        }
        }

        // TODO : Modify drawing methods so that they don't draw outside the screen -- Priority URGENT
void ngl::window::stroke(int y1, int x1, int y2, int x2){
  double slope = static_cast<double>(y2 - y1) / (x2 - x1);
  double y = y1;
  int step=1;
  if (x2 < x1){
    slope *= -1;
    step = -1;
  }
  while(x1 != x2){
    mvaddch(floor(y) - y_, x1 - x_, 'x');
    y  += slope;
    x1 += step;
  }
}
void ngl::window::square(int y, int x, int height, int width){
  //draw top border
  int i=0;
  int s_x = x_ + x;
  int s_y = y_ + y;

  //draw top and bottom borders
  for (i=s_x; i < s_x+width; ++i){
    mvaddch(s_y, i,'#');
    mvaddch(s_y +height-1,i,'#');
  }
  //draw left and right borders
  for (i=s_y+1; i<s_y+height-1; ++i){
    mvaddch(i,s_x,'#');
    mvaddch(i,s_x+width-1,'#');
  }
}

//void ellipse(int y, int x, int height, int width);
void ngl::window::text(int y, int x, std::string str, int just){
  int s_x = x_ + x;
  int s_y = y_ + y;
  if (just == 0){
    mvprintw(s_y, s_x,"%s",str.data());
  }
  else if (just != 0){
    std::string arg = "%-";
    arg += just;
    arg += "s";
    mvprintw(y,x,"%s",str.data());
  }
}

void ngl::window::add_char(int y, int x, int c){
  mvaddch(y, x, c);
}

void ngl::window::set_hl(int pair){
  attron(pair);
}

void ngl::window::clear_hl(){
  attron(0);
}

void ngl::window::split(ngl::window& o){
  o.y_ = y_ + h_ / 2 + h_ % 2;
  o.x_ = x_ + w_ / 2 + h_ % 2;
  o.h_ = h_ / 2;
  o.w_ = w_ / 2;
  h_ = h_ / 2 + h_ % 2;
  w_ = w_ / 2 + w_ % 2;
}
