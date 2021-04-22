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
    ci::gl::drawSolidCircle(player_.GetPosition(), 30);
  }

  void Level::AdvanceOneFrame() {
    MovePlayer();
  }

  Frog Level::CreateFrogPlayer(const vec2 &position, int lives) {
    Frog frog = Frog(position, lives);
    return frog;
  }

  Frog Level::GetPlayer() {
    return player_;
  }

  void Level::MovePlayer() {
    if (isMovingForward) {
      player_.MoveUp();
    } else if (isMovingDown) {
      player_.MoveDown();
    }
    if (isMovingRight) {
      player_.MoveRight();
    } else if (isMovingLeft) {
      player_.MoveLeft();
    }
  }
  
}

