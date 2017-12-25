#include "entity.hpp"
#pragma once


namespace ngl {
  class text_button : public entity {
    public:
      text_button(int y, int x, int h, int w,
          std::string text="default button", std::function<void()> c=[](){}) :
        y_(y), x_(x), h_(h), w_(w), m_(text), callback_(c) { hl=false; };

      bool intersect(int y, int x){
        return (y_ <= y && y < y_ + h_
            &&  x_ <= x && x < x_ + w_);
      }

      void update(const event &e){
        if (e.type == EVENT::MOUSE && intersect(e.y, e.x)){
          hl = true;
          callback_();
        } else {
          hl = false;
        }
      }
      void draw(canvas &c){
        if (hl){
          //TODO, replace with colored highlight
          c.text(y_,x_,"##" + m_ + "##");
        } else {
          c.text(y_,x_,m_);
        }
      }
      void set_callback(const std::function<void()> &f){
        callback_ = f;
      }
    private:
      bool hl;
      int y_, x_;
      int h_, w_;
      std::string m_;
      std::function<void()> callback_;
  };

  class checkbox : public entity {
    public:
      text_button(int y, int x, int h, int w,
          std::string text="default button", std::function<void()> c=[](){}) :
        y_(y), x_(x), h_(h), w_(w), m_(text), callback_(c) { hl=false; };

      bool intersect(int y, int x){
        return (y_ <= y && y < y_ + h_
            &&  x_ <= x && x < x_ + w_);
      }

      void update(const event &e){
        if (e.type == EVENT::MOUSE && intersect(e.y, e.x)){
          hl = true;
          callback_();
        } else {
          hl = false;
        }
      }
      void draw(canvas &c){
        if (hl){
          //TODO, replace with colored highlight
          c.text(y_,x_,"##" + m_ + "##");
        } else {
          c.text(y_,x_,m_);
        }
      }
      void set_callback(const std::function<void()> &f){
        callback_ = f;
      }
    private:
      bool hl;
      int y_, x_;
      int h_, w_;
      std::string m_;
      std::function<void()> callback_;
  };

  //TODO: Add checkbox menu, multiple-selection-interactive menu, vertical menu, text-entry button, paragraph-entry form, mixed-forms

}
