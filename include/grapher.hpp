#include "canvas.hpp"
#include "window.hpp"
#include "geom_entity.hpp"
#include <unistd.h>
#pragma once

class grapher{
  typedef enum {quitting, running, dragging} states;
  public:
    grapher(WINDOW* in) : scene_(in){
      state_ = running;
      noecho();
      keypad(in, TRUE);
      setup_program();
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

    void setup_program(); //set up handlers and items and whatever

    void handle();  // well. this will be a lot of work
    
    void draw(){
      typedef std::vector<ngl::entity*>::iterator iter;
      scene_.clear();
      for (iter i = ents_.begin(); i != ents_.end(); ++i)
        (*i)->draw(scene_);
      for (iter i = menu_.begin(); i != menu_.end(); ++i)
        (*i)->draw(scene_);
      scene_.refresh();
    }
    ngl::window scene_;
    //all things being rendered are in here
    std::vector<ngl::entity*> ents_;
    std::vector<ngl::entity*> menu_;

};


//do stuff t update scene
void grapher::handle(){
}

void grapher::setup_program(){
  //do everything 
}
