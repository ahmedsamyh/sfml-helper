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

  Data *d = new Data();
  init(d, s_width, s_height, width, height, "sfml-helper");

  // variables --------------------------------------------------
  float thicc = 1.f;
  sf::Sprite spr;

  sf::Vertex q[4];

  d->tex_man.load_texture("momo.png");

  const float size = 100.f;
  const sf::Vector2f tex_size = {
      float(d->tex_man.get_texture("momo.png").getSize().x),
      float(d->tex_man.get_texture("momo.png").getSize().y)};

  q[0].position = {0.f, 0.f};
  q[1].position = {size, 0.f};
  q[2].position = {size, size};
  q[3].position = {0.f, size};

  q[0].texCoords = {0.f, 0.f};
  q[1].texCoords = {tex_size.x, 0.f};
  q[2].texCoords = {tex_size.x, tex_size.y};
  q[3].texCoords = {0.f, tex_size.y};

  spr.setTexture(d->tex_man.get_texture("momo.png"));

  // game loop
  while (d->win.isOpen()) {
    // calculate delta time
    d->delta = d->clock.restart().asSeconds();
    float delta = d->delta;

    // update window title
    const int fps = int(1 / delta);
    d->win.setTitle(std::format("{} | {:.2f}s | {}fps", d->title, delta, fps));

    // event loop
    sf::Event e;
    while (d->win.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        d->win.close();
      }

      if (e.type == sf::Event::MouseMoved) {
        d->mpos.x = float(e.mouseMove.x / scale);
        d->mpos.y = float(e.mouseMove.y / scale);
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
    clear(d);

    // update

    // draw
    // spr.setPosition(mpos);
    // ren_tex.draw(spr);

    sf::Vertex qq[4];

    sf::Vector2f q_pos = d->mpos;

    for (size_t i = 0; i < 4; ++i) {
      qq[i] = q[i];
      qq[i].position += q_pos;
    }
    sf::RenderStates states;
    states.texture = &d->tex_man.get_texture("momo.png");
    d->ren_tex.draw(qq, 4, sf::PrimitiveType::Quads, states);

    // display
    display(d, s_width, s_height);
  }

  delete d;

  return 0;
}
