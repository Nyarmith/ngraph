#include "canvas.hpp"
#include "poller.hpp"
#pragma once

namespace ngl {
  class entity {
    public:
      virtual ~entity() = default;
      virtual void draw(canvas& g) = 0;
      virtual void update(const event& e){ };
      virtual bool intersect(int y, int x){ return true; };
      std::string getid();
  };
}
