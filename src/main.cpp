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
  //////////////////////////////////////////////////
  for (size_t i = 0; i < 2; ++i) {
    write_font_to_data("PressStart2P-Regular.ttf");
  }
  PRINT("-------------------------------------------------------------------");
  for (auto &name : list_of_names_in_data()) {
    if (name == "PressStart2P-Regular.ttf") {
      remove_data_from_data(name);
    }
  }

  exit(0);
  //////////////////////////////////////////////////
  //  global
  sf::Font font;
  char *font_data = nullptr;
  size_t font_data_size = 0;
  if (read_font_from_data("PressStart2P-Regular.ttf", &font_data,
                          &font_data_size))
    font.loadFromMemory(font_data, font_data_size);
  sf::Text text;
  text.setFont(font);

  Data *d = new Data();
  init(d, s_width, s_height, width, height, "sfml-helper");

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
    text.setString("Hello, World");
    d->ren_tex.draw(text);

    // display
    display(d, s_width, s_height);
  }

  delete d;

  return 0;
}
