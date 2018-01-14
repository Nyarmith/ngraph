#include "cursapp.hpp"
#pragma once


namespace ngl {
  //Base Class
  static const std::string CHECKED="y";
  static const std::string UNCHECKED="n";

  class gui_entity : public entity {
    public:
      gui_entity(int y, int x, int h, int w, std::function<void()> c=[](){}) :
        y_(y), x_(x), h_(h), w_(w), callback_(c) { hover_ = toggled_ = false; }

      bool intersect(int y, int x){
        return (y_ <= y && y < y_ + h_ &&  x_ <= x && x < x_ + w_); }

      virtual void normal_draw(canvas& g)=0;
      virtual void hover_draw(canvas& g) { normal_draw(g); };
      virtual void toggled_draw(canvas& g) { normal_draw(g); };

      void draw(canvas &g){
        if (toggled_)
          toggled_draw(g);
        else if (hover_)
          hover_draw(g);
        else
          normal_draw(g);
      }

      void set_callback(const std::function<void()> &f){ callback_=f; }
    protected:
      gui_entity(){};
      bool hover_;
      bool toggled_;
      std::string state_ = UNCHECKED;
      int y_, x_;
      int h_, w_;
      std::function<void()> callback_;
  };

  class text_button : public gui_entity {
    public:
      text_button(int y, int x, int h, int w, std::string text="dflt_bttn",
          std::function<void()> c=[](){}) :
        gui_entity(y,x,h,w,c), m_(text) { }
      text_button(int y, int x, std::string text="dflt_bttn",
          std::function<void()> c=[](){}) : m_(text){
        x_=x; y_=y; h_=1; w_=m_.size()+4;
        callback_=c;
      }
      text_button(std::string text="dflt_bttn",
          std::function<void()> c=[](){}) : m_(text){
        x_=y_=0; h_=1; w_=m_.size()+4;
        callback_=c;
      }
      void update(const event &e){
        if (e.type == EVENT::MOUSE && (e.bstate & BUTTON1_CLICKED)){
          toggled_ = !toggled_;
          callback_();
          if(toggled_)
            state_ = CHECKED;
          else
            state_ = UNCHECKED;
        } 
      }
      void normal_draw(canvas &c){
          c.text(y_,x_,"( )-" + m_);
      }
      void toggled_draw(canvas &c){
          c.text(y_,x_,"(x)-" + m_ );
      }
    private:
      std::string m_;
  };

  class checkbox : public gui_entity {
    public:
      checkbox(int y, int x, int h, int w, std::string text="dflt_chkbx",
          std::function<void()> c=[](){}) :
        gui_entity(y,x,h,w,c), m_(text) { }
      checkbox(int y, int x, std::string text="dflt_bttn",
          std::function<void()> c=[](){}) : m_(text){
        x_=x; y_=y; h_=1; w_=m_.size();
        callback_=c;
      }
      checkbox(std::string text="dflt_chkbx",
          std::function<void()> c=[](){}) : m_(text){
        x_=y_=0; h_=1; w_=m_.size()+4;
        callback_=c;
      }

      bool intersect(int y, int x){
        return (y_ <= y && y < y_ + h_
            &&  x_ <= x && x < x_ + w_);
      }
      void update(const event &e){
        if (e.type == EVENT::MOUSE && (e.bstate & BUTTON1_CLICKED)){
          toggled_ = !toggled_;
          callback_();
          if(toggled_)
            state_ = CHECKED;
          else
            state_ = UNCHECKED;
        } 
      }
      void normal_draw(canvas &c){
          c.text(y_,x_,"[ ]-" + m_);
      }
      void toggled_draw(canvas &c){
          c.text(y_,x_,"[x]-" + m_);
      }
    private:
      std::string m_;
  };

  //TODO: need better defaults for gui_entity(), also to redo defaults for above. refactor constructors somehow?
  class textbox : public gui_entity{
    textbox(int y, int x, int h, int w, std::string text="[type here]",
        std::function<void()> c=[](){}) :
      gui_entity(y,x,h,w,c), m_(text) { }
    textbox(int y, int x, std::string text="[type here]",
        std::function<void()> c=[](){}) : m_(text){
      x_=y_=0; h_=2; w_=m_.size();
    }
    private:
      std::string m_;
  };

  //class stringform : public gui_entity {
  //}


  void boxform(window w, std::vector<std::string> entries, std::function<void(bool[])> callback){
    int y,x;
    y=x=1;
    bool* cb = new bool[entries.size()];
    for (int i=0; i<(int)entries.size(); ++i){
      cb[i] = 0;
      w.add_entity(new checkbox(y,x,entries[i],[cb,i,callback](){cb[i]=!cb[i]; callback(cb);}));
      ++y;
    }
  }

  void buttonform(window w, std::vector<std::string> entries, std::function<void(bool[])> callback){
    int y,x;
    y=x=1;
    int n = (int)entries.size();
    bool* cb = new bool[entries.size()];
    for (int i=0; i<(int)entries.size(); ++i){
      cb[i] = 0;
      w.add_entity(new text_button(y,x,entries[i],[n,cb,i,callback](){cb[i]=!cb[i]; callback(cb);})); //fuck how do I untoggle
      ++y;
    }
  }

  /* TODO: Complete this after stringform has been created and buttonform's logic has been sorted out
  void form(window w, std::vector<std::string> entries, std::function<void(bool[])> callback){
    int y,x;
    y=x=1;
    bool* cb = new bool[entries.size()];
    entity* c;
    for (int i=0; i<(int)entries.size(); ++i){
      cb[i] = 0;
      switch (entries[i][0]){
        case '-':
          c = new text_button(y,x,entries[i]);
          ++y;
          break;
        case '+':
          c = new checkbox(y,x,entries[i]);
          ++y;
          break;
        case '$':
          c = new checkbox(y,x,entries[i]);
          ++y;
          break;
        default:
          break;
      }
      w.add_entity(new text_button(y,x,entries[i],[cb,i,callback](){cb[i]=!cb[i]; callback(cb);}));
      ++y;
    }
  }
  */

}
