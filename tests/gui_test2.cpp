#include "../include/cursapp.hpp"
#include "../include/gui.hpp"
//have a multi-level gui that looks like a professional program
//have it graph somethign nice, with color coding

class result : public ngl::entity{
  public:
    bool bold;
    bool underline;
    bool blink;
    int color_pair;
    void draw(ngl::canvas &c){
      c.text(0,0,"wow");
    }
};

int main(){
  using namespace std::placeholders;

  ngl::cursapp m;
  auto windows = m.partition(3);
  ngl::window left_window = windows[0];
  ngl::window middle_window = windows[1];
  ngl::window right_window = windows[2];

  result state;
  //ngl::compound_menu r;

  left_window = ngl::form(
      ngl::title("ATTRIBUTES"),
      ngl::checkbox("bold", [&state](){state.bold = !state.bold;} ),
      ngl::checkbox("underlined", [&state](){state.underline = !state.underline;}),
      ngl::checkbox("blink", [&state](){state.blink = !state.blink;}),
      );
  //TODO: add mutually exclusive form here, make it so that it runs a callback on an updated state, and that you give it the function that accepts the new state when it's updatged
  middle_window = ngl::state_form(
      [&state](const ngl::form_list &l) {
        //search l like a DOM (?), then change state of "state"
      };
      ngl::title("COLOR_PAIR"),
      ngl::line(),
      ngl::title("FG COLOR"),
      ngl::checkbox("red"),
      ngl::checkbox("green"),
      ngl::checkbox("blue"),
      ngl::line(ngl::line::DOTTED),
      ngl::title("BG COLOR"),
      ngl::checkbox("teal"),
      ngl::checkbox("purple"),
      ngl::checkbox("orange"),
      ngl::line()
      );

  right_window.add_entity(&state);
  m.run();
}
