#pragma once

#include "cinder/gl/gl.h"
#include "Frog.h"

using glm::vec2;

namespace frogger {
class Level {
    public:
      Level(int lives);
      
      void Display() const;
      
      void AdvanceOneFrame();
      
      static Frog CreateFrogPlayer(const vec2& position, int lives);

      const Frog &GetPlayer() const;
      
      

private:
      Frog player_;
      vec2 kSpawnPoint = vec2(1200, 1950);
};
}
