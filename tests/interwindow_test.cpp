#define DEBUG
#include <functional>
#include "../include/cursapp.hpp"

class option : public ngl::entity{

  public:
    option(int y, int x, int h, int w, std::string text="default text") : m_(text), y_(y), x_(x), h_(h), w_(w) { }

    void draw(ngl::canvas &c){
      if (hl){
        c.text(y_,x_,"##" + m_ + "##");
      }
      else{
        c.text(y_,x_,m_);
      }
    }

    bool intersect(int y, int x){
      return (y_ <= y && y < y_ + h_
          &&  x_ <= x && x < x_ + w_);
    }
    void update(const ngl::event &e){
      if (e.type == ngl::EVENT::MOUSE && intersect(e.y, e.x)){
        hl = true;
        callback_();
      } else {
        hl = false;
      }
    }
    void setcallback(const std::function<void()> &f){
      callback_ = f;
    }
  private:
    std::string m_;
    bool hl = false;
    int y_; 
    int x_;
    int h_; 
    int w_;
    std::function<void()> callback_ = [](){};
};

class amorphous_entity : public ngl::entity {
  int state;
  public:
  amorphous_entity(){ state = 0; };
  void update_state(int i){ state = i; }
  void draw(ngl::canvas &c){
    int y = 10, x = 10;
    switch(state){
      case 0:
        c.rect(2,2,y,x);
        break;
      case 1:
        c.text(y,x,"########");
        break;
      case 2:
        break;
    }
  }
};

int main(){
  using namespace std::placeholders;

  amorphous_entity e;

  ngl::cursapp &m = ngl::cursapp::instance();
  option a(2,5,2,15,"square");
  a.setcallback( [&e](){e.update_state(0);});
  option b(4,5,2,15,"line");
  b.setcallback( [&e](){e.update_state(1);});
  option c(6,5,2,15,"nothing");
  c.setcallback( [&e](){e.update_state(2);});
  ngl::window menu_window (0,0,20,20);
  menu_window.add_entity(&a);
  menu_window.add_entity(&b);
  menu_window.add_entity(&c);
  ngl::window results_window (20,0,20,20);
  results_window.add_entity(&e);

  m.addWindow(menu_window);
  m.addWindow(results_window);
  m.run();
}
