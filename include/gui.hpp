#include "cursapp.hpp"
#pragma once

//TODO: add nice comments and documentation here to make the file more readable

namespace ngl {
  //Base Class
  static const std::string CHECKED="y";
  static const std::string UNCHECKED="n";

  //TODO move state stuff to separate smaller interface struct/class

  class nstate {
    public:
      virtual const std::string& get_state(){ return state_; };
    protected:
      std::string state_ = UNCHECKED;
  };

  class gui_entity : public entity, public nstate {
    public:
      gui_entity(int y, int x, int h, int w, std::function<void()> c=[](){}) :
        y_(y), x_(x), h_(h), w_(w), callback_(c) { hover_ = toggled_ = false; }

      bool intersect(int y, int x){
        return (y_ <= y && y < y_ + h_ &&  x_ <= x && x < x_ + w_); }

      virtual void normal_draw(canvas& g)=0;
      virtual void hover_draw(canvas& g) { normal_draw(g); };
      virtual void toggled_draw(canvas& g) { normal_draw(g); };

      virtual void draw(canvas &g){
        if (toggled_)
          toggled_draw(g);
        else if (hover_)
          hover_draw(g);
        else
          normal_draw(g);
      }

      virtual void set_callback(const std::function<void()> &f){ callback_=f; }

    protected:
      gui_entity(){};
      bool hover_;
      bool toggled_;
      int y_, x_;
      int h_, w_;
      std::function<void()> callback_;
  };

  class label : public gui_entity{
    public:
      label(int y, int x, int h, int w, std::string text)
        : gui_entity(y,x,h,w){ state_ = "=" + text + "="; };

      label(int y, int x, std::string text):
        label(y,x,1,text.length()+2, text) { };

      void normal_draw(canvas& c){
        for (int i=0; i<h_ && i*w_ < (int)state_.length(); ++i){
          if ((int)state_.length() > (i+1)*w_)
            c.text( y_ + i, x_, state_.substr(i*w_, w_) );
          else
            c.text( y_ + i, x_, state_.substr(i*w_) );
        }
      }

      void update(const event&) { /* does nothing */ };
  };

  class radiobutton : public gui_entity {
    public:
      radiobutton(int y, int x, int h, int w, std::string text="dflt_bttn",
          std::function<void()> c=[](){}, int gid=0) :
        gui_entity(y,x,h,w,c), m_(text) {
          //static initialization (ask coworker if there's a better way to do this)
          if ((int)id_list_.capacity() != MAX_ID){
            id_list_.reserve(MAX_ID);
          }
          if ((int)button_groups_.capacity() != MAX_GROUP){
            button_groups_.reserve(MAX_GROUP);
            button_groups_.assign(MAX_GROUP,-1);
          }

          id_ = max_id_;
          ++max_id_;
          //TODO: use id vector to recycle ids or something

          group_ = gid;
        }

      radiobutton(int y, int x, std::string text="dflt_bttn",
          std::function<void()> c=[](){}, int gid=0) :
        radiobutton(y,x,1,text.size()+4, text, c, gid) { }  //constructor delegation!

      radiobutton(std::string text="dflt_bttn",
          std::function<void()> c=[](){}, int gid=0) :
        radiobutton(0,0,text, c, gid) { }

      ~radiobutton() { button_groups_[id_] = false; };

      void update(const event &e){
        if (e.type == EVENT::MOUSE && (e.bstate & BUTTON1_CLICKED)){
          button_groups_[group_] = id_;
          callback_();
        }
      }

      void draw(canvas &g){
        if (button_groups_[group_] == id_)
          toggled_draw(g);
        else if (hover_)
          hover_draw(g);
        else
          normal_draw(g);
      }

      void normal_draw(canvas &c){
        c.text(y_,x_,"( )-" + m_);
      }
      void toggled_draw(canvas &c){
        c.text(y_,x_,"(x)-" + m_ );
      }
      void set_group(int n){ group_ = n; }

    private:
      static int max_id_;
      static std::vector<bool> id_list_;
      static std::vector<int> button_groups_;
      const static int MAX_ID;
      const static int MAX_GROUP;
      std::string m_;
      int id_;
      int group_;
  };

  const int radiobutton::MAX_ID = 512;
  const int radiobutton::MAX_GROUP = 128;
  std::vector<bool> radiobutton::id_list_;
  std::vector<int> radiobutton::button_groups_;
  int radiobutton::max_id_ = 0;


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
          std::function<void(std::string)> c=[](std::string){}, bool clear=true) :
        gui_entity(y,x,h,w), m_(text), callback_(c), clear_(clear) {}


      void normal_draw(canvas &c){
        //draw border
        c.box( y_, x_, h_, w_);
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
            case '\n':
              callback_(m_);
              if (clear_)
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
      bool clear_;
  };


  class button : public gui_entity {
    public:
      button(int y, int x, std::function<void()> c=[](){}) : 
        gui_entity(y,x,3,m_.length()+2,c) { }

      void update(const event &e){
        if (e.type == EVENT::MOUSE && (e.bstate & BUTTON1_CLICKED)){
          toggled_ = true;
          callback_();
        }
      }

      void normal_draw(canvas &c){
        c.box(y_,x_,h_,w_,1);
        c.text(y_+1, x_+1, m_.c_str());
        c.box(y_,x_,h_,w_,1);
      }

      void toggled_draw(canvas &c){
        attron(A_STANDOUT);
        attroff(A_STANDOUT);
        toggled_ = false;  //only do toggled draw once
      }

      const static std::string m_;
  };
  const std::string button::m_ = "submit";


  /*
  class nplot : public gui_entity {
    public:
      nplot(int y, int x, int h, int w,
          int range[], int domain[], std::function<int(int)> f)
        : gui_entity(y,x,h,w), f_(f) {
          for (int i : {0,1}){  //woah this compiles
            domain_[i] = domain[i];
            range_[i] = range[i];
          }
        };

      void compute_coords(){
        //setting the graph parameters
        float x_step =  (domain_[1] - domain_[0]) / (float)w;
        
      }
      void normal_draw(canvas &c) {
        //vision: graph a plot, then draw number axes on bottom
        
        //draw dots to represent a graph I guess?
        for (int i=0; i<h_; ++i)
          for (int j=0; j<w_; ++j)
            c.add_char(y_+i, x_+j, '.');
        
        
        for (auto i : graph_)
          c.add_char(i.first, i.second, 'x');
      };
    private:
      int domain_[2];
      int range_[2];
      std::function<int(int)> f_;
      std::vector<std::pair<int,int>> graph_;
  };



  // -- Orchestrating Funcitons --
  
  //take entire window and use it to graph a plot
  void plot(window w, std::vector<int> range_domain, std::function<int(int)> f){
    if (range_domain.size() < 4)
      throw std::invalid_argument( "not enough integers passed to define a domain and range" );
    int r[2] = {range_domain[0],range_domain[1]};
    int d[2] = {range_domain[2], range_domain[3]};
    w.add_entity(new nplot(1,1,w.height() - 2, w.width() - 2, r, d, f));
          
  }
  */

  void boxform(window w, std::vector<std::string> entries, std::function<void(std::vector<nstate*>)> callback){
    int y,x;
    y=x=1;
    std::vector<nstate*> ent_capture;


    entity* c;
    for (int i=0; i<(int)entries.size(); ++i){
      c = new checkbox(y,x,entries[i]);
      w.add_entity(c);
      ent_capture.push_back(dynamic_cast<nstate*>(c));
      ++y;
    }
  }

  void buttonform(window w, std::vector<std::string> entries, std::function<void(std::vector<nstate*>)> callback){
    static int radio_group = 96;
    int y,x;
    std::vector<nstate*> ent_capture;
    y=x=1;

    entity* c;
    for (int i=0; i<(int)entries.size(); ++i){
      //TODO, define this properly
      w.add_entity(new radiobutton(y,x,entries[i], [](){},radio_group));
      ++y;
    }
    ++radio_group;
  }

  void form(window w, std::vector<std::string> entries,
      std::function<void( std::vector<nstate*> )> callback){
    std::vector<nstate*> ent_capture;
    int y,x;
    y=1; x=2;

    bool last_radio=false;
    static int radio_group = 63;

    int wdt = w.width();
    int hgt = w.height();
    entity* c;

    for (int i=0; i<(int)entries.size() && i < hgt; ++i){
      switch (entries[i][0]){
        case '-':
          if (!last_radio)
            ++radio_group;
          c = new radiobutton(y,x,entries[i], [](){}, radio_group);
          ++y;
          break;
        case '+':
          c = new checkbox(y,x,entries[i]);
          ++y;
          last_radio = false;
          break;
        case '$':
          c = new textbox(y,x+1,4,wdt-4,entries[i]);
          y+=4;
          last_radio = false;
          break;
        default:
          //just put the string there
          c = new label(y,x,entries[i]);
          ++y;
          last_radio = false;
          break;
      }

      ent_capture.push_back(dynamic_cast<nstate*>(c));

      //create button that handles the states of all these forms
      w.add_entity(new button(y,x,[=](){ callback(ent_capture); }));
      ++y;
    }
  }
}

