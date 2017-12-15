#include "../util/util.hpp"
#include "window.hpp"

#ifdef DEBUG
    static ngl::event e;
    static ngl::event le;
    static int curs_y, curs_x;
#endif

namespace ngl {
  class cursapp {
    public:
      cursapp();
      ~cursapp() = default;
      void run();
      void addWindow(window &n);
    private:
      void update();
      void draw();
      void clear();

      std::vector<window> windows_;
      poller poller_;
  };


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
      if (w.isIntersect(curs_y, curs_x))
        w.update(e);

#ifdef DEBUG
    ::e = e;
    static event le;
    if (e.type != EVENT::NOEVT){
      le = e;
    }
    ::curs_y = curs_y; ::curs_x = curs_x;
#endif
  }

  void cursapp::draw(){
    for (window w : windows_)
      w.draw();

#ifdef DEBUG
    mvprintw(3,3, "event type: %d,;  globlcursor x coord : %d , y coord : %d", e.type, curs_x, curs_y);
    mvprintw(1,2, "last non-empty event: %d, x coord: %d, y coord: %d", le.type,le.x,le.y);
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

}
