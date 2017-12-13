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
      poller() = default;
      ~poller() = default;

      event poll(){
        event s;
        int c = getch();

        if (c == ERR)
          return s;

        //if is mouse event
        if (c == KEY_MOUSE && getmouse(&m_) == OK){
          s.type = EVENT::MOUSE;
          s.y = m_.y;
          s.x = m_.x;
          s.bstate = m_.bstate;
        } else {
          s.type = EVENT::KEYBD;
          s.y = s.x = c;
        }
        return s;
      }

      event poll_blocking(){
        nodelay(stdscr, FALSE);
        event s = poll();
        nodelay(stdscr, TRUE);
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
      MEVENT m_;
  };
}
