#ifndef _SFML_HELPER_H_
#define _SFML_HELPER_H_

#include <SFML/Graphics.hpp>

// macros ==================================================
#define is_key_held(key) sf::Keyboard::isKeyPressed(sf::Keyboard::key)
#define IF_KEY_PRESSED(block)                                                  \
  if (e.type == sf::Event::KeyPressed) {                                       \
    block                                                                      \
  }
#define is_key(k) e.key.code == sf::Keyboard::k
#define IF_KEY_RELEASED(block)                                                 \
  if (e.type == sf::Event::KeyReleased) {                                      \
    block                                                                      \
  }

// data --------------------------------------------------
struct Data {
  sf::RectangleShape rect;
  sf::CircleShape circle;
};

// math -------------------------
namespace math {
#define PI 3.14159265359

float randomf(const float min, const float max);
int randomi(const float min, const float max);
float rad2deg(const float rad);
float deg2rad(const float deg);
float map(float val, float min, float max, float from, float to);
} // namespace math

// Vector2f --------------------------------------------------
namespace v2f {
float dist(const sf::Vector2f &vec);
float mag(const sf::Vector2f &vec);
sf::Vector2f normalize(const sf::Vector2f &vec);
float radians(const sf::Vector2f &vec);
float degrees(const sf::Vector2f &vec);
sf::Vector2f normal(const sf::Vector2f &vec);
sf::Vector2f set_mag(const sf::Vector2f &v, float mag);
sf::Vector2f limit(const sf::Vector2f &v, float min, float max);
sf::Vector2f from_degrees(float deg);
sf::Vector2f from_radians(float rad);
} // namespace v2f

// Main sfml functions
void display(sf::RenderTexture &ren_tex, sf::RectangleShape &ren_rect,
             sf::RenderWindow &win, int s_width, int s_height);
void clear(sf::RenderTexture &ren_tex, sf::RenderWindow &win);
void init(sf::RenderWindow &win, sf::RenderTexture &ren_tex,
          const std::string &title, int s_w, int s_h, int w, int h);

// drawing functions
void draw_rect(Data &data, sf::RenderTarget &ren, const sf::Vector2f &pos,
               const sf::Vector2f &size,
               sf::Color fill_col = sf::Color::Transparent,
               sf::Color out_col = sf::Color::White, float out_thic = 1);

#endif /* _SFML-HELPER_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SFML_HELPER_IMPLEMENTATION
// math -------------------------
namespace math {
#define PI 3.14159265359

float randomf(const float min, const float max) {
  return (float(rand()) / float(RAND_MAX) * (max - min)) + min;
}
int randomi(const float min, const float max) {
  return int((float(rand()) / float(RAND_MAX) * (max - min)) + min);
}

float rad2deg(const float rad) { return float((rad / PI) * 180.f); }

float deg2rad(const float deg) { return float((deg / 180) * PI); }

float map(float val, float min, float max, float from, float to) {
  float normalized = val / (max - min);
  return normalized * (to - from) + from;
}

} // namespace math

// Vector2f --------------------------------------------------
namespace v2f {
float dist(const sf::Vector2f &vec) {
  return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float mag(const sf::Vector2f &vec) { return dist(vec); }

sf::Vector2f normalize(const sf::Vector2f &vec) {
  const float d = dist(vec);
  sf::Vector2f res = vec;
  if (d != 0.f) {
    res /= d;
  }

  return res;
}

float radians(const sf::Vector2f &vec) {
  float a = atan2(vec.y, vec.x);
  if (a < 0.f) {
    a += float(2 * PI);
  }
  return a;
}

float degrees(const sf::Vector2f &vec) { return math::rad2deg(radians(vec)); }

sf::Vector2f normal(const sf::Vector2f &vec) {
  return sf::Vector2f(-vec.y, vec.x);
}

sf::Vector2f set_mag(const sf::Vector2f &v, float mag) {
  return v2f::normalize(v) * mag;
}

sf::Vector2f limit(const sf::Vector2f &v, float min, float max) {
  float mag = v2f::mag(v);
  sf::Vector2f res = v;

  if (mag < min) {
    mag = min;
  }
  if (mag > max) {
    mag = max;
  }

  return v2f::set_mag(res, mag);
}

sf::Vector2f from_degrees(float deg) {
  return from_radians(math::deg2rad(deg));
}

sf::Vector2f from_radians(float rad) {
  float radians = rad;

  sf::Vector2f res;

  res.x = cos(radians);
  res.y = sin(radians);

  return res;
}

} // namespace v2f

// Main sfml functions
void display(sf::RenderTexture &ren_tex, sf::RectangleShape &ren_rect,
             sf::RenderWindow &win, int s_width, int s_height) {
  ren_tex.display();

  ren_rect.setSize(sf::Vector2f((float)s_width, (float)s_height));
  ren_rect.setTexture(&ren_tex.getTexture());

  win.draw(ren_rect);
  win.display();
}

void clear(sf::RenderTexture &ren_tex, sf::RenderWindow &win) {
  win.clear();
  ren_tex.clear();
}

void init(sf::RenderWindow &win, sf::RenderTexture &ren_tex,
          const std::string &title, int s_w, int s_h, int w, int h) {
  // create window
  win.create(sf::VideoMode(s_w, s_h), title,
             sf::Style::Close | sf::Style::Titlebar);
  win.setVerticalSyncEnabled(true);

  // create render texture
  if (!ren_tex.create(w, h)) {
    sf::err() << "ERROR: Could not create render texture!\n";
  }
}

// drawing function
void draw_rect(Data &data, sf::RenderTarget &ren, const sf::Vector2f &pos,
               const sf::Vector2f &size, sf::Color fill_col, sf::Color out_col,
               float out_thic) {
  data.rect.setPosition(pos + sf::Vector2f(out_thic, out_thic));
  data.rect.setSize(size - sf::Vector2f(out_thic, out_thic));
  data.rect.setFillColor(fill_col);
  data.rect.setOutlineColor(out_col);
  data.rect.setOutlineThickness(out_thic);

  ren.draw(data.rect);
}

#endif
