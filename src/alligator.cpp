#include "alligator.h"
namespace frogger {

    Alligator::Alligator(const vec2 &spawnpoint, float speed) {
      top_left_edge_ = vec2(spawnpoint.x - kHorizontalWidth / 2, spawnpoint.y - kVerticalWidth / 2);
      bot_right_edge_ = vec2(spawnpoint.x + kHorizontalWidth / 2, spawnpoint.y + kVerticalWidth / 2);
      move_speed_ = speed;
    }

    void Alligator::DrawGator() const{
      ci::gl::color(kColor);
      ci::gl::drawSolidRect(ci::Rectf(top_left_edge_, bot_right_edge_));
    }

    void Alligator::MoveGator(float difficulty_scalar, bool direction) {
      if (direction) {
        top_left_edge_.x += difficulty_scalar * move_speed_;
        bot_right_edge_.x += difficulty_scalar * move_speed_;
      } else {
        top_left_edge_.x += (-1.0f * difficulty_scalar * move_speed_);
        bot_right_edge_.x += (-1.0f * difficulty_scalar * move_speed_);
      }
    }

    const vec2 &Alligator::GetTopLeftEdge() const {
      return top_left_edge_;
    }

    const vec2 &Alligator::GetBotRightEdge() const {
      return bot_right_edge_;
    }

    void Alligator::PlaceGator(const vec2 &point) {
      top_left_edge_ = vec2(point.x - kHorizontalWidth / 2, point.y - kVerticalWidth / 2);
      bot_right_edge_ = vec2(point.x + kHorizontalWidth / 2, point.y + kVerticalWidth / 2);
    }
}