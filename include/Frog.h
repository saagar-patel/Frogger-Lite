#include "cinder/gl/gl.h"

namespace frogger {

using glm::vec2;

class Frog {
  public:
    explicit Frog(const vec2& position, const int& lives);
    
    void MoveUp() const;
    void MoveRight() const;
    void MoveLeft() const;
    void MoveDown() const;

    const vec2 &GetPosition() const;

    void SetPosition(const vec2 &position);

private:
    vec2 position_;
    float kMoveDistance = 50;
    int lives_;
};
}