#include "Frog.h"
namespace frogger {
    
using glm::dot;
using glm::length;

Frog::Frog(const vec2& position, const int& lives) {
  position_ = position;
  lives_ = lives;
}

    void Frog::MoveUp() const {
      position_ + vec2(0, kMoveDistance);
    }
    
    void Frog::MoveRight() const {
      position_ + vec2(kMoveDistance, 0);
    }
    
    void Frog::MoveLeft() const{
      position_.x - vec2(kMoveDistance, 0);
    }
    
    void Frog::MoveDown() const {
      position_.y - vec2(0, kMoveDistance);
    }

    const vec2 &Frog::GetPosition() const {
      return position_;
    }

    void Frog::SetPosition(const vec2 &position) {
      position_ = position;
    }

}