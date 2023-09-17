#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

// TODO: Add spacing.

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
<<<<<<< HEAD
=======
    ui.begin(d.ss() / 2.f);

    ui.text("Main Menu", CenterCenter, 32);
    ui.spacing({0.f, 100.f}, CenterCenter);
    ui.btn("Play", CenterCenter);
    ui.btn("Option", CenterCenter);
    if (ui.btn("Quit", CenterCenter)) {
      return 0;
    }
>>>>>>> ui

    // display
    d.display();
  }

  return 0;
}
