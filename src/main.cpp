#include <SFML/Graphics.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 2, "sfml-helper");

  // game loop
  while (d.win.isOpen()) {
    // calculate delta time
    float delta = d.calc_delta();

    // update window title
    const int fps = int(1.f / d.delta);
    d.win.setTitle(std::format("{} | {:.2f}s | {}fps", d.title, d.delta, fps));

    // event loop
    sf::Event e;
    while (d.win.pollEvent(e)) {
      d.handle_close(e);
      d.update_mouse(e);
    }

    // clear
    d.clear();

    // update

    // draw

    // display
    d.display();
  }

  return 0;
}
