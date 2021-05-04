#include "frogger_app.h"
#include "level.h"
#include "cinder/Font.h"

namespace frogger {
    
FroggerApp::FroggerApp() : level_(Level()){
    ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
}

void FroggerApp::setup() {
  auto img = ci::loadImage((loadAsset("../assets/background-complete.png")));
  background = ci::gl::Texture2d::create(img);
}

void FroggerApp::draw() {
  ci::Color bg_color("white");
  ci::gl::clear(bg_color);

  ci::gl::color(ci::Color("white"));
  ci::gl::draw(background, ci::Rectf(vec2(0,0), vec2(kWindowSizeX, kWindowSizeY)));

  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, kTopMargin - 8), vec2(kWindowSizeX, kTopMargin)));

  ci::gl::color(ci::Color("magenta"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 278), vec2(kWindowSizeX, 280)));

  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 422), vec2(kWindowSizeX, 424)));
  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 566), vec2(kWindowSizeX, 568)));
  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 710), vec2(kWindowSizeX, 712)));
  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 854), vec2(kWindowSizeX, 856)));
  
  ci::gl::color(ci::Color("magenta"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 998), vec2(kWindowSizeX, 1000)));
  
  ci::gl::drawStringCentered(
          "Level: " + std::to_string(level_.level_count_),
          glm::vec2((kWindowSizeX / 10) * 3, kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered(
          "Score: " + std::to_string(level_.score_),
          glm::vec2(kWindowSizeX / 10, kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered(
          "Lives: " + std::to_string(level_.GetPlayer().GetLives()),
          glm::vec2(9 * (kWindowSizeX / 10), kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered("Time: " + std::to_string(level_.current_time_),
                             vec2(6 * (kWindowSizeX / 10), kTopMargin/4),
                             ci::Color("Black"),
                             ci::Font("Consolas", 100));
  
  ci::gl::color(ci::Color("pink"));
  level_.Display();

  if (level_.game_over) {
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidRect(ci::Rectf(vec2(0, 0), vec2(kWindowSizeX, kWindowSizeY)));
    ci::gl::drawStringCentered(
            "Game Over",
            glm::vec2(kWindowSizeX/2, 2 * kWindowSizeY/7),
            ci::Color("white"),
            ci::Font("Consolas", 150));
    ci::gl::drawStringCentered(
            "Final Score: " + std::to_string(level_.score_),
            glm::vec2(kWindowSizeX/2, 3 * kWindowSizeY/7),
            ci::Color("white"),
            ci::Font("Consolas", 125));
    ci::gl::drawStringCentered(
            "To Exit, close window. To Replay, restart app.",
            glm::vec2(kWindowSizeX/2, 4 * kWindowSizeY/7),
            ci::Color("white"),
            ci::Font("Consolas", 60));
  }
}

void FroggerApp::update() {
    level_.AdvanceOneFrame();
}

void FroggerApp::keyDown(ci::app::KeyEvent event) {
  if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
    level_.can_move = true;
  }
  if (level_.can_move && !level_.game_over) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_w:
        level_.isMovingUp = true;
        break;

      case ci::app::KeyEvent::KEY_a:
        level_.isMovingLeft = true;
        break;

      case ci::app::KeyEvent::KEY_s:
        level_.isMovingDown = true;
        break;

      case ci::app::KeyEvent::KEY_d:
        level_.isMovingRight = true;
        break;
    }
  }
}

void FroggerApp::keyUp(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_w:
      level_.isMovingUp = false;
      break;

    case ci::app::KeyEvent::KEY_a:
      level_.isMovingLeft = false;
      break;

    case ci::app::KeyEvent::KEY_s:
      level_.isMovingDown = false;
      break;

    case ci::app::KeyEvent::KEY_d:
      level_.isMovingRight = false;
      break;
  }
}
}

