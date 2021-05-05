#include "frogger_app.h"
#include "level.h"

namespace frogger {
    
FroggerApp::FroggerApp() : level_(Level()){
    ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
}

void FroggerApp::setup() {
  //loads in and sets background_
  auto img = ci::loadImage((loadAsset("../assets/background-complete.png")));
  background_ = ci::gl::Texture2d::create(img);
}

void FroggerApp::draw() {
  ci::Color bg_color("white");
  ci::gl::clear(bg_color);

  ci::gl::color(ci::Color("white"));
  ci::gl::draw(background_, ci::Rectf(vec2(0, 0), vec2(kWindowSizeX, kWindowSizeY)));

  //Draws top border below game stats
  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, kTopMargin - 8), vec2(kWindowSizeX, kTopMargin)));

  //Draws lines that splits up streams in river
  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 422), vec2(kWindowSizeX, 424)));
  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 566), vec2(kWindowSizeX, 568)));
  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 710), vec2(kWindowSizeX, 712)));
  ci::gl::color(ci::Color("lightskyblue"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, 854), vec2(kWindowSizeX, 856)));
  
  ci::gl::drawStringCentered(
          "Level: " + std::to_string(level_.GetLevelCount()),
          glm::vec2((kWindowSizeX / 10) * 3, kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered(
          "Score: " + std::to_string(level_.GetScore()),
          glm::vec2(kWindowSizeX / 10, kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered(
          "Lives Left: " + std::to_string(level_.GetPlayer().GetLives()),
          glm::vec2(8 * (kWindowSizeX / 10), kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered(
          "Time: " + std::to_string(level_.GetCurrentTimeCount()),
          vec2(5.2 * (kWindowSizeX / 10.0), kTopMargin/4),
          ci::Color("Black"),
          ci::Font("Consolas", 100));
  
  ci::gl::color(ci::Color("pink"));
  level_.Display();

  //Draws game overlay for when game is over
  if (level_.IsGameOver()) {
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidRect(ci::Rectf(vec2(0, 0), vec2(kWindowSizeX, kWindowSizeY)));
    ci::gl::drawStringCentered(
            "Game Over",
            glm::vec2(kWindowSizeX/2, 2 * kWindowSizeY/7),
            ci::Color("white"),
            ci::Font("Consolas", 150));
    ci::gl::drawStringCentered(
            "Final Score: " + std::to_string(level_.GetScore()),
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
  //handles movement enabling at the start of each attempt
  if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
    level_.SetCanMove(true);
  }
  if (level_.IsCanMove() && !level_.IsGameOver()) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_w:
        level_.SetIsMovingUp(true);
        break;

      case ci::app::KeyEvent::KEY_a:
        level_.SetIsMovingLeft(true);
        break;

      case ci::app::KeyEvent::KEY_s:
        level_.SetIsMovingDown(true);
        break;

      case ci::app::KeyEvent::KEY_d:
        level_.SetIsMovingRight(true);
        break;
    }
  }
}

void FroggerApp::keyUp(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_w:
      level_.SetIsMovingUp(false);
      break;

    case ci::app::KeyEvent::KEY_a:
      level_.SetIsMovingLeft(false);
      break;

    case ci::app::KeyEvent::KEY_s:
      level_.SetIsMovingDown(false);
      break;

    case ci::app::KeyEvent::KEY_d:
      level_.SetIsMovingRight(false);
      break;
  }
}
}

