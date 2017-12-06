#include <functional>
#include "../include/window.hpp"

void drawhandler(const ngl::event &e, ngl::canvas &c){
  if (e.type == ngl::EVENT::MOUSE){
    c.text(e.y, e.x, "x");
  }
}

int main(){
  using namespace std::placeholders;
  initscr(); //may not be necessary with the individual newwin()s and initscr()s

  ngl::window main_window(0,0,60,60);

  std::function<void(const ngl::event &e)> f = std::bind(drawhandler, _1, main_window);
  main_window.add_handler(new ngl::handler(0,0,40,40,f));

  while(true){
    //main_window.clear();  //if you want new frames every second, uncomment this
    main_window.update();
    main_window.refresh();
    usleep(33000);
  }

}
