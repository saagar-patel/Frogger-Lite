#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "level.h"
#include "cinder/Font.h"

namespace frogger {
class FroggerApp : public ci::app::App {
    public:
      FroggerApp();
      
      void setup() override;
      void draw() override;
      void update() override;
      
      void keyDown(ci::app::KeyEvent event) override;
      void keyUp(ci::app::KeyEvent event) override;
      
    private:
      int kWindowSizeX = 2400;
      int kWindowSizeY = 2000;
      int kTopMargin = 150;
      
      ci::gl::Texture2dRef background_;
      Level level_;
      
};
}