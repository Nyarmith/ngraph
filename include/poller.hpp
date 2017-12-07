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
      poller(WINDOW* in) : scr_(in){
      }

      ~poller() = default;

      event poll(){
        event s;
        int c = wgetch(scr_);

        if (c == ERR)
          return s;

        //if is mouse event
        if (c == KEY_MOUSE && getmouse(&m_) == OK){
          s.type = EVENT::KEYBD;
          s.y = m_.y;
          s.x = m_.x;
          s.bstate = m_.bstate;
        } else {
          s.type = EVENT::MOUSE;
          s.y = s.x = c;
        }
        return s;
      }

      event poll_blocking(){
        nodelay(scr_, FALSE);
        event s = poll();
        nodelay(scr_, TRUE);
        return s;
      }

    private:
      static bool is_mouse(int c){
        if (c == KEY_MOUSE)
          return true;
        else
          return false;
      }

    private:
      WINDOW* scr_;
      MEVENT m_;
  };
}
