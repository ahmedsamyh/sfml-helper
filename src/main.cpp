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

  write_data_to_data(Data_type::Texture, "res/gfx/momo.png");

  exit(0);
  //////////////////////////////////////////////////
  //  global
  Data *d = new Data();
  init(d, s_width, s_height, width, height, "sfml-helper");

  sf::Texture tex;
  std::ifstream ifs;
  ifs.open("res/gfx/momo.png", std::ios::binary);
  char *data = nullptr;
  size_t data_size = 0;
  if (ifs.is_open()) {
    ifs.seekg(0, std::ios::end);
    data_size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    data = new char[data_size];

    ifs.read((char *)data, data_size);

    ifs.close();
  }

  tex.loadFromMemory(data, data_size);
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
    d->ren_tex.draw(spr);

    // display
    display(d, s_width, s_height);
  }

  delete d;

  return 0;
}
