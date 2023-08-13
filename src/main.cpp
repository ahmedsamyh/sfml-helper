#include <SFML/Graphics.hpp>
#include <format>
#include <iostream>
#include <string>
#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

static const int s_width = 1280, s_height = 720;
static const int scale = 1;
static const int width = s_width / scale;
static const int height = s_height / scale;

int main(int argc, char *argv[]) {
  // global
  sf::Clock clock;
  float delta = 0.f;
  sf::RenderWindow win;
  sf::RenderTexture ren_tex;
  sf::RectangleShape ren_rect;
  const std::string title = "sfml-helper";
  sf::Vector2f mpos;

  Data d;

  init(win, ren_tex, title, s_width, s_height, width, height);

  // variables --------------------------------------------------
  float thicc = 1.f;

  // game loop
  while (win.isOpen()) {
    // calculate delta time
    delta = clock.restart().asSeconds();

    // update window title
    const int fps = int(1 / delta);
    win.setTitle(std::format("{} | {:.2f}s | {}fps", title, delta, fps));

    // event loop
    sf::Event e;
    while (win.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        win.close();
      }

      if (e.type == sf::Event::MouseMoved) {
        mpos.x = float(e.mouseMove.x / scale);
        mpos.y = float(e.mouseMove.y / scale);
      }
    }

    // clear
    clear(ren_tex, win);

    // update
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
      thicc += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
      thicc -= 1.f;
    }
    // draw
    sf::Vector2f size = {100.f, 100.f};
    draw_rect(d, ren_tex, mpos, size, sf::Color::Transparent, sf::Color::White,
              thicc);

    // display
    display(ren_tex, ren_rect, win, s_width, s_height);
  }

  return 0;
}
