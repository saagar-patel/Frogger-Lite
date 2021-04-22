#include "Frog.h"
namespace frogger {
    
using glm::dot;
using glm::length;

Frog::Frog(const vec2& position, const int& lives) {
  position_ = position;
  lives_ = lives;
}

    void Frog::MoveUp() {
      position_.y = position_.y - kMoveDistance;
    }
    
    void Frog::MoveRight() {
      position_.x = position_.x + kMoveDistance;
    }
    
    void Frog::MoveLeft() {
      position_.x = position_.x - kMoveDistance;
    }
    
    void Frog::MoveDown() {
      position_.y = position_.y + kMoveDistance;
    }

    const vec2 &Frog::GetPosition() const {
      return position_;
    }

    void Frog::SetPosition(const vec2 &position) {
      position_ = position;
    }

}