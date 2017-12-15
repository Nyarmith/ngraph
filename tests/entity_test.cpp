#define DEBUG
#include <functional>
#include "../include/cursapp.hpp"

class mousefollower : public ngl::entity {
  int y;
  int x;
  public:
  //TODO: Figure out how I can pass this, see line 43
  void update(ngl::event e){
    if (e.type == ngl::EVENT::MOUSE){
      x = e.x;
      y = e.y;
    }
  };
  void draw(ngl::canvas& g){ g.square(y-1,x-1, 3, 3);}
  mousefollower(){ x = y = 5; }
};

int main(){
  using namespace std::placeholders;

  nutil::init_curses();

  ngl::cursapp m;
  mousefollower r;
  ngl::window main_window(0,0,60,60);
  main_window.add_entity(&r);
  std::function<void(const ngl::event &e)> f = [&r](const ngl::event &e){r.update(e);};

  // TODO: Figure out how to pass bound method
  main_window.add_handler(new ngl::handler(0,0,60,60,f));

  m.addWindow(main_window);
  m.run();
}

