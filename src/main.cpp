#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

  // game loop
  while (d.win.isOpen()) {
    // calculate delta time
    float delta = d.calc_delta();

    // update window title
    d.update_title();

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
    sf::Vector2f center = {d.width / 2.f, d.height / 2.f};
    d.draw_line_ex(d.mpos, center, sf::Color::Green, sf::Color::Red);

    // display
    d.display();
  }

  return 0;
}
