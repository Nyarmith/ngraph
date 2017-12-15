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
      void update(event &e);    //actions to do every frame
      void draw();
      void clear();
      void refresh();

      void add_handler(handler* h){ callbacks_.push_back(h); }
      void add_entity(entity* h){ entities_.push_back(h); }

      bool isIntersect(int y, int x);  //coord in this window?
    protected:
      //void poll();
      WINDOW* win_; //nothing else should be able to refresh, draw on this WINDOW*
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

void ngl::window::update(event &e){
  typedef std::vector<handler*>::size_type st;

  for (st i=0; i < callbacks_.size(); ++i){
    callbacks_[i]->handle(e);
  }
}

void ngl::window::draw(){
  typedef std::vector<entity*>::size_type s_t;
  for (s_t i=0; i<entities_.size(); ++i){
      entities_[i]->draw(*this);
    }
}

void ngl::window::clear(){
  wclear(win_);
}

void ngl::window::refresh(){
  wrefresh(win_);
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

  for (i=x; i < x+width; ++i)
    mvwaddch(win_,y - y_,i,'#');

  //draw left and right borders
  for (i=y+1; i<y+height-1; ++i){
    mvaddch(i,x - x_,'#');
    mvaddch(i,x - x_ + width-1,'#');
  }

  //draw bottom border
  for (i=x; i < x+width; ++i)
    mvaddch(y - y_ +height-1,i,'#');
}

//void ellipse(int y, int x, int height, int width);
void ngl::window::text(int y, int x, std::string str, int just){
  if (just == 0){
    mvprintw(y - y_, x - x_,"%s",str.data());
  }
  else if (just != 0){
    std::string arg = "%-";
    arg += just;
    arg += "s";
    mvwprintw(win_,y,x,"%s",str.data());
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
