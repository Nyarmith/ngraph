#include "../util/util.hpp"
#include "poller.hpp" //event
#include <functional>
#pragma once

//callback class
namespace ngl {
  class handler {
    public:
      handler(int y, int x, int h, int w, std::function<void(event&)> f=[](event &e) {return ;}) : y_(y), x_(x), h_(h), w_(w), f_(f) { };

      virtual bool intersect(int y, int x){
        return (y_ <= y && y < y_+ h_ && x_ <= x && x < x_ + w_);
      }

      virtual void handle(event &e){
        f_(e);
      }
    private:
      int y_, x_;
      int h_, w_;
      std::function<void(event &)> f_;
  };
}
