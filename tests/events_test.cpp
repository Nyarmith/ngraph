#define DEBUG
#include <functional>
#include "../include/cursapp.hpp"

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

int main(){
  using namespace std::placeholders;

  nutil::init_curses();

  ngl::cursapp m;
  ngl::window main_window(0,0,60,60);

  std::function<void(const ngl::event &e)> f = std::bind(drawhandler, _1, main_window);
  main_window.add_handler(new ngl::handler(0,0,40,40,f));

  m.addWindow(main_window);
  m.run();
}
