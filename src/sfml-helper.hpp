#ifndef _SFML_HELPER_H_
#define _SFML_HELPER_H_

#include <SFML/Graphics.hpp>

// math -------------------------
namespace math {
#define PI 3.14159265359

float randomf(const float min, const float max);
int randomi(const float min, const float max);
float rad2deg(const float rad);
float deg2rad(const float deg);
} // namespace math

// Vector2f --------------------------------------------------
namespace v2f {
float dist(const sf::Vector2f &vec);
float mag(const sf::Vector2f &vec);
sf::Vector2f normalize(const sf::Vector2f &vec);
float radians(const sf::Vector2f &vec);
float degrees(const sf::Vector2f &vec);
sf::Vector2f normal(const sf::Vector2f &vec);
} // namespace v2f

// Main sfml functions
void display(sf::RenderTexture &ren_tex, sf::RectangleShape &ren_rect,
             sf::RenderWindow &win, int s_width, int s_height);
void clear(sf::RenderTexture &ren_tex, sf::RenderWindow &win);
void init(sf::RenderWindow &win, sf::RenderTexture &ren_tex,
          const std::string &title, int s_w, int s_h, int w, int h);

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

#endif
