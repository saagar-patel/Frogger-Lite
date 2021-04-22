#include "level.h"

#include <utility>
#include "cinder/Rand.h"
#include "ctime"
#include "random"
namespace frogger {
  Level::Level(int lives) : player_(CreateFrogPlayer(kSpawnPoint, lives)) {
    player_;
    player_.SetPosition(kSpawnPoint);
  }

  void Level::Display() const {
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidCircle(player_.GetPosition(), 25);
    
    ci::gl::drawStringCentered(std::to_string(player_.GetPosition().x), vec2(500, 500), ci::Color("white"));
  }

  void Level::AdvanceOneFrame() {

  }

  Frog Level::CreateFrogPlayer(const vec2 &position, int lives) {
    Frog frog = Frog(position, lives);
    return frog;
  }

  const Frog &Level::GetPlayer() const {
    return player_;
  }

}

