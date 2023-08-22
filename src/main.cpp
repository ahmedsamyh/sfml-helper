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

  // std::ofstream ofs;
  // ofs.open("test.txt", std::ios::binary);

  // Data_type type = Data_type::Texture;
  // const std::string name = "PressStart2P-Regular.ttf";
  // if (ofs.is_open()) {
  //   // write data type
  //   ofs.write((char *)&type, sizeof(type));

  //   // write name size
  //   size_t name_size = name.size();
  //   ofs.write((char *)&name_size, sizeof(name_size));

  //   // write name
  //   ofs.write((char *)name.c_str(), name_size);

  //   ofs.close();
  // }

  // std::ifstream ifs;
  // ifs.open("test.txt", std::ios::binary);

  // if (ifs.is_open()) {
  //   // read type
  //   Data_type t = Data_type::Font;
  //   ifs.read((char *)&t, sizeof(t));

  //   VAR(ifs.tellg());

  //   VAR(t);

  //   // read name size
  //   size_t name_size = 0;
  //   ifs.read((char *)&name_size, sizeof(name_size));

  //   VAR(ifs.tellg());

  //   VAR(name_size);

  //   // // read name
  //   char n[1024];
  //   ifs.read(n, name_size);
  //   n[name_size] = '\0';

  //   VAR(n);

  //   ifs.close();
  // }

  // exit(0);
  // //////////////////////////////////////////////////
  // write_font_to_data("PressStart2P-Regular.ttf");

  unsigned char *font_data = nullptr;
  size_t font_data_size = 0;

  read_font_from_data("PressStart2P-Regular.ttf", &font_data, &font_data_size);

  for (auto &name : list_of_names_in_data()) {
    std::cout << name << "\n";
  }
  exit(0);
  //////////////////////////////////////////////////
  //  global
  sf::Font font;
  // unsigned char *font_data = nullptr;
  // size_t font_data_size = 0;
  // font.loadFromMemory(font_data, font_data_size);
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
