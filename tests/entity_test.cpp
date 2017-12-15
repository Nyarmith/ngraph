#define DEBUG
#include <functional>
#include "../include/cursapp.hpp"

class mousefollower : public ngl::entity {
  int y;
  int x;
  public:
  /* TODO: Figure out how I can pass this, see line 43
  void update(ngl::event e){
    if (e.type == ngl::EVENT::MOUSE){
      x += x - e.x;
      x += y - e.y;
    }
  };*/
  mousefollower(){ x = y = 5; }
  friend void update(const ngl::event &e, mousefollower &m);
  void draw(ngl::canvas& g){ g.square(y-1,x-1, 3, 3);}
};

void update(const ngl::event &e, mousefollower &m){
  if (e.type == ngl::EVENT::MOUSE){
    m.x = e.x;
    m.y = e.y;
  }
};


int main(){
  using namespace std::placeholders;

  nutil::init_curses();

  ngl::cursapp m;
  mousefollower r;
  ngl::window main_window(0,0,60,60);
  main_window.add_entity(&r);

  // TODO: Figure out how to pass bound method
  // main_window.add_handler(new ngl::handler(0,0,60,60,r.update));  //could also make a lambda that runs r.update()
  std::function<void(const ngl::event &e)> g = std::bind(update, _1, r);  //test could be failing due to copy semantics here
  main_window.add_handler(new ngl::handler(0,0,60,60,g));

  m.addWindow(main_window);
  m.run();
}

