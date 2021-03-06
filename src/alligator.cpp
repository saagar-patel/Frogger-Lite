#include "alligator.h"
namespace frogger {

    Alligator::Alligator(const vec2 &spawnpoint, float speed) {
      //places corner relative to center point
      top_left_edge_ = vec2(spawnpoint.x - kHorizontalWidth / 2, spawnpoint.y - kVerticalWidth / 2);
      bot_right_edge_ = vec2(spawnpoint.x + kHorizontalWidth / 2, spawnpoint.y + kVerticalWidth / 2);
      move_speed_ = speed;
    }

    void Alligator::DrawGator() const{
      ci::gl::color(kColor);
      ci::gl::drawSolidRect(ci::Rectf(top_left_edge_, bot_right_edge_));
    }

    void Alligator::MoveGator(float difficulty_scalar, bool left_to_right) {
      if (left_to_right) {
        top_left_edge_.x += difficulty_scalar * move_speed_;
        bot_right_edge_.x += difficulty_scalar * move_speed_;
      } else {
        //uses -1.0f to flip the direction of the movement depending on left_to_right
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
      //places gator at point and modifies corner values accordingly
      top_left_edge_ = vec2(point.x - kHorizontalWidth / 2, point.y - kVerticalWidth / 2);
      bot_right_edge_ = vec2(point.x + kHorizontalWidth / 2, point.y + kVerticalWidth / 2);
    }
}