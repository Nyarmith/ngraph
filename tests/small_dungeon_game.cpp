#include "../include/gui.hpp"
#include "../include/cursapp.hpp"

struct room : public ngl::gui_entity {
  room(int y, int x, int h_, int w_) y_(y), x_(x), h_(h), w_(w);
  void draw(ngl::canvas &c){
    c.rect(y_,x_,h_,w_,'#');
  }
};

struct player : public ngl::entity {
  player(int y, int x) : y_(y), x_(x) { };
  void draw(ngl::canvas &c){
    c.add_char(y_,x_,'@');
  }
  int y_, x_;
};

struct enemy : public ngl::entity {
  player(int y, int x) : y_(y), x_(x) { };
  void draw(ngl::canvas &c){
    c.add_char(y_,x_,'@'); //same as player but different color. very deep commentary
  }
  int y_, x_;
};

int main(){
  ngl::cursapp m;

  player p;
  room SW, SE, NW, NE; //boss rooms
  room W, E, N, S; //corridors

  //do stuff and make player and room relate/interact somehow
  


  m.add_entity();
}
