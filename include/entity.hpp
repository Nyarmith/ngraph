#include "canvas.hpp"
#pragma once

namespace ngl {
  class entity {
    public:
      virtual ~entity() = default;
      virtual void draw(canvas& g) = 0;
      virtual bool intersect(int y, int x) = 0;
      virtual void handle();
      std::string getid();
  };
}
