#include "canvas.hpp"
#include "poller.hpp"
#pragma once

namespace ngl {
  class entity {
    public:
      virtual ~entity() = default;
      virtual void draw(canvas& g) = 0;
      std::string getid();
  };
}
