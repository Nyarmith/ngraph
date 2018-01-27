#define DEBUG
#include "../include/cursapp.hpp"
#include "../include/gui.hpp"
//test basic prefab buttons and checboxes

int main(){
  using namespace std::placeholders;

  auto &m = ngl::cursapp::instance();
  auto windows = m.partition(2);
  windows[0].add_entity(new ngl::radiobutton("button_test_mate"));
  windows[0].add_entity(new ngl::radiobutton(7,0,"pls pls work"));
  windows[1].add_entity(new ngl::checkbox("pls work"));

  m.run();
}
