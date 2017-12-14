#include "canvas.hpp"
#include "poller.hpp"
#pragma once

namespace ngl {
  class entity {
    public:
      virtual ~entity() = default;
      virtual void draw(canvas& g) = 0;
      virtual bool intersect(int y, int x) = 0;
      virtual void handle(event &e) = 0;
      std::string getid();
  };
}
