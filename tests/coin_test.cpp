#include <coin.h>

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

using glm::vec2;
using frogger::Coin;
using frogger::Player;

// kXRadius = 24;
// kYRadius = 30;

TEST_CASE("Test Set To Random Position") {
  Coin coin = Coin(100, 100, 0, 50);
  coin.SetToRandomPosition();
  vec2 position = coin.GetPosition();
  coin.SetToRandomPosition();
  REQUIRE(position != coin.GetPosition());
}

TEST_CASE("Test CheckCoinCollision") {
  Player player = Player(vec2(0,0), 3, 10);
  Coin coin = Coin(100, 100, 0, 50);
  coin.SetPosition(vec2(50,50));
  SECTION("Check player does collide") {
    player.SetPosition(vec2(40, 40));
    REQUIRE(coin.CheckCoinCollision(player));
  }
  SECTION("Check player does not collide") {
    player.SetPosition(vec2(-100,-100));
    REQUIRE(!coin.CheckCoinCollision(player));
  }
}