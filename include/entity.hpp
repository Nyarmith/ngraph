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

  class anon_entity : public entity {
    public:
      ~anon_entity() = default;
      anon_entity(std::function<void(canvas&)> d,
          std::function<void(const event& e)> u=[](const event&){}) :
        d_(d), u_(u) { }
      virtual void draw(canvas& g) { d_(g); };
      virtual void update(const event& e){ u_(e); };
      virtual bool intersect(int y, int x){ return true; };
      std::string getid();
    private:
      std::function<void(canvas&)> d_;
      std::function<void(const event& e)> u_;
  };
}
