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
  Texture_manager tex_man;

  init(win, ren_tex, title, s_width, s_height, width, height);

  // variables --------------------------------------------------
  float thicc = 1.f;
  sf::Sprite spr;

  sf::Vertex q[4];

  tex_man.load_texture("momo.png");

  const float size = 100.f;
  const sf::Vector2f tex_size = {
      float(tex_man.get_texture("momo.png").getSize().x),
      float(tex_man.get_texture("momo.png").getSize().y)};

  q[0].position = {0.f, 0.f};
  q[1].position = {size, 0.f};
  q[2].position = {size, size};
  q[3].position = {0.f, size};

  q[0].texCoords = {0.f, 0.f};
  q[1].texCoords = {tex_size.x, 0.f};
  q[2].texCoords = {tex_size.x, tex_size.y};
  q[3].texCoords = {0.f, tex_size.y};

  spr.setTexture(tex_man.get_texture("momo.png"));

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

      IF_KEY_PRESSED({
        if (is_key(Space)) {
          std::cout << "Space\n";
        }
        if (is_key(Enter)) {
          std::cout << "Enter\n";
        }
      });

      IF_KEY_RELEASED({
        if (is_key(Space)) {
          std::cout << "Space Released\n";
        }
      });
    }

    // clear
    clear(ren_tex, win);

    // update

    // draw
    // spr.setPosition(mpos);
    // ren_tex.draw(spr);

    sf::Vertex qq[4];

    sf::Vector2f q_pos = mpos;

    for (size_t i = 0; i < 4; ++i) {
      qq[i] = q[i];
      qq[i].position += q_pos;
    }
    sf::RenderStates states;
    states.texture = &tex_man.get_texture("momo.png");
    ren_tex.draw(qq, 4, sf::PrimitiveType::Quads, states);

    // display
    display(ren_tex, ren_rect, win, s_width, s_height);
  }

  return 0;
}
