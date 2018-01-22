#include "../include/cursapp.hpp"
#include "../include/gui.hpp" 
//make a form that takes a textbox and an attribute froma radial box and then applies that to the other screen(but several at a time)
//also tests ability to pass rendering function and have that draw

//this test currently works OK, but TODO: Make this test work fully as intended

//the reason this doesn't work may be very deeply c++
std::function<void(ngl::canvas&)> drawer_factory(std::string s){
  static int y = 1;
  static int x = 1;
  ++y;
  return [=](ngl::canvas &c){c.text(y,x,s.c_str());};
}


int main(){
  using namespace std::placeholders;

  ngl::cursapp m = ngl::cursapp::instance();
  auto windows = m.partition(2);
  ngl::window left  = windows[0];
  ngl::window right = windows[1];

  left.add_entity(new ngl::textbox(0,0,5,20,
        "type a message to enter on the right",
        //callback that somehow creates and adds new entities to other window
        [&right](std::string e){ right.add_entity(drawer_factory(e)); }
        ));

  m.run();
}
