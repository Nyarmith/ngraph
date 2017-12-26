#include "../include/cursapp.hpp"
#include "../include/gui.hpp"
//test basic prefab buttons and checboxes

int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  auto windows = m.partition(2);
  windows[0].add_entity(new ngl::text_button());
  windows[1].add_entity(new ngl::checkbox());

  m.run();
}
