#pragma once

#include "cinder/gl/gl.h"

namespace frogger {

using glm::vec2;

class Player {
  public:
    /**
     * Constructor for player object
     * @param position initial position of player
     * @param lives number of lives the player is allotted
     * @param radius the radius of the player object
     */
    Player(const vec2& position, const int& lives, float radius);
    
    /**
     * Moves player object up according to kMoveDistance
     */
    void MoveUp();
    
    /**
     * Moves player object right according to kMoveDistance
     */
    void MoveRight();
    
    /**
     * Moves player left according to kMoveDistance
     */
    void MoveLeft();
    
    /**
     * Moves player object down according to kMoveDistance
     */
    void MoveDown();
    
    /**
     * Draws player object
     */
    void DrawPlayer() const;
    
    /**
     * Getter for the position of the player object
     * @return a vec2 representing the position of the player in x and y coords
     */
    const vec2 &GetPosition() const;

    /**
     * Setter for the position of the player
     * @param vec vec2 with two coordinates at which to place the player
     */
    void SetPosition(const vec2& vec);

    /**
     * Getter for the radius of the player object
     * @return float of the radius of the player object
     */
    float GetRadius() const;

    /**
     * Getter for the lives of the player
     * @return int representing the lives
     */
    int GetLives() const;

    /**
     * Setter for the lives
     * @param lives integer for what you want to set the lives of the player to
     */
    void SetLives(int lives);

private:
    float kMoveDistance = 10;
    
    float radius_;
    vec2 position_;
    int lives_;
};
}