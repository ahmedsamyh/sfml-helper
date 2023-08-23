#include <SFML/Graphics.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

static const int s_width = 1280, s_height = 720;
static const int scale = 2;
static const int width = s_width / scale;
static const int height = s_height / scale;

int main(int argc, char *argv[]) {
  //  global
  Data *d = new Data();
  init(d, 1280, 720, 2, "sfml-helper");

  sf::Sprite spr;
  spr.setTexture(d->tex_man.get_texture("res/gfx/momo.png"));

  // game loop
  while (d->win.isOpen()) {
    // calculate delta time
    d->delta = d->clock.restart().asSeconds();

    // update window title
    const int fps = int(1.f / d->delta);
    d->win.setTitle(
        std::format("{} | {:.2f}s | {}fps", d->title, d->delta, fps));

    // event loop
    sf::Event e;
    while (d->win.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        d->win.close();
      }
      d->update_mouse(e);
    }

    // clear
    clear(d);

    // update
    spr.setPosition(d->mpos);

    // draw
    d->draw(spr);

    // display
    d->display();
  }

  delete d;

  return 0;
}
