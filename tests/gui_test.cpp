#include "../include/cursapp.hpp"
#include "../include/gui.hpp"
//have a multi-level gui that looks like a professional program
//have it graph somethign nice, with color coding

int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  ngl::window left_window (0,0,30,30);  //use screen splitting abstractions instead of fixed dimensions (something that allows a nice n-way split)
  ngl::window middle_window (0,30,30,30); //splitting is a useful abstraction, but different than partitioining
  ngl::window right_window (0,60,30,30);

  //ngl::compound_menu r;

  auto windows = m.partition(3);

  m.run();
}
