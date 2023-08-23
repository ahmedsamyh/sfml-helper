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
  init(d, s_width, s_height, width, height, "sfml-helper");

  d->tex_man.load_all_textures();

  sf::Texture tex;
  Data_chunk tex_chunk{0};
  if (!read_texture_from_data(tex_chunk, "res/gfx/c++.png")) {
    exit(1);
  }
  tex.loadFromMemory(tex_chunk.data, tex_chunk.data_size);

  sf::Sprite spr;
  spr.setTexture(tex);

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
    }

    // clear
    clear(d);

    // draw
    d->draw(spr);

    // display
    display(d, s_width, s_height);
  }

  delete d;

  return 0;
}
