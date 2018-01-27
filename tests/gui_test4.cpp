#include "../include/cursapp.hpp"
#include "../include/gui.hpp"

//test multiple custom forms to do a thing

double function_of_x(double x){
  return (x*x)/3.0;
}

int color=0;
bool dunno=false;
unsigned int attr_flags=0;
int boxboi=3;
int mandatories=6;

void boxboi_drawer(ngl::canvas &c){
  c.set_attr(attr_flags);
  switch(boxboi){
    case 0:
      c.rect(1,1,6,5,'o');
      break;
    case 1:
      c.text(4,4,"v-v-v-v-v-v-v-v");
      break;
    case 2:
      c.rect(1,1,3,5,'o');
      c.rect(4,2,3,3,'o');
      break;
    case 3:
      //draw nothing
      return;

  }
}

int main(){
  using namespace std::placeholders;

  ngl::cursapp &m = ngl::cursapp::instance();
  auto windows = m.partition(3);

  ngl::window left_window = windows[0];
  ngl::window middle_window = windows[1];
  ngl::window right_window = windows[2];

  ngl::window bottom_right = right_window.split();
  ngl::window bottom_left  = left_window.split();

  ngl::form( middle_window,
      {"options:","-red", "-blue", "-green", "+dunno",
       "mandatories", "-powerful","-weak","-insightful"},
      [&](ngl::nstate **m){
        for (int i : {1,2,3})
          if (m[i]->checked())
            color=i;

        dunno = m[4]->checked();

        for (int i : {6,7,8}){
          mandatories = i;
        }
        });
       

  ngl::buttonform( left_window, {"box","line","two box","NONE"},
      [&](ngl::nstate** b){
      boxboi = 3;
      for (int i : {0,1,2})
        if (b[i]->checked())
          boxboi = i;
      });

  ngl::boxform( bottom_left, {"highlight","bold","italic","alternate-charset"},
      [&](ngl::nstate** b){
      attr_flags = 0;
      if (b[0]->checked())
        attr_flags |= A_STANDOUT;
      if (b[1]->checked())
        attr_flags |= A_BOLD;
      if (b[2]->checked())
        attr_flags |= A_ITALIC;
      if (b[3]->checked())
        attr_flags |= A_ALTCHARSET;
      }
      );

  //display some intermediate results in top-right window?
  ngl::plot( bottom_right, {0,10,0,10}, function_of_x );

  right_window.add_entity(boxboi_drawer);
  m.run();
}
