#include <cinder/Rand.h>
#include "coin.h"
namespace frogger {

    using glm::distance;
    
    Coin::Coin(float max_x_size, float max_y_size, float margin, int value) {
      max_x_ = max_x_size;
      max_y_ = max_y_size;
      margin_ = margin;
      position_ = vec2(ci::Rand::randFloat(0, max_x_ - margin_),
                       ci::Rand::randFloat(margin_, max_y_ - margin_));
      value_ = value;
      collected_ = false;
    }

    void Coin::SetToRandomPosition() {
      position_ = vec2(ci::Rand::randFloat(margin_, max_x_ - margin_),
                       ci::Rand::randFloat(margin_, max_y_ - margin_));
    }

    void Coin::DrawCoin() const{
      ci::gl::color(kColor);
      ci::gl::drawSolidEllipse(position_, kXRadius, kYRadius);
      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedEllipse(position_, kXRadius, kYRadius);
      ci::gl::drawSolidRect(ci::Rectf(vec2(position_.x - 5, position_.y + 15),
                                      vec2(position_.x + 5, position_.y - 15)));
    }

    bool Coin::CheckCoinCollision(const Player& player) {
      if(distance(player.GetPosition(), position_) < player.GetRadius() + kXRadius) {
        return true;
      }
      return false;
    }

    bool Coin::IsCollected() const {
      return collected_;
    }

    void Coin::SetIsCollected(bool collected) {
      collected_ = collected;
    }

    int Coin::GetValue() const {
      return value_;
    }
    
}



