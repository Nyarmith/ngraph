#include "entity.hpp"

namespace ngl {
  class text_entity : public entity {
    public:
      void draw(canvas &g) { g.text(text_); };
      bool intersect(int y, int x) {
        if (y == y_)
          return x >= x_ && x < x + static_cast<int>(text_.length());
        return false;
      };
    private:
      std::string text_;
  };
}
