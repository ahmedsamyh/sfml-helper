#ifndef _SFML_HELPER_H_
#define _SFML_HELPER_H_

#include <SFML/Graphics.hpp>
#include <format>
#include <string>
#include <unordered_map>

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
#define VAR(name) std::cout << #name << ": " << name << "\n"
#define VAR_STR(name) std::format("{}: {}", #name, name)
#define NL() std::cout << "\n"
#define PRINT(msg) std::cout << msg << "\n"
#define ASSERT(condition)                                                      \
  if (!(condition)) {                                                          \
    std::cerr << __FILE__ << ":" << __LINE__ << ":0"                           \
              << " ASSERTION_FAILED: " << #condition << "\n";                  \
    exit(1);                                                                   \
  }
#ifdef DEBUG
#define DEBUG_MSG(msg) std::cout << "DEBUG: " << msg << "\n"
#endif
void d_msg(const std::string &_msg);
#ifdef DEBUG
#define DEBUG_WARNING(msg) std::cout << "WARNING: " << msg << "\n"
#endif
void d_warn(const std::string &_msg);

// data.dat ==================================================
enum Data_type { None = -1, Font, Texture, Sound };

struct Data_chunk {
  Data_type type;
  size_t data_size;
  size_t name_size;
  std::string name;
  char *data;

  void free();
  void allocate(size_t size);

  static size_t data_allocated;
};

/* data.dat format
   [data_type]
   [data_size]
   [name_size]
   [name]
   [data]
   ...
 */

std::vector<std::string> list_of_names_in_data();
std::vector<Data_chunk> list_of_chunks_in_data();
bool remove_chunk_from_data(const std::string &_name);
bool write_chunk_to_data(const Data_type &type, const std::string &filename);
bool write_texture_to_data(const std::string &texture_filename);
bool write_font_to_data(const std::string &font_filename);
bool write_sound_to_data(const std::string &sound_filename);
bool read_chunk_from_data(Data_chunk &chunk, const std::string &name,
                          Data_type type = Data_type::None);
bool read_font_from_data(Data_chunk &chunk, const std::string &name);
bool read_texture_from_data(Data_chunk &chunk, const std::string &name);
bool read_sound_from_data(Data_chunk &chunk, const std::string &name);

// texture_manager --------------------------------------------------
struct Texture_manager {
  std::vector<Data_chunk> texture_chunks;
  bool load_all_textures();

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

  // drawing functions {calls ren_tex.draw()}
  void draw(const sf::Drawable &drawable,
            const sf::RenderStates &states = sf::RenderStates::Default);
  void draw(const sf::Vertex *vertices, std::size_t vertexCount,
            sf::PrimitiveType type,
            const sf::RenderStates &states = sf::RenderStates::Default);
  void draw(const sf::VertexBuffer &vertexBuffer,
            const sf::RenderStates &states = sf::RenderStates::Default);
  void draw(const sf::VertexBuffer &vertexBuffer, std::size_t firstVertex,
            std::size_t vertexCount,
            const sf::RenderStates &states = sf::RenderStates::Default);
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
// macro functions
void d_msg(const std::string &_msg) {
#ifdef DEBUG
  DEBUG_MSG(_msg);
#endif
}

void d_warn(const std::string &_msg) {
#ifdef DEBUG
  DEBUG_WARNING(_msg);
#endif
}

// data.dat --------------------------------------------------
void Data_chunk::free() {
  type = Data_type::None;
  data_size = 0;
  name_size = 0;
  d_msg(std::format("Chunk `{}` freed!", name));
  name.resize(0);
  if (data != nullptr) {
    delete data;
    ASSERT(Data_chunk::data_allocated > 0);
    Data_chunk::data_allocated--;
  }
}

void Data_chunk::allocate(size_t size) {
  if (data != nullptr) {
    d_warn("data is already allocated!");
    return;
  }
  data = new char[size];
  Data_chunk::data_allocated++;
}

size_t Data_chunk::data_allocated = 0;

std::vector<std::string> list_of_names_in_data() {
  std::ifstream ifs;
  std::vector<std::string> names;
  ifs.open("data.dat", std::ios::binary | std::ios::in);
  // TODO: check if `data.dat` exists
  if (ifs.is_open()) {

    size_t bytes_read = 0;
    size_t total_bytes = 0;
    ifs.seekg(0, std::ios::end);
    total_bytes = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    while (bytes_read < total_bytes) {

      // read data type
      Data_type type = Data_type::Font;
      ifs.read((char *)&type, sizeof(type));
      bytes_read += ifs.gcount();

      // read data size
      size_t data_size = 0;
      ifs.read((char *)&data_size, sizeof(data_size));
      bytes_read += ifs.gcount();

      // read name size
      size_t name_size = 0;
      ifs.read((char *)&name_size, sizeof(name_size));
      bytes_read += ifs.gcount();

      // read name
      std::string name;
      name.resize(name_size);
      ifs.read((char *)name.c_str(), name_size);
      bytes_read += ifs.gcount();

      // read data
      char *data = new char[data_size];
      ifs.read((char *)data, data_size);
      bytes_read += ifs.gcount();

      if (name_size > 0) {
        names.push_back(name);
      }
    }
  } else {
    std::cerr << "ERROR: Could not open `data.dat`!\n";
    return names;
  }

  ifs.close();
  return names;
}

std::vector<Data_chunk> list_of_chunks_in_data() {
  std::vector<Data_chunk> chunks;

  std::ifstream ifs;
  ifs.open("data.dat", std::ios::binary);

  if (!ifs.is_open()) {
    std::cerr << "ERROR: Could not open `data.dat` for input\n";
    return chunks;
  }

  size_t bytes_read = 0;
  size_t total_bytes = 0;
  ifs.seekg(0, std::ios::end);
  total_bytes = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  while (bytes_read < total_bytes) {
    Data_chunk chunk{0};

    // read data type
    ifs.read((char *)&chunk.type, sizeof(chunk.type));
    bytes_read += ifs.gcount();

    // read data size
    ifs.read((char *)&chunk.data_size, sizeof(chunk.data_size));
    bytes_read += ifs.gcount();

    // read name size
    ifs.read((char *)&chunk.name_size, sizeof(chunk.name_size));
    bytes_read += ifs.gcount();

    // read name
    ASSERT(chunk.name_size > 0);
    chunk.name.resize(chunk.name_size);
    ifs.read((char *)chunk.name.c_str(), chunk.name_size);
    bytes_read += ifs.gcount();

    // read data
    ASSERT(chunk.data_size > 0);
    chunk.allocate(chunk.data_size);
    ifs.read((char *)chunk.data, chunk.data_size);
    bytes_read += ifs.gcount();

    chunks.push_back(chunk);
  }

  return chunks;
}

bool remove_chunk_from_data(const std::string &_name) {
  std::ifstream ifs;
  ifs.open("data.dat", std::ios::binary);
  char *data = nullptr;
  size_t data_size = 0;

  char *previous_data_file = nullptr;
  char *new_data_file = nullptr;

  if (ifs.is_open()) {
    // allocate previous data file state to memory
    ifs.seekg(0, std::ios::end);
    size_t previous_data_file_size = ifs.tellg();
    if (previous_data_file_size <= 0) {
      std::cout << "ERROR: `data.dat` is empty!\n";
      return false;
    }
    previous_data_file = new char[previous_data_file_size];

    ifs.seekg(0, std::ios::beg);

    ifs.read(previous_data_file, previous_data_file_size);
    ifs.seekg(0, std::ios::beg);

    bool found = false;
    size_t found_start = 0;
    size_t found_size = 0;

    size_t bytes_read = 0;
    size_t total_bytes = 0;
    ifs.seekg(0, std::ios::end);
    total_bytes = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    while (bytes_read < total_bytes) {
      // record start of data
      found_start = ifs.tellg();
      found_size = 0;

      // read data type
      Data_type type = Data_type::Font;
      ifs.read((char *)&type, sizeof(type));
      ASSERT(ifs.gcount() == sizeof(type));
      size_t gcount = ifs.gcount();
      found_size += gcount;
      bytes_read += gcount;

      // read data size
      ifs.read((char *)&data_size, sizeof(data_size));
      ASSERT(ifs.gcount() == sizeof(data_size));
      gcount = ifs.gcount();
      found_size += gcount;
      bytes_read += gcount;

      // read name size
      size_t name_size = 0;
      ifs.read((char *)&name_size, sizeof(name_size));
      ASSERT(ifs.gcount() == sizeof(name_size));
      gcount = ifs.gcount();
      found_size += gcount;
      bytes_read += gcount;

      // read name
      std::string name;
      name.resize(name_size);
      ifs.read((char *)name.c_str(), name_size);
      ASSERT(ifs.gcount() == name_size);
      gcount = ifs.gcount();
      found_size += gcount;
      bytes_read += gcount;

      // read data
      data = new char[data_size];
      ifs.read(data, data_size);
      ASSERT(ifs.gcount() == data_size);
      gcount = ifs.gcount();
      found_size += gcount;
      bytes_read += gcount;

      // break if name is found
      found = (name_size > 0 ? name == _name : false);
      if (found)
        break;
    }
    ifs.close();

    // remove the data found
    if (found) {
      ASSERT(0 <= found_start && found_start < previous_data_file_size);

      new_data_file[found_start];

      // pre = [  ][  ][  ][  ][  ][  ]
      //           ^  ^
      //  found start end
      // new = [  ][  ][  ][  ][  ]
      //           ^
      size_t new_data_file_size = previous_data_file_size - found_size;
      new_data_file = new char[new_data_file_size];

      memcpy(new_data_file, previous_data_file, new_data_file_size);

      memcpy(new_data_file + found_start,
             previous_data_file + found_start + found_size,
             (previous_data_file_size - (found_start + found_size)));

      // output new data to data.dat
      if (new_data_file != nullptr) {

        d_warn("Overwriting the data.dat file!");
        std::ofstream ofs;
        ofs.open("data.dat", std::ios::binary);
        if (ofs.is_open()) {

          ofs.write(new_data_file, new_data_file_size);

          delete new_data_file;
          delete previous_data_file;

          d_msg(
              std::format("Successfully removed `{}` from `data.dat`", _name));
          return true;
          ofs.close();
        } else {
          std::cerr << "ERROR: Could not open `data.dat` for output\n";
          return false;
        }
      }
    }

    std::cerr << "ERROR: Could not find `" << _name << "` in `data.dat`\n";
    return false;
  } else {
    std::cerr << "ERROR: Could not open `data.dat` for input\n";
    return false;
  }
}

bool write_chunk_to_data(const Data_type &type, const std::string &filename) {
  for (auto &name : list_of_names_in_data()) {
    if (name == filename) {
      d_warn(std::format("Trying to add duplicate data `{}`", filename));
      return true;
    }
  }

  std::ifstream ifs;
  ifs.open(filename, std::ios::binary);

  char *data = nullptr;
  size_t data_size = 0;

  if (ifs.is_open()) {
    ifs.seekg(0, std::ios::end);
    data_size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    data = new char[data_size];

    ifs.read((char *)data, data_size);

    ifs.close();
  } else {
    std::cerr << "ERROR: Could not open `" << filename << "` for input\n";
    return false;
  }

  std::ofstream ofs;
  ofs.open("data.dat", std::ios::app | std::ios::binary);

  if (ofs.is_open()) {
    ofs.seekp(0, std::ios::end);
    d_msg(std::format<size_t>(
        "`data.dat` contains {} bytes of data before writing `{}`", ofs.tellp(),
        filename));
    ofs.seekp(0, std::ios::beg);

    size_t bytes_written = 0;

    // write data type
    ofs.write((char *)&type, sizeof(type));
    bytes_written += sizeof(type);

    // write data size
    ofs.write((char *)&data_size, sizeof(data_size));
    bytes_written += sizeof(data_size);

    // write name size
    size_t name_size = filename.size();
    ofs.write((char *)&name_size, sizeof(name_size));
    bytes_written += sizeof(name_size);

    // write name
    ofs.write((char *)filename.c_str(), name_size);
    bytes_written += name_size;

    // write data
    ofs.write((char *)data, data_size);
    bytes_written += data_size;

    d_msg(std::format("Successfully written `{}` ({} bytes) to `data.dat`",
                      filename, bytes_written));
    return true;
    ofs.close();
  } else {
    std::cerr << "ERROR: Could not open `data.dat` for output\n";
    return false;
  }
  return false;
}

bool write_texture_to_data(const std::string &texture_filename) {
  return write_chunk_to_data(Data_type::Texture, texture_filename);
}

bool write_font_to_data(const std::string &font_filename) {
  return write_chunk_to_data(Data_type::Font, font_filename);
}

bool write_sound_to_data(const std::string &sound_filename) {
  return write_chunk_to_data(Data_type::Sound, sound_filename);
}

bool read_chunk_from_data(Data_chunk &chunk, const std::string &name,
                          Data_type type) {
  auto chunks = list_of_chunks_in_data();
  if (chunks.empty()) {
    std::cerr << "ERROR: No chunk(s) found in `data.dat`\n";
    return false;
  }

  bool found = false;
  bool found_type = false;
  bool found_name = false;
  bool check_type = type != Data_type::None;
  int found_idx = -1;
  for (size_t i = 0; i < chunks.size(); ++i) {
    auto &ch = chunks.at(i);

    if (check_type) {
      found_type = ch.type == type;
    }
    found_name = ch.name == name;

    if (check_type) {
      found = found_name && found_type;
    } else {
      found = found_name;
    }
    if (found) {
      found_idx = int(i);
      chunk = ch;
      break;
    }
  }

  // free unwanted allocated chunks
  for (size_t i = 0; i < chunks.size(); ++i) {
    if (i != found_idx) {
      chunks.at(i).free();
    }
  }

  std::string type_str;

  switch (type) {
  case Data_type::None:
    type_str = "chunk";
    break;
  case Data_type::Font:
    type_str = "font";
    break;
  case Data_type::Texture:
    type_str = "texture";
    break;
  case Data_type::Sound:
    type_str = "sound";
    break;
  }

  if (!found) {
    std::cerr << "ERROR: Could not find " << type_str << " `" << name
              << "` in `data.dat`\n";
    return false;
  } else {
    d_msg(std::format("Found {} `{}` in `data.dat`", type_str, name));
    return true;
  }
}

bool read_font_from_data(Data_chunk &chunk, const std::string &name) {
  return read_chunk_from_data(chunk, name, Data_type::Font);
}

bool read_texture_from_data(Data_chunk &chunk, const std::string &name) {
  return read_chunk_from_data(chunk, name, Data_type::Texture);
}

bool read_sound_from_data(Data_chunk &chunk, const std::string &name) {
  return read_chunk_from_data(chunk, name, Data_type::Sound);
}

// data --------------------------------------------------

void Data::draw(const sf::Drawable &drawable, const sf::RenderStates &states) {
  ren_tex.draw(drawable, states);
}

void Data::draw(const sf::Vertex *vertices, std::size_t vertexCount,
                sf::PrimitiveType type, const sf::RenderStates &states) {
  ren_tex.draw(vertices, vertexCount, type, states);
}

void Data::draw(const sf::VertexBuffer &vertexBuffer,
                const sf::RenderStates &states) {
  ren_tex.draw(vertexBuffer, states);
}
void Data::draw(const sf::VertexBuffer &vertexBuffer, std::size_t firstVertex,
                std::size_t vertexCount, const sf::RenderStates &states) {
  ren_tex.draw(vertexBuffer, firstVertex, vertexCount, states);
}

// texture_manager --------------------------------------------------
std::string Texture_manager::texture_path = "res/gfx/";

bool Texture_manager::load_all_textures() {
  std::vector<Data_chunk> chunks = list_of_chunks_in_data();

  if (chunks.empty()) {
    std::cerr << "ERROR: No chunk(s) found in `data.dat`\n";
    return false;
  }

  for (auto &ch : chunks) {
    if (ch.type == Data_type::Texture) {
      texture_chunks.push_back(ch);
    } else {
      ch.free();
    }
  }

  d_msg(std::format("Loaded {} textures", texture_chunks.size()));
  return true;
}

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
