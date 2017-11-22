#include "../util/util.hpp"
#pragma once

namespace ngl{
  //types of events
  enum EVENT { MOUSE, KEYBD, NOEVT };
  //event types
  struct event {
    event() { y=x=bstate=0; type=NOEVT; }
    EVENT type;
    int y,x;
    mmask_t bstate;
  };

  class poller{
    public:
      poller(WINDOW* in) : scr_(in) {
        nodelay(in, TRUE);
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
      }
      ~poller() = default;
      event poll(){
        event s;
        int c = wgetch(scr_);
        if (c == ERR)
          return -1;

        return s;
      }
      event poll_blocking(){
        nodelay(scr_, FALSE);
        int c = wgetch(scr_);
        nodelay(scr_, TRUE);
        return c;
      }

      static bool is_mouse(int c){
        if (c == KEY_MOUSE)
          return true;
        else
          return false;
      }

      static MEVENT* get_mouse_event(){
        MEVENT* event=0;
        if (getmouse(event) == OK) {
          return event;
        }
        return NULL;
      }

      std::tuple<int,int> get_mousedown_xy(){
        MEVENT m;
        int c = getch();
        if (c == KEY_MOUSE && getmouse(&m) == OK){
          return std::make_tuple(m.y, m.x);
        }
        return std::make_tuple(-1,-1);
      }

    private:
      WINDOW* scr_;
  };
}
