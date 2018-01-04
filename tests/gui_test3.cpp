#include "../include/cursapp.hpp"
#include "../include/gui.hpp"

//test with form

int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  auto windows = m.partition(2);
  ngl::window left  = windows[0];
  ngl::window right = windows[1];

  left.add_entity(new boxform({"box","line","two boxes"}),
      [](std::vector<std::string,std::string> &s){
        
      };
  right.add_entity();
  
  m.run();
}
