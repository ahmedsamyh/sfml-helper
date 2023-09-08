#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

  UI ui(d);

  sf::Uint8 r = 0;

  // game loop
  while (d.win.isOpen()) {
    // calculate delta time
    float delta = d.calc_delta();

    // update window title
    d.update_title();

    // event loop
    sf::Event e;
    d.update_mouse();
    d.update_key();

    while (d.win.pollEvent(e)) {
      d.handle_close(e);
      d.update_mouse_event(e);
      d.update_key_event(e);
    }

    // clear
    d.clear(sf::Color{r, 0, 0, 255});

    // update

    // draw
    ui.begin({10.f, 10.f});

    if (ui.btn(0, "Button 1")) {
      std::cout << "Button 1 Pressed!\n";
    }

    r = static_cast<sf::Uint8>(ui.slider(1, float(r), 0.f, 255.f, "Red:"));

    ui.end();

    // display
    d.display();
  }

  return 0;
}
