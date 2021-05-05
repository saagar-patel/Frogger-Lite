#include "stream.h"

#include <utility>
#include <cinder/Rand.h>
#include <player.h>

namespace frogger {

    Stream::Stream(std::vector<vec2> spawnpoints, float min_speed, float max_speed, bool direction, float top_bound, float bot_bound, float player_move_speed) {
        spawnpoints_ = std::move(spawnpoints);
        max_speed_ = max_speed;
        min_speed_ = min_speed;
        stream_width = spawnpoints_[1].x - spawnpoints_[0].x;
        left_to_right_ = direction;
        stream_left_right_ = !direction;
        top_bound_ = top_bound;
        bot_bound_ = bot_bound;
        player_move_speed_ = player_move_speed;
        CreateGatorObstacles();
    }

    bool Stream::IsLeftToRight() const {
      return left_to_right_;
    }

    bool Stream::isGatorReachedEnd(const frogger::Alligator &gator) const {
      if (left_to_right_) {
        if (gator.GetTopLeftEdge().x >= reset_point.x) {
          return true;
        }
      } else {
        if (gator.GetBotRightEdge().x <= reset_point.x) {
          return true;
        }
      }
      return false;
    }

    bool Stream::isPlayerInStream(const Player &player) const {
      if (player.GetPosition().y + player.GetRadius()>= top_bound_ && player.GetPosition().y + player.GetRadius()<= bot_bound_) {
        return true;
      }
      return false;
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

    void Stream::SetResetPoint(const glm::vec2 &resetPoint) {
      reset_point = resetPoint;
    }

    void Stream::CreateGatorObstacles() {
      float speed = ci::Rand::randFloat(min_speed_, max_speed_);
      //assigns initial directions and spawnpoints 
      if (left_to_right_) {
        current_spawnpoint_ = spawnpoints_[0];
        reset_point = spawnpoints_[1];
      } else {
        current_spawnpoint_ = spawnpoints_[1];
        reset_point = spawnpoints_[0];
      }
      for (int i = 0; i < kNumGators; ++i) {
        if (left_to_right_) {
          gators_.emplace_back(Alligator(vec2(current_spawnpoint_.x + ((stream_width/static_cast<float>(kNumGators)) * static_cast<float>(i)), current_spawnpoint_.y), speed));
        } else {
          gators_.emplace_back(Alligator(vec2(current_spawnpoint_.x - ((stream_width/static_cast<float>(kNumGators)) * static_cast<float>(i)), current_spawnpoint_.y), speed));
        }
      }
    }

    float Stream::GetPlayerMoveSpeed() const {
      return player_move_speed_;
    }

    void Stream::SetPlayerMoveSpeed(float playerMoveSpeed) {
      player_move_speed_ = playerMoveSpeed;
    }

    const std::vector<vec2> &Stream::GetSpawnpoints() const {
      return spawnpoints_;
    }

    bool Stream::IsStreamLeftRight() const {
      return stream_left_right_;
    }

    void Stream::SetStreamLeftRight(bool streamLeftRight) {
      stream_left_right_ = streamLeftRight;
    }

}



