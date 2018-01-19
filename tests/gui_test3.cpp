#include "../include/cursapp.hpp"
#include "../include/gui.hpp"

//make a form that takes a textbox and an attribute froma radial box and then applies that to the other screen(but several at a time)
//also tests ability to pass rendering function and have that draw

std::function<void(ngl::canvas &c)> drawer_factory(std::string s){
  static int y = 1;
  static int x = 1;
  ++y;
  return [s](ngl::canvas &c){ c.text(y,x,s.c_str());};
}


int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  auto windows = m.partition(2);
  ngl::window left  = windows[0];
  ngl::window right = windows[1];

  left.add_entity(new ngl::textbox(0,0,30,30,
        //callback that somehow creates and adds new entities to other window
        ));
  right.add_entity();
  
  m.run();
}
