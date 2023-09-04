#define NO_WARNING
#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 2, "sfml-helper");

  int pressed = 0;
  int correct = 0;

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
      d.update_mouse_event(e);
    }
    d.update_mouse();
    d.update_key();

    // clear
    d.clear();

    // update
    if (d.k_pressed(Key::Space)) {
      for (size_t i = 0; i < 1000; ++i) {
        if (math::chance(1.f)) {
          correct++;
        }
        pressed++;
      }
      std::cout << correct << "/" << pressed << "\n";
    }

    // draw

    // display
    d.display();
  }

  return 0;
}
