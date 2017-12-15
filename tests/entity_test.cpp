#define DEBUG
#include <functional>
#include "../include/cursapp.hpp"

class mousefollower : public ngl::entity {
  int y;
  int x;
  public:
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

  ngl::cursapp m;
  mousefollower r;
  ngl::window main_window(0,0,60,60);
  main_window.add_entity(&r);

  main_window.add_handler(new ngl::handler(0,0,60,60,
        [&r](const ngl::event &e){ r.update(e); }) );

  m.addWindow(main_window);
  m.run();
}

