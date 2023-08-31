#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

  sf::Vector2f cam = {0.f, 0.f};
  sf::Vector2f from_mpos = {0.f, 0.f};

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
    d.camera_follow(cam);

    if (d.m_pressed(MB::Left)) {
      from_mpos = d.scr_to_wrld(d.mpos());
    }

    float zoom_rate = d.k_held(Key::LShift) ? 0.1f : 0.01f;

    if (d.k_pressed(Key::Num1)) {
      d.camera_zoom() = 1.f;
    }

    d.camera_zoom() -= float(d.mouse_scroll() * zoom_rate);

    // draw
    //////////////////////////////////////////////////
    d.camera_view();

    if (d.m_held(MB::Left)) {
      cam += from_mpos - d.scr_to_wrld(d.mpos());
      // d.draw_line(from_mpos, d.scr_to_wrld(d.mpos()));
    }

    d.draw_point(d.scr_to_wrld(d.mpos()));

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

    // display
    d.display();
  }

  return 0;
}
