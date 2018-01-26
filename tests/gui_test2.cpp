#include "../include/cursapp.hpp"
#include "../include/gui.hpp"
#include <algorithm>

//test some basic gui forms
struct drawer : public ngl::entity {
  int state=0;
  void draw(ngl::canvas &c){
    switch(state){
      case 1:
        c.rect(2,2,4,4);
        break;
      case 2:
        c.text(3,3,"########");
        break;
      case 3:
        c.rect(1,1,4,4);
        c.rect(2,8,2,3);
        break;
    }
  }
};

int main(){
  using namespace std::placeholders;

  auto &m = ngl::cursapp::instance();
  auto windows = m.partition(2);
  ngl::window left_win  = windows[0];
  ngl::window right_win = windows[1];

  drawer n;

  //left window is input of checkboxes, right window is result
  ngl::boxform(left_win, {"box", "line", "two boxes"}, 
      [&n](ngl::nstate** b){
        if (b[0]->checked())
          n.state=1;
        else if (b[1]->checked())
          n.state=2;
        else if (b[2]->checked())
          n.state=3;
      });
  right_win.add_entity(&n);

  //make separate "buttonform"
  //perhaps make generic "form" ?
  m.run();
}
