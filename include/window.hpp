#include "../util/util.hpp"
#include "canvas.hpp"
#include "handler.hpp"
#include "entity.hpp"
#pragma once

//add border, make it optional to be used/displayed

namespace ngl {
  class win_obj : public canvas {
    public:
      win_obj(int y, int x, int h, int w) : y_(y), x_(x), h_(h), w_(w) { };
      ~win_obj() {
      }
      win_obj& operator=(const win_obj& o);

      //drawing
      void add_char(int y, int x, int c);
      void stroke(int y1, int x1, int y2, int x2, int ch='x');
      void rect(int y, int x, int height, int width, int ch='#');
      void box(int y, int x, int height, int width, int btype=0);
      void text(int y, int x, std::string str, int just=0);
      void set_attr(unsigned long attrs, bool on=true);
      void set_hl(int pair);
      void clear_hl();

      //interface
      void update(event &e, int y, int x);    //actions to do every frame
      void draw();
      void clear();
      void refresh();

      void add_handler(handler* h){ callbacks_.push_back(h); }
      void add_entity(entity* h){ entities_.push_back(h); }

      bool intersect(int y, int x);  //global coord in this win_obj?

      int height() { return h_; };
      int width() { return w_; };

      //adding other widnows
      win_obj* split();
    protected:
      //void poll();
      int y_, x_;
      int h_, w_;

      //std::vector<entity*> ents_;
      std::vector<handler*> callbacks_;
      std::vector<entity*> entities_;
  };

  class window {
    public:
      window();
      window(int y, int x, int h, int w) { win_ = new win_obj(y,x,h,w); };
      window(const window &o) { win_ = o.win_; };
      window(win_obj &o)      { win_ = &o; };
      window& operator=(const window &o) = delete;
      void update(event &e, int y, int x) {win_->update(e,y,x);};
      void draw() { win_->draw(); };
      void refresh() { win_->refresh(); };
      void add_entity(entity *e)  { win_->add_entity(e); };
      void add_entity(std::function<void(canvas&)> d) { win_->add_entity(new anon_entity(d)); };
      void add_entity(std::function<void(canvas&)> d,
          std::function<void(const event&)> u)        { win_->add_entity(new anon_entity(d,u)); };
      void add_handler(handler *h){ win_->add_handler(h);};
      bool intersect(int y,int x){ return win_->intersect(y,x); };
      int width()  { return win_->width(); }
      int height() { return win_->height();}
      window split(); //defined in cursapp.hpp
    private:
      win_obj* win_;
  };

}


//definitions
bool ngl::win_obj::intersect(int y, int x){
  if (y_ <= y && y < y_+ h_ && x_ <= x && x < x_ + w_)
    return true;

  return false;
}

void ngl::win_obj::update(event &e, int y, int x){
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

        void ngl::win_obj::draw(){
        typedef std::vector<entity*>::size_type s_t;
        for (s_t i=0; i<entities_.size(); ++i){
        entities_[i]->draw(*this);
        }
        }

        // TODO : Modify drawing methods so that they don't draw outside the screen -- Priority URGENT
void ngl::win_obj::stroke(int y1, int x1, int y2, int x2, int ch){
  double slope = static_cast<double>(y2 - y1) / (x2 - x1);
  double y = y1;
  int step=1;
  if (x2 < x1){
    slope *= -1;
    step = -1;
  }
  while(x1 != x2){
    add_char(floor(y), x1, ch);
    y  += slope;
    x1 += step;
  }
}
void ngl::win_obj::rect(int y, int x, int height, int width, int ch){
  int i=0;
  
  for (i=x; i < x+width; ++i){  //draw top and bottom borders
    add_char(y, i, ch);
    add_char(y +height-1,i, ch);
  }
  
  for (i=y+1; i<y+height-1; ++i){  //draw left and right borders
    add_char(i,x,ch);
    add_char(i,x+width-1,ch);
  }
}

void ngl::win_obj::box(int y, int x, int height, int width, int btype){
  y = y + y_;
  x = x + x_;
  // with alternate charset attribute enabled(A_ALTCHARSET)
  // ┘=j
  // └=m
  // ┐=k
  // ┌=l
  // [mv]hline  =  horizontal line with chtype ch (0 is what I want)
  // [mv]vline  =  vertical line equivalent
  if (height < 2 || width < 2)
    return ;//draw nothing

  attron(A_ALTCHARSET); //each call here draws its respective corner
  mvaddch(y         , x, 'l'); mvaddch(y         , x+width-1, 'k');
  mvaddch(y+height-1, x, 'm'); mvaddch(y+height-1, x+width-1, 'j');
  attroff(A_ALTCHARSET);

  mvhline(y         , x+1    , btype, width - 2 );
  mvhline(y+height-1, x+1    , btype, width - 2 );

  mvvline(y+1     , x        , btype, height  - 2 );
  mvvline(y+1     , x+width-1, btype, height  - 2 );
}

//todo: add some kind of thing for str justiciation
void ngl::win_obj::text(int y, int x, std::string str, int just){
  int s_x = x_ + x;
  int s_y = y_ + y;

  //out of bounds
  if ( 0  > y || y > h_ || x > w_ || (x + (int)str.size()) < 0 )
    return;
  //fully fits in perfectly
  else if (0 <= x && x + (int)str.length() < w_){
    mvprintw(s_y, s_x, str.data());
  }
  //cut off on left
  else if (x < 0 && x + (int)str.length() < w_){
    mvprintw(s_y, s_x, str.substr(-x).data());
  }
  //cut off on right
  else if (0 <= x && x + (int)str.length() > w_){
    mvprintw(s_y, s_x, str.substr(0,w_ - x).data());
  }
  //cut off on both sides
  else if (x < 0 && x + (int)str.length() > w_){
    mvprintw(s_y, x_, str.substr(-x,w_ ).data());
  }
}

void ngl::win_obj::add_char(int y, int x, int c){
  if (0 <= x && x < w_ && 0 <= y && y < h_)
    mvaddch(y_ + y,  x_ + x, c);
}

void ngl::win_obj::set_attr(unsigned long attrs, bool on){
  if (on)
    attron(attrs);
  else
    attroff(attrs);
}

void ngl::win_obj::set_hl(int pair){
  attron(pair);
}

void ngl::win_obj::clear_hl(){
  attron(0);
}

ngl::win_obj* ngl::win_obj::split(){
  int o_y = y_ + h_ / 2 + h_ % 2;
  int o_x = x_ + w_ / 2 + h_ % 2;
  int o_h = h_ / 2;
  int o_w = w_ / 2;
  h_ = h_ / 2 + h_ % 2;
  w_ = w_ / 2 + w_ % 2;
  return new win_obj(o_y, o_x, o_h, o_w);
}
