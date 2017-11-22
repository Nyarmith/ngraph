#include "entity.hpp"

namespace ngl {
  class geom_entity : public entity {
    public:
      geom_entity() : height_(0), width_(0) { };
      geom_entity(int y, int x, int h, int w) : y_(y), x_(x), height_(h), width_(w) { };
      virtual ~geom_entity() = default;
    protected:
      int y_, x_;
      int height_, width_;
  };

  class square : public geom_entity {
    public:
      square() : geom_entity() { };
      square(int y, int x, int h, int w) : geom_entity(y,x,h,w) { };
      void draw(canvas& g){
        g.square(y_, x_, height_, width_);
      }
      bool intersect(int y, int x){
        if (y == y_ || y == y + height_ || x == x_ || x == x + height_)
          return true;
        return false;
      }
  };
  /* TODO : Add ellipse drawing
  class ellipse : geom_entity{
    public:
      void draw(canvas& g){
        g.ellipse(y_, x_, height_, width_);
      }
  };
  */
}
