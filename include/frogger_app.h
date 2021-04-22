#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "level.h"

namespace frogger {
class FroggerApp : public ci::app::App {
    public:
      FroggerApp();
      
      void draw() override;
      void update() override;
      void keyDown(ci::app::KeyEvent event) override;
      
    private:
      Level level_;
      int kWindowSizeX = 2400;
      int kWindowSizeY = 2000;

};
}