#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  std::cout << std::unitbuf;
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

  sf::Vector2f cam = {0.f, 0.f};
  sf::Vector2f from_mpos = {0.f, 0.f};
  sf::Vector2f diff = {0.f, 0.f};
  float cam_zoom = 1.f;

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
    d.camera_follow(cam, 1.f);

    if (d.m_pressed(Left)) {
      from_mpos = d.scr_to_wrld(d.mpos());
      diff = cam - from_mpos;
    }

    cam_zoom -= float(d.mouse_scroll() * 0.01f);

    // draw
    //////////////////////////////////////////////////
    d._camera_view.zoom(cam_zoom);
    d.camera_view();

    if (d.m_held(Left)) {
      cam += from_mpos - d.scr_to_wrld(d.mpos());
      // d.draw_line(from_mpos, d.scr_to_wrld(d.mpos()));
    }

    d.draw_rect({0.f, 0.f}, d.ss());

    d.draw_line(cam - sf::Vector2f(10.f, 0.f), cam + sf::Vector2f(10.f, 0.f),
                sf::Color::Red);
    d.draw_line(cam - sf::Vector2f(0.f, 10.f), cam + sf::Vector2f(0.f, 10.f),
                sf::Color::Red);

    sf::Vector2f mw = d.scr_to_wrld(d.mpos());
    sf::Vector2f ms = d.wrld_to_scr(d.mpos());

    //////////////////////////////////////////////////
    d.default_view();
    // d.draw_text(d.ss() / 2.f, "Center", CenterCenter);

    d.draw_text({0.f, 0.f},
                std::format("mpos_scr: ({:.0f}, {:.0f})", ms.x, ms.y));

    d.draw_text({0.f, float(d.text.getCharacterSize())},
                std::format("mpos_world: ({:.2f}, {:.2f})", mw.x, mw.y));

    // display
    d.display();
  }

  return 0;
}
