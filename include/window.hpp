#include "../util/util.hpp"
#include "poller.hpp"
#include "canvas.hpp"
#include "handler.hpp"
//#include "entity.hpp"
#pragma once

namespace ngl {
  class window : public canvas {
    public:
      window(int y, int x, int h, int w) : y_(y), x_(x), h_(h), w_(w){
        //all window related initialization happens here
        win_ = newwin(h,w,y,x);
        //keypad(win_, TRUE);
        wrefresh(win_);
        wclear(win_);
        //wrefresh(win_);
        //wclear(win_);
        poller_ = new poller(win_);
        //nodelay(win_, TRUE);
      };
      ~window() {
        delwin(win_);
      }
      window& operator=(const window& o) = delete;

      //entity mgmt
      

      //drawing
      void stroke(int y1, int x1, int y2, int x2);
      void square(int y, int x, int height, int width);
      void text(int y, int x, std::string str, int just=0);
      void set_hl(int pair);
      void clear_hl();

      //interface
      void update();    //actions to do every frame
      void draw();
      void clear();
      void refresh();

      void add_handler(handler* h){
        callbacks_.push_back(h);
      }
      bool isIntersect(int y, int x);  //coord in this window?
    protected:
      //void poll();
      WINDOW* win_; //nothing else should be able to refresh, draw on this WINDOW*
      int y_, x_;
      int h_, w_;
      poller* poller_;

      //std::vector<entity*> ents_;
      std::vector<handler*> callbacks_;
  };
}


//definitions
bool ngl::window::isIntersect(int y, int x){
  if (y_ <= y && y < y_+ h_ && x_ <= x && x < x_ + w_)
    return true;

  return false;
}

void ngl::window::update(){
  typedef std::vector<handler*>::size_type st;
  //get event
  ngl::event e = poller_->poll();
  for (st i=0; i < callbacks_.size(); ++i){
    callbacks_[i]->handle(e);
  }
}

void ngl::window::draw(){
//  // TODO: do something with p that relates to the entities managed by window
//  //typedef std::vector<entity*>::size_type s_t;
//  for (s_t i=0; i<ents_.size(); ++i){
//    //TODO : Make not hardcoded
//    ents_[i]->handle();
//  }
}

void ngl::window::clear(){
  wclear(win_);
}

void ngl::window::refresh(){
  wrefresh(win_);
}

void ngl::window::stroke(int y1, int x1, int y2, int x2){
  double slope = static_cast<double>(y2 - y1) / (x2 - x1);
  double y = y1;
  int step=1;
  if (x2 < x1){
    slope *= -1;
    step = -1;
  }
  while(x1 != x2){
    mvwaddch(win_, floor(y), x1, 'x');
    y  += slope;
    x1 += step;
  }
}
void ngl::window::square(int y, int x, int height, int width){
  //draw top border

  int i=0;

  for (i=x; i < x+width; ++i)
    mvwaddch(win_,y,i,'#');

  //draw left and right borders
  for (i=y+1; i<y+height-1; ++i){
    mvwaddch(win_,i,x,'#');
    mvwaddch(win_,i,x+width-1,'#');
  }

  //draw bottom border
  for (i=x; i < x+width; ++i)
    mvwaddch(win_,y+height-1,i,'#');
}

//void ellipse(int y, int x, int height, int width);
void ngl::window::text(int y, int x, std::string str, int just){
  if (just == 0){
    mvwprintw(win_,y,x,"%s",str.data());
  }
  else if (just != 0){
    std::string arg = "%-";
    arg += just;
    arg += "s";
    mvwprintw(win_,y,x,"%s",str.data());
  }
}
void ngl::window::set_hl(int pair){
  attron(pair);
}
void ngl::window::clear_hl(){
  attron(0);
}
