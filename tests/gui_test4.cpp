#include "../include/cursapp.hpp"
#include "../include/gui.hpp"

//test multiple custom forms to do a thing

int function_of_x(int x){
  return ((float)(x*x)/(float)(3));
}

int color=0;
bool dunno=false;

int boxboi=0;
int boxboi=0;

int main(){
  using namespace std::placeholders;

  ngl::cursapp m = ngl::cursapp::instance();
  auto windows = m.partition(3);

  ngl::window left_window = windows[0];
  ngl::window middle_window = windows[1];
  ngl::window right_window = windows[2];

  ngl::window bottom_right = right_window.split();
  ngl::window bottom_left  = left_window.split();

  ngl::form( middle_window,
      {"options:","-red", "-blue", "-green", "+dunno",
       "mandatories", "-powerful","-weak","-insightful"},
      [&](std::vector<ngl::nstate*> m){
        for (int i : {1,2,3})
          if (m[i]->get_state() == ngl::CHECKED)
            color=i;
        });
       

  ngl::button( left_window, {"box","line","two box","NONE"},
      [&](){}
      );
  ngl::boxform( bottom_left, {"highlight","bold","italic","alternate-charset"},
      [](){}
      );

  //display some intermediate results in top-right window?
  ngl::plot( bottom_right, {0,10,0,10}, function_of_x );

  right_window.add_entity(&state);
  m.run();
}
