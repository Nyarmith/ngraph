#define DEBUG
#include <functional>
#include "../include/cursapp.hpp"


//class border_and_event_test : 
void drawhandler(const ngl::event &e, ngl::canvas &c){
  if (e.type == ngl::EVENT::MOUSE){
    c.text(e.y, e.x, "xxxx");
  } else if (e.type == ngl::EVENT::KEYBD){
    std::string t = "we got a : ";
    c.text(10,10, t + static_cast<char>(e.x));
  }

  //draw border
  c.square(0,0,60,60);
}

class menudrawer : public ngl::entity{

  void update(const ngl::event &e){
  using namespace std::placeholders;
    f = std::bind(drawhandler, e, _1);
  }

  void draw(ngl::canvas &c){
    f(c);
  }
  std::function<void(ngl::canvas &g)> f;
};

int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  ngl::window main_window(0,0,60,60);

  menudrawer t;
  
  main_window.add_entity(&t);

  m.addWindow(main_window);
  m.run();
}
