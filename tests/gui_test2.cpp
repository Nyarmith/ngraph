#include "../include/cursapp.hpp"
#include "../include/gui.hpp"

//test some basic gui forms

int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  auto windows = m.partition(3);
  ngl::window left_window = windows[0];
  ngl::window middle_window = windows[1];
  ngl::window right_window = windows[2];


  m.run();
}
