#include "../include/cursapp.hpp"
#include "../include/gui.hpp"

int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  auto windows = m.partition(3);
  ngl::window left_window = windows[0];
  ngl::window middle_window = windows[1];
  ngl::window right_window = windows[2];

  ngl::window bottom_right = m.split(windows[2]);

  ngl::text( left_window, {"This is an interactive graphing demo","----","Click on the buttons to make the graph do different things"}, [](){} );

  ngl::form( middle_window, {"red", "blue", "green", "dunno"},
                  []( ngl::formstruct &f ){} );
  ngl::form( right_window, {"","","",""} );
  ngl::plot( bottom_right, {0,10,0,10}, function_of_x );

  right_window.add_entity(&state);
  m.run();
}
