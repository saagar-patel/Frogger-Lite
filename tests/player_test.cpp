#include <player.h>

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include "cinder/gl/gl.h"

using glm::vec2;
using frogger::Player;


TEST_CASE("Test Player Movement") {
  Player player = Player(vec2(100, 100), 3, 30);
  SECTION("Move Up") {
    player.MoveUp();
    REQUIRE(player.GetPosition() == vec2(100, 90));
  }
  SECTION("Move Left") {
    player.MoveLeft();
    REQUIRE(player.GetPosition() == vec2(90, 100));
  }
  SECTION("Move Right") {
    player.MoveRight();
    REQUIRE(player.GetPosition() == vec2(110, 100));
  }
  SECTION("Move Down") {
    player.MoveDown();
    REQUIRE(player.GetPosition() == vec2(100, 110));
  }
  
}
