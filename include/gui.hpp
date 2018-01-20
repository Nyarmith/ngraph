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

  class radiobutton : public gui_entity {
    public:
      radiobutton(int y, int x, int h, int w, std::string text="dflt_bttn",
          std::function<void()> c=[](){}) :
        gui_entity(y,x,h,w,c), m_(text) { }
      radiobutton(int y, int x, std::string text="dflt_bttn",
          std::function<void()> c=[](){}) : m_(text){
        x_=x; y_=y; h_=1; w_=m_.size()+4;
        callback_=c;
      }
      radiobutton(std::string text="dflt_bttn",
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

  class textbox : public gui_entity{
    public:
    textbox(int y, int x, int h, int w, std::string text="[type here]",
        std::function<void(std::string)> c=[](std::string m){}) :
      gui_entity(y,x,h,w), m_(text), callback_(c) { }
      

    void normal_draw(canvas &c){
      //draw border
      c.rect( y_, x_, h_, w_);
      //dimensions of drawable portion
      int y=y_+1;
      int x=x_+1;
      int w = w_ - 2;
      int h = h_ - 2;
      for (int i=0; i<h && i*w < (int)m_.length(); ++i){
        if ((int)m_.length() > (i+1)*w)
          c.text( y + i, x, m_.substr(i*w, w) );
        else
          c.text( y + i, x, m_.substr(i*w) );
      }
    }

    void update(const event &e){
      if (e.type == EVENT::KEYBD){
        switch(e.x){
          case KEY_ENTER:
            callback_(m_);
            m_ = "";
            break;
          case KEY_BACKSPACE:
            if (m_.size() > 0)
              m_ = m_.substr(0,m_.size()-1);
            break;
          default:
            if ((int)m_.length() < (w_-2)*(h_-2))
                m_ += static_cast<char>(e.x);
            break;
        }
      }
    }

    //TODO: make toggled_ state happen and toggled_draw() thing happen

    private:
    std::string m_;
    std::function<void(std::string)> callback_;
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
      w.add_entity(new radiobutton(y,x,entries[i],[n,cb,i,callback](){cb[i]=!cb[i]; callback(cb);})); //fuck how do I untoggle
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
