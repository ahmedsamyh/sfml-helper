#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  std::cout << std::unitbuf;
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
      d.update_mouse_event(e);
    }
    d.update_mouse();

    // clear
    d.clear();

    // update
    d.camera_follow(d.mpos());

    // draw
    //////////////////////////////////////////////////
    d.camera_view();

    d.draw_rect({0.f, 0.f}, d.ss());

    sf::Vector2f mw = d.s_to_w(d.mpos());
    sf::Vector2f ms = d.w_to_s(d.mpos());

    //////////////////////////////////////////////////
    d.default_view();
    d.draw_text(d.ss() / 2.f, "Center", CenterCenter);

    sf::Vector2f mw_from_ms = d.w_to_s(mw);

    d.draw_text({0.f, 0.f},
                std::format("mpos_scr: ({:.0f}, {:.0f})", ms.x, ms.y));

    d.draw_text({0.f, float(d.text.getCharacterSize())},
                std::format("mpos_world: ({:.2f}, {:.2f})", mw.x, mw.y));

    d.draw_text({0.f, float(d.text.getCharacterSize() * 2.f)},
                std::format("mpos_world_from_mpos_scr: ({:.2f}, {:.2f})",
                            mw_from_ms.x, mw_from_ms.y));

    // display
    d.display();
  }

  return 0;
}
