#include "../util/util.hpp"
#include "poller.hpp" //event
#pragma once

//callback class
namespace ngl {
  class handler {
    public:
      handler(int y, int x, int h, int w);
      virtual bool intersect(int y, int x){
          return (y_ <= y && y < y_+ h_ && x_ <= x && x < x_ + w_);
      }

      virtual void handle(event e) = 0;
    private:
      int y_, x_;
      int h_, w_;
  };
}
