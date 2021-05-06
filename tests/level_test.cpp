#include <level.h>

#include <catch2/catch.hpp>

using frogger::Level;
using frogger::Player;
using frogger::Alligator;

TEST_CASE("Test Wall Collision") {
  Level level = Level();
  Player player = Player(vec2(100, 100), 3, 30);
  SECTION("Test does wall collide right") {
    level.GetPlayer().SetPosition(vec2(2400, 800));
    level.AdvanceOneFrame();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1200, 1930)); //testing that the player resets to original position
  }
  SECTION("Test does wall collide left") {
    level.GetPlayer().SetPosition(vec2(0, 800));
    level.AdvanceOneFrame();
    REQUIRE(level.GetPlayer().GetLives() == 2);
  }
  SECTION("Test does wall collide bottom") {
    level.GetPlayer().SetPosition(vec2(1100, 2000));
    level.AdvanceOneFrame();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1200, 1930));
  }
  SECTION("Test does corner collide") {
    level.GetPlayer().SetPosition(vec2(2400, 2000));
    level.AdvanceOneFrame();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1200, 1930));
  }
}

TEST_CASE("Test player move") {
  Level level = Level();
  SECTION("Move up") {
    level.SetIsMovingUp(true);
    level.MovePlayer();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1200, 1920));
  }
  SECTION("Move left") {
    level.SetIsMovingLeft(true);
    level.MovePlayer();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1190, 1930));
  }
  SECTION("Move down") {
    level.SetIsMovingDown(true);
    level.MovePlayer();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1200, 1940));
  }
  SECTION("Move right") {
    level.SetIsMovingRight(true);
    level.MovePlayer();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1210, 1930));
  }
  SECTION("Move up and left only moves up") {
    level.SetIsMovingUp(true);
    level.SetIsMovingLeft(true);
    level.MovePlayer();
    REQUIRE(level.GetPlayer().GetPosition() == vec2(1200, 1920));
  }
}

TEST_CASE("Test reset player") {
  Level level = Level();
  level.SetIsMovingUp("true");
  level.MovePlayer();
  level.MovePlayer();
  level.MovePlayer();
  level.MovePlayer();
  level.ResetPlayerPosition();
  REQUIRE(level.GetPlayer().GetPosition() == vec2(1200, 1930));
}