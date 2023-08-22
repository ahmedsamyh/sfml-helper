#ifndef _SFML_HELPER_H_
#define _SFML_HELPER_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

#define VAR(name) std::cout << #name << ": " << name << "\n"

// data.dat ==================================================
enum Data_type { Font, Texture, Sound };

/* data.dat format
   [data_type]
   [data_size]
   [name_size]
   [name]
   [data]
   ...
 */

std::vector<std::string> list_of_names_in_data() {
  std::ifstream ifs;
  std::vector<std::string> names;
  ifs.open("data.dat", std::ios::binary | std::ios::in);
  if (ifs.is_open()) {
    size_t looped = 0;
    while (ifs.rdstate() != std::ios::eofbit) {
      // read data type
      Data_type type = (Data_type)0;
      ifs.read((char *)&type, 1);

      VAR(type);

      // read data size
      size_t size = 0;
      ifs.read((char *)&size, 8);

      VAR(size);

      // read name size
      size_t name_size = 0;
      ifs.read((char *)&name_size, 8);

      VAR(name_size);

      // read name
      char *name = nullptr;
      name = new char[name_size];
      ifs.read(name, name_size);
      std::string name_str = name;

      // add to names
      names.push_back(name_str);
      delete name;

      // read data

      looped++;
      std::cout << "looped: " << looped << "\n\n";

      if (looped >= 1000) {
        exit(1);
      }
    }
    ifs.close();
    return names;
  }
  sf::err() << "ERROR: Could not open `data.dat`!\n";
  return names;
}

bool write_font_to_data(const std::string &font_filename) {
  std::ifstream ifs;
  ifs.open(font_filename, std::ios::binary);

  unsigned char *bytes = nullptr;
  size_t bytes_size = 0;

  if (ifs.is_open()) {
    ifs.seekg(0, std::ios::end);
    bytes_size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    bytes = new unsigned char[bytes_size];

    ifs.read((char *)bytes, bytes_size);

    ifs.close();
  } else {

    return false;
  }

  std::ofstream ofs;
  ofs.open("data.dat", std::ios::binary | std::ios::app);

  if (ofs.is_open()) {
    // write data type {1 byte(s)}
    Data_type type = Data_type::Font;
    ofs.write((char *)&type, sizeof(type));

    // write data size {8 byte(s)}
    ofs.write((char *)&bytes_size, sizeof(bytes_size));

    // write name size {8 byte(s)}
    size_t name_size = font_filename.size();
    ofs.write((char *)&name_size, sizeof(name_size));

    // write name
    ofs.write(font_filename.c_str(), name_size);

    // write data
    ofs.write((char *)bytes, bytes_size);

    ofs.close();
  } else {
    sf::err() << "ERROR: Could not open `data.dat`\n";
    return false;
  }
  std::cout << "Successfully written `" << font_filename << "` to `data.dat`\n";
  return true;
}

bool read_font_from_data(const std::string &font_name,
                         unsigned char **font_data, size_t *font_data_size) {
  std::ifstream ifs;
  ifs.open("data.dat", std::ios::binary);
  if (ifs.is_open()) {
    while (!ifs.eof()) {
      // read data type
      Data_type type = Data_type::Font;
      ifs.read((char *)&type, sizeof(type));

      VAR(ifs.tellg());

      VAR(type);

      switch (type) {
      case Data_type::Font: {

        // read data size
        size_t size = 0;
        ifs.read((char *)&size, sizeof(size));
        *font_data_size = size;

        VAR(size);

        // read name size
        size_t name_size = 0;
        ifs.read((char *)&name_size, sizeof(name_size));

        VAR(name_size);

        // TODO: Name buffer size is 1024, maybe make it a macro
        // read name
        char name[1024];
        ifs.read((char *)&name, name_size);
        name[name_size] = '\0';
        std::string name_str = name;

        // read data
        ifs.read((char *)*font_data, size);

        if (name == font_name) {
          return true;
        }

      } break;
      case Data_type::Texture: {
        std::cerr << "ERROR: Unimplemented `read_font_from_data`!\n";
        exit(1);
      } break;
      case Data_type::Sound: {
        std::cerr << "ERROR: Unimplemented `read_font_from_data`!\n";
        exit(1);
      } break;
      default: {
        std::cerr << "ERROR: Data type is invalid in `read_font_from_data`!\n";
        exit(1);
      } break;
      }
    }
    ifs.close();
    std::cerr << "ERROR: Could not find font `" << font_name
              << "` in `data.dat`!!!\n";
    return false;
  }
  std::cerr << "ERROR: Could not open `data.dat`\n";
  return false;
}

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

// texture_manager --------------------------------------------------
struct Texture_manager {
  std::unordered_map<std::string, sf::Texture> textures;

  sf::Texture &load_texture(const std::string &filename);

  sf::Texture &get_texture(const std::string &filename);

  static std::string texture_path;
};
// data --------------------------------------------------
struct Data {
  sf::RectangleShape rect;
  sf::CircleShape circle;
  sf::RenderWindow win;
  sf::RenderTexture ren_tex;
  sf::RectangleShape ren_rect;
  sf::Clock clock;
  float delta = 0.f;
  std::string title = "sfml-helper";
  sf::Vector2f mpos;
  Texture_manager tex_man;
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
void display(Data *d, int s_width, int s_height);
void clear(Data *d);
void init(Data *data, int s_w, int s_h, int w, int h, const std::string &title);

// drawing functions
void draw_rect(Data &data, sf::RenderTarget &ren, const sf::Vector2f &pos,
               const sf::Vector2f &size,
               sf::Color fill_col = sf::Color::Transparent,
               sf::Color out_col = sf::Color::White, float out_thic = 1);

#endif /* _SFML-HELPER_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SFML_HELPER_IMPLEMENTATION

// texture_manager --------------------------------------------------
std::string Texture_manager::texture_path = "res/gfx/";

sf::Texture &Texture_manager::load_texture(const std::string &filename) {
  // return the texture if it already exists
  if (textures.contains(filename)) {
    return textures.at(filename);
  }

  // load new texture
  sf::Texture tex;
  if (!tex.loadFromFile(Texture_manager::texture_path + filename)) {
    std::cerr << "ERROR: could not load texture '" << filename << "'\n";
    exit(1);
  }
  textures.insert({filename, tex});
  return textures.at(filename);
}

sf::Texture &Texture_manager::get_texture(const std::string &filename) {
  // return the texture if it already exists
  if (!textures.contains(filename)) {
    std::cerr << "ERROR: the texture '" << filename
              << "' doesn't exist or isn't loaded!\n";
    exit(1);
  }

  return textures.at(filename);
}

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
void display(Data *d, int s_width, int s_height) {
  d->ren_tex.display();

  d->ren_rect.setSize(sf::Vector2f((float)s_width, (float)s_height));
  d->ren_rect.setTexture(&d->ren_tex.getTexture());

  d->win.draw(d->ren_rect);
  d->win.display();
}

void clear(Data *d) {
  d->win.clear();
  d->ren_tex.clear();
}

void init(Data *d, int s_w, int s_h, int w, int h, const std::string &title) {
  d->title = title;

  // create window
  d->win.create(sf::VideoMode(s_w, s_h), title,
                sf::Style::Close | sf::Style::Titlebar);
  d->win.setVerticalSyncEnabled(true);

  // create render texture
  if (!d->ren_tex.create(w, h)) {
    std::cerr << "ERROR: Could not create render texture!\n";
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
