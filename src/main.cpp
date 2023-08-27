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
    d.camera_follow(d.mpos());

    // draw
    d.camera_view();

    d.draw_rect({0.f, 0.f}, d.ss());

    sf::Vector2f mw = d.s_to_w(d.mpos());

    d.default_view();
    d.draw_text(d.ss() / 2.f, "Center", CenterCenter);

    sf::Vector2f ms = d.w_to_s(d.mpos());

    d.draw_text({0.f, 0.f},
                std::format("mpos_scr: ({:.0f}, {:.0f})", ms.x, ms.y));

    d.draw_text({0.f, float(d.text.getCharacterSize())},
                std::format("mpos_world: ({:.2f}, {:.2f})", mw.x, mw.y));

    // display
    d.display();
  }

  return 0;
}
