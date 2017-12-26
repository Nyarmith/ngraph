#include "entity.hpp"
#pragma once


namespace ngl {
  //Base Class
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
      int y_, x_;
      int h_, w_;
      std::function<void()> callback_;
  };

  class text_button : public gui_entity {
    public:
      text_button(int y, int x, int h, int w, std::string text="dflt_bttn",
          std::function<void()> c=[](){}) :
        gui_entity(y,x,h,w,c), m_(text) { }
      text_button(std::string text="dflt_bttn",
          std::function<void()> c=[](){}) : m_(text){
        x_=y_=0; h_=1; w_=m_.size();
        callback_=c;
      }
      void update(const event &e){
        if (e.type == EVENT::MOUSE && intersect(e.y, e.x)){
          toggled_ = true;
          callback_();
        } else {
          toggled_ = false;
        }
      }
      void normal_draw(canvas &c){
          c.text(y_,x_,m_);
      }
      void toggle_draw(canvas &c){
          c.text(y_,x_,"##" + m_ + "##");
      }
    private:
      std::string m_;
  };

  class checkbox : public gui_entity {
    public:
      checkbox(int y, int x, int h, int w, std::string text="dflt_chkbx",
          std::function<void()> c=[](){}) :
        gui_entity(y,x,h,w,c), m_(text) { }
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
        if (e.type == EVENT::MOUSE && intersect(e.y, e.x)){
          toggled_ = true;
          callback_();
        } else {
          toggled_ = false;
        }
      }
      void normal_draw(canvas &c){
          c.text(y_,x_,"[ ]-" + m_);
      }
      void toggle_draw(canvas &c){
          c.text(y_,x_,"[x]-" + m_);
      }
    private:
      std::string m_;
      std::function<void()> callback_;
  };

  //TODO: Add checkbox menu, multiple-selection-interactive menu, vertical menu, text-entry button, paragraph-entry form, mixed-forms
  
  /*
  class window_facade {
  };

  class form : window_facade {
  }

  don't need these classes yet */
}