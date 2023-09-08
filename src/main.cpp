#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

  UI ui(d);

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
    d.clear();

    // update

    // draw
    ui.begin({0.f, 0.f});

    if (ui.btn(0, "button")) {
      std::cout << "Button Pressed!\n";
    }
    if (ui.btn(1, "button2")) {
      std::cout << "Button2 Pressed!\n";
    }

    ui.end();
    // display
    d.display();
  }

  return 0;
}
