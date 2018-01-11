#include "../util/util.hpp"
#include "window.hpp"
#pragma once

#ifdef DEBUG
static ngl::event e;
static ngl::event le;
static int curs_y, curs_x;
#endif

namespace ngl {
  class cursapp {
    public:
      ~cursapp() = default;
      //static cursapp *cursapp_instance;
      //static cursapp* inst();  //TODO make a singleton

      void run();
      void addWindow(window &n);
      static cursapp& instance(){
        if (!cursapp_instance)
          cursapp_instance = new cursapp();
        return *cursapp_instance;
      }

      //fancy ways to add a window
      std::vector<window> partition(int n);  //partition evenly among n subwindows
      std::vector<window> partition(std::vector<int> n);  //partition in given ratio
    private:
      static cursapp* cursapp_instance;
      cursapp();
      void update();
      void draw();
      void clear();

      std::vector<window> windows_;
      poller poller_;
  };

  cursapp *cursapp::cursapp_instance = 0;


  void cursapp::run(){
    while(true){
      update();
      clear();
      draw();
      usleep( 33000 );
    }
  }

  void cursapp::addWindow(window &n){
    windows_.push_back(n);
  }

  void cursapp::update(){
    static int curs_y=0;
    static int curs_x=0;

    //get input
    event e = poller_.poll();

    //update meta-cursor state
    if (e.type == EVENT::MOUSE){   //curs_y, curs_x events are somehow updating. Figure out why.
      curs_y = e.y;
      curs_x = e.x;
    }

    for (window w : windows_)
      if (w.intersect(curs_y, curs_x))
        w.update(e, curs_y, curs_x);

#ifdef DEBUG
    //::e = e;
    if (e.type != EVENT::NOEVT){
      le.type = e.type;
      le.x = e.x;
      le.y = e.y;
      le.bstate = e.bstate;
    }
    ::curs_y = curs_y; ::curs_x = curs_x;
#endif
  }

  void cursapp::draw(){
    for (window w : windows_)
      w.draw();

#ifdef DEBUG
    mvprintw(3,3, "event type: %d,;  globlcursor x coord : %d , y coord : %d", e.type, ::curs_x, ::curs_y);
    mvprintw(1,2, "last non-empty event: %d, x coord: %d, y coord: %d, bstate: %#X", le.type,le.x,le.y,le.bstate);
#endif

    refresh();
  }

  void cursapp::clear(){
    ::clear();
  }

  cursapp::cursapp(){
    nutil::init_curses();
    refresh();
  }
//  cursapp* cursapp::inst(){
//    if (!cursapp_instance){
//      cursapp_instance = new cursapp();
//    }
//    return cursapp_instance;
//  }

  std::vector<window> cursapp::partition(int n){  //horizontally partition evenly among n subwindows
    std::vector<window> result;
    int y, x;
    getmaxyx(stdscr,y,x);
    int width = x/n;
    int leftover = x%n;
    int start=0;
    int carry=0;;
    for (int i=0; i<n; ++i){
      if (leftover > 0){
        carry = 1;
        --leftover;
      }
      result.push_back(window(0,start,y,width+carry));
      addWindow(result[result.size()-1]);
      start += width + carry;
      carry = 0;
    }

    return result;
  }

  std::vector<window> cursapp::partition(std::vector<int> n){  //partition in given ratio
    std::vector<window> result;
    int y, x;
    getmaxyx(stdscr,y,x);
    int sum=0;
    int start=0;
    for (int i : n)
      sum += i;

    for (int i : n){
      int width = ((float)i / (float)sum) * x;
      result.push_back(window(0,start,y,start + width));
      addWindow(result[result.size()-1]);
      start += width;
    }

    return result;
  }

}

