#pragma once

#include "cinder/gl/gl.h"
#include "alligator.h"
#include "player.h"

namespace frogger {
    
    using glm::vec2;
    
    class Stream {
      public:
        /**
         * Constructor for the stream object
         * @param spawnpoints a vector containing vec2 with two possible spawnpoints, reset_point and spawnpoint are
         * chosen from this
         * @param min_speed minimum speed of alligator for this stream 
         * @param max_speed max speed of alligator for this stream
         * @param left_to_right represents the direction of alligator movement in this stream
         * @param top_bound upper y-coord of stream
         * @param bot_bound lower y-coord of stream
         * @param player_move_speed the base speed the player moves in this stream by current
         */
        Stream(std::vector<vec2> spawnpoints, float min_speed, float max_speed,
               bool left_to_right, float top_bound, float bot_bound, float player_move_speed);
        
        /**
         * Determine if a gator has reached the reset point
         * @param gator check if this gator has reached the reset point
         * @return boolean, true = gator has reached end, false = gator has not reached end
         */
        bool IsGatorReachedEnd(const Alligator& gator) const;
        
        /**
         * Checks if the player is within the y-bounds of the stream
         * @param player check condition for this player
         * @returnboolean, true = player is in stream, false = player is not in stream
         */
        bool isPlayerInStream(const Player &player) const;

        /**
         * Getter for the direction of the gator
         * @return boolean, true = left->right, false = right->left
         */
        bool IsLeftToRight() const;

        /**
         * Setter for the direction of the gator movement
         * @param leftToRight 
         */
        void SetLeftToRight(bool leftToRight);

        /**
         * Getter for the direction of the stream current
         * @return true = left->right, false = right -> left
         */
        bool IsStreamLeftRight() const;

        /**
         * Setter for direction of the stream
         * @param streamLeftRight true = left->right, false = right->left
         */
        void SetStreamLeftRight(bool streamLeftRight);

        /**
         * Getter for the current spawnpoint of the gators in this stream
         * @return vec2 representing the spawnpoint coords
         */
        const vec2 &GetCurrentSpawnpoint() const;

        /**
         * Setter for the current spawnpoint
         * @param currentSpawnpoint vec2 with coords of current spawnpoint
         */
        void SetCurrentSpawnpoint(const vec2 &currentSpawnpoint);

        /**
         * Setter for the reset point of the gators in this stream
         * @return vec2 representing the reset point coords
         */
        void SetResetPoint(const vec2 &resetPoint);

        /**
         * Setter for the move speed effect by the current on the player
         * @param playerMoveSpeed float representing move speed of player in current
         */
        void SetPlayerMoveSpeed(float playerMoveSpeed);

        /**
         * Getter for the move speed effect by the current on the player
         * @return float of move speed
         */
        float GetPlayerMoveSpeed() const;

        /**
         * Getter for the vector of all possible spawnpoints and reset points for this stream
         * @return a vector containing vec2s representing the coordinates of the spawnpoints
         */
        const std::vector<vec2> &GetSpawnpoints() const;

        /**
         * Getter for the vector storing all the Cars that belong to this road
         * @return vector of Alligator objects
         */
        std::vector<Alligator> &GetGators();

    private:
        int kNumGators = 2;
        std::vector<Alligator> gators_;
        float player_move_speed_;
        bool left_to_right_; //movement direction of alligators
        bool stream_left_right_; //movement direction of current
        std::vector<vec2> spawnpoints_;
        float min_speed_; //min base speed of alligators in this stream
        float max_speed_; //max base speed of alligators in this stream
        float stream_width; //width of stream in x direction
        float top_bound_; //top bound of stream in y direction
        float bot_bound_; //bot bound of stream in y direction
        vec2 current_spawnpoint_;
        vec2 reset_point;

        /**
         * Creates all the Alligator objects belonging to this stream 
         * according to the member variables of this Alligator object
         */
        void CreateGatorObstacles();
    };
}