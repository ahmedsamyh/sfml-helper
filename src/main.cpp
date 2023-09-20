#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

  Text_box tx(d, d.ss() / 2.f, {uint32_t(d.width / DEFAULT_CHAR_SIZE) - 40, 5});
  tx.add_text("Hello! Niggers of planet Earth.");
  tx.add_text("This is the second text!");

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
    tx.update();

    // draw
    tx.draw();

    ui.begin({});

    ui.text(fmt("current_text_id = {}", tx.current_text_id));
    ui.text(fmt("last_text_buffer = {}", tx.text_buffer.size() - 1));

    ui.end();

    // display
    d.display();
  }

  return 0;
}
