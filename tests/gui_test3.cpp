#include "../include/cursapp.hpp"
#include "../include/gui.hpp"

//make a form that takes a textbox and an attribute froma radial box and then applies that to the other screen(but several at a time)
//also tests ability to pass rendering function and have that draw

std::function<void(ngl::canvas &c)> drawer_factory(){
  //TODO: return new drawing function that goes on the next line
}


int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  auto windows = m.partition(2);
  ngl::window left  = windows[0];
  ngl::window right = windows[1];

  left.add_entity(new boxform({"box","line","two boxes"}),
      [](std::vector<std::string,std::string> &s){

      });
  right.add_entity();
  
  m.run();
}
