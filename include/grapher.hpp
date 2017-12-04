#include "canvas.hpp"
#include "window.hpp"
#include "geom_entity.hpp"
#include <unistd.h>
#pragma once

class grapher{
  typedef enum {quitting, running, dragging} states;
  public:
    grapher(WINDOW* in) : canv_(in){
      state_ = running;
      noecho();
      keypad(in, TRUE);
    }
    grapher& operator=(grapher other) = delete;
    ~grapher() = default;


    void run(){
      while ( state_ != quitting ){
        handle();
        draw();
        usleep(40000);
      }
    }
  private:
    states state_;
    void handle();  // well. this will be a lot of work
    
    void draw(){
      typedef std::vector<ngl::entity*>::iterator iter;
      canv_.clear();
      for (iter i = ents_.begin(); i != ents_.end(); ++i)
        (*i)->draw(canv_);
      for (iter i = menu_.begin(); i != menu_.end(); ++i)
        (*i)->draw(canv_);
      canv_.refresh();
    }
    ngl::canvas canv_;
    //all things being rendered are in here
    std::vector<ngl::entity*> ents_;
    std::vector<ngl::entity*> menu_;

};


void grapher::handle(){
  static int o_x=0;
  static int o_y=0;
  //check for events
  int e = handler_.poll();
  MEVENT* evnt=NULL;
  if (e != -1){
    if (ngl::handler::is_mouse(e))
      evnt = ngl::handler::get_mouse_event();
  }


  //if we have a mouse event
  if (evnt != NULL){
    if (evnt->bstate & BUTTON1_PRESSED && state_ != dragging){
      state_ = dragging;
      o_x = evnt->x;
      o_y = evnt->y;
    }
    else if (evnt->bstate & BUTTON1_PRESSED && state_ == dragging){
      canv_.square(o_y, o_x, evnt->y, evnt->x);
    }
    else if (evnt->bstate & BUTTON1_RELEASED && state_ == dragging){
      state_ = running;
      ents_.push_back(new ngl::square(o_y, o_x, evnt->y, evnt->x));
    }
  }
  else if (e != -1){
    addch(e);
  }
}

