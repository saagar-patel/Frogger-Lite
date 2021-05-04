#include "stream.h"

#include <utility>
#include <cinder/Rand.h>
#include <Player.h>

namespace frogger {
    bool Stream::isLeftToRight() const {
      return left_to_right_;
    }

    Stream::Stream(std::vector<vec2> spawnpoints, float min_speed, float max_speed, bool direction, float top_bound, float bot_bound) {
        spawnpoints_ = std::move(spawnpoints);
        max_speed_ = max_speed;
        min_speed_ = min_speed;
        stream_width = spawnpoints_[1].x - spawnpoints_[0].x;
        left_to_right_ = direction;
        top_bound_ = top_bound;
        bot_bound_ = bot_bound;
    }

    bool Stream::isGatorReachedEnd(const frogger::Alligator &gator) const {
      if (left_to_right_) {
        if (gator.GetTopLeftEdge().x >= reset_point.x) {
          return true;
        }
      } else if (!left_to_right_) {
        if (gator.GetBotRightEdge().x <= reset_point.x) {
          return true;
        }
      }
      return false;
    }

    bool Stream::isGatorInStream(const Player &player) const {
      if (player.GetPosition().y <= top_bound_ && player.GetPosition().y > bot_bound_) {
        return true;
      } else {
        return false;
      }
    }
    
    void Stream::SetLeftToRight(bool leftToRight) {
      left_to_right_ = leftToRight;
    }

    const glm::vec2 &Stream::GetCurrentSpawnpoint() const {
      return current_spawnpoint_;
    }

    void Stream::SetCurrentSpawnpoint(const glm::vec2 &currentSpawnpoint) {
      current_spawnpoint_ = currentSpawnpoint;
    }

    const glm::vec2 &Stream::GetResetPoint() const {
      return reset_point;
    }

    void Stream::SetResetPoint(const glm::vec2 &resetPoint) {
      reset_point = resetPoint;
    }

    void Stream::CreateGatorObstacles() {
      float speed = ci::Rand::randFloat(min_speed_, max_speed_);
      std::vector<vec2> new_spawnpoints;
      if (left_to_right_) {
        current_spawnpoint_ = spawnpoints_[0];
        reset_point = spawnpoints_[1];
      } else {
        current_spawnpoint_ = spawnpoints_[1];
        reset_point = spawnpoints_[0];
      }

      for (int i = 0; i < kNumGators; ++i) {
        vec2 sp_point = vec2(0,0);
        if (left_to_right_) {
          sp_point = vec2(current_spawnpoint_.x + ((stream_width/static_cast<float>(kNumGators)) * static_cast<float>(i)), current_spawnpoint_.y);
        } else {
          sp_point = vec2(current_spawnpoint_.x - ((stream_width/static_cast<float>(kNumGators)) * static_cast<float>(i)), current_spawnpoint_.y);
        }
        new_spawnpoints.emplace_back(sp_point);
      }

      for (int i = 0; i < kNumGators; ++i) {
        gators_.emplace_back(Alligator(new_spawnpoints[i], speed));
      }
    }

    float Stream::GetKPlayerMoveSpeed() const {
      return kPlayerMoveSpeed;
    }

}



