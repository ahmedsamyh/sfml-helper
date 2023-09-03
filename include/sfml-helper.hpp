#ifndef _SFML_HELPER_H_
#define _SFML_HELPER_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

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
#define ASSERT_MSG(condition, msg)                                             \
  if (!(condition)) {                                                          \
    std::cerr << __FILE__ << ":" << __LINE__ << ":0"                           \
              << " ASSERTION_FAILED: " << #condition << " `" << msg << "`\n";  \
    exit(1);                                                                   \
  }
#define INFO(msg) std::cout << "INFO: " << msg << "\n"
void d_info(const std::string &_msg);
void info(const std::string &_msg, bool debug = false);
#define WARNING(msg) std::cout << "WARNING: " << msg << "\n"
void d_warn(const std::string &_msg);
void warn(const std::string &_msg, bool debug = false);
#define error(msg, ...)                                                        \
  std::cerr << std::format("ERROR: {}:{}:0 {}\n", __FILE__, __LINE__, msg);    \
  exit(1)

#define fmt(str, ...) std::format((str), __VA_ARGS__)
#ifndef NO_PRINT
#define print(str, ...) std::cout << fmt(str, __VA_ARGS__)
#endif

// data.dat ==================================================
enum Data_type { None = -1, Font, Texture, Sound, Shader };

// #define LOG_DATA_CHUNK_FREE

struct Data_chunk {
  Data_type type;
  size_t data_size;
  size_t name_size;
  std::string name;
  char *data;

  void free();
  void allocate(size_t size);
  size_t total_size() const;

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
bool remove_chunk_from_data(const std::string &filename);
bool remove_all_chunks_from_data();
bool write_chunk_to_data(const Data_type &type, const std::string &filename);
bool write_texture_to_data(const std::string &filename);
bool write_font_to_data(const std::string &filename);
bool write_sound_to_data(const std::string &filename);
bool write_shader_to_data(const std::string &filename);
bool read_chunk_from_data(Data_chunk &chunk, const std::string &filename,
                          Data_type type = Data_type::None);
bool read_font_from_data(Data_chunk &chunk, const std::string &filename);
bool read_texture_from_data(Data_chunk &chunk, const std::string &filename);
bool read_sound_from_data(Data_chunk &chunk, const std::string &filename);
bool read_shader_from_data(Data_chunk &chunk, const std::string &filename);
bool chunk_exists_in_data(const std::string &filename);

// resource_manager --------------------------------------------------
struct Resource_manager {
  std::vector<Data_chunk> texture_chunks;
  std::vector<Data_chunk> font_chunks;
  bool load_all_textures();
  bool load_all_fonts();

  sf::Font &load_font(const std::string &filename);

  std::unordered_map<std::string, sf::Texture> textures;
  std::unordered_map<std::string, sf::Font> fonts;
  sf::Texture &get_texture(const std::string &filename);
  sf::Font &get_font(const std::string &filename);
  static std::string texture_path;
};

// timer --------------------------------------------------
struct Data;
struct Timer {
  float time; // in seconds
  Data *d;
  bool initted = false;

  Timer();
  Timer(Data &_d, float _time = 0.f);

  void run();
  void init(Data &_d, float _time = 0.f);

  // getters
  float s() const;
  sf::Int32 ms() const;
  sf::Int64 us() const;
};

struct Alarm : Timer {
  float alarm_time; // in seconds
  bool one_time;
  bool ran_one_time;

  Alarm();
  Alarm(Data &_d, float _alarm_time, bool _one_time = false, float _time = 0.f);

  void init(Data &_d, float _alarm_time, bool _one_time = false,
            float _time = 0.f);

  bool on_alarm();
};

// text_aligment --------------------------------------------------
enum Text_align {
  TopLeft,
  TopCenter,
  TopRight,
  CenterLeft,
  CenterCenter,
  CenterRight,
  BottomLeft,
  BottomCenter,
  BottomRight
};

// mouse --------------------------------------------------
enum class MB {
  Left,     //!< The left mouse button
  Right,    //!< The right mouse button
  Middle,   //!< The middle (wheel) mouse button
  XButton1, //!< The first extra mouse button
  XButton2, //!< The second extra mouse button

  ButtonCount //!< Keep last -- the total number of mouse buttons
};

// Key --------------------------------------------------
enum class Key {
  Unknown = -1, //!< Unhandled key
  A = 0,        //!< The A key
  B,            //!< The B key
  C,            //!< The C key
  D,            //!< The D key
  E,            //!< The E key
  F,            //!< The F key
  G,            //!< The G key
  H,            //!< The H key
  I,            //!< The I key
  J,            //!< The J key
  K,            //!< The K key
  L,            //!< The L key
  M,            //!< The M key
  N,            //!< The N key
  O,            //!< The O key
  P,            //!< The P key
  Q,            //!< The Q key
  R,            //!< The R key
  S,            //!< The S key
  T,            //!< The T key
  U,            //!< The U key
  V,            //!< The V key
  W,            //!< The W key
  X,            //!< The X key
  Y,            //!< The Y key
  Z,            //!< The Z key
  Num0,         //!< The 0 key
  Num1,         //!< The 1 key
  Num2,         //!< The 2 key
  Num3,         //!< The 3 key
  Num4,         //!< The 4 key
  Num5,         //!< The 5 key
  Num6,         //!< The 6 key
  Num7,         //!< The 7 key
  Num8,         //!< The 8 key
  Num9,         //!< The 9 key
  Escape,       //!< The Escape key
  LControl,     //!< The left Control key
  LShift,       //!< The left Shift key
  LAlt,         //!< The left Alt key
  LSystem,      //!< The left OS specific key: window (Windows and Linux), apple
                //!< (macOS), ...
  RControl,     //!< The right Control key
  RShift,       //!< The right Shift key
  RAlt,         //!< The right Alt key
  RSystem,    //!< The right OS specific key: window (Windows and Linux), apple
              //!< (macOS), ...
  Menu,       //!< The Menu key
  LBracket,   //!< The [ key
  RBracket,   //!< The ] key
  Semicolon,  //!< The ; key
  Comma,      //!< The , key
  Period,     //!< The . key
  Apostrophe, //!< The ' key
  Slash,      //!< The / key
  Backslash,  //!< The \ key
  Grave,      //!< The ` key
  Equal,      //!< The = key
  Hyphen,     //!< The - key (hyphen)
  Space,      //!< The Space key
  Enter,      //!< The Enter/Return keys
  Backspace,  //!< The Backspace key
  Tab,        //!< The Tabulation key
  PageUp,     //!< The Page up key
  PageDown,   //!< The Page down key
  End,        //!< The End key
  Home,       //!< The Home key
  Insert,     //!< The Insert key
  Delete,     //!< The Delete key
  Add,        //!< The + key
  Subtract,   //!< The - key (minus, usually from numpad)
  Multiply,   //!< The * key
  Divide,     //!< The / key
  Left,       //!< Left arrow
  Right,      //!< Right arrow
  Up,         //!< Up arrow
  Down,       //!< Down arrow
  Numpad0,    //!< The numpad 0 key
  Numpad1,    //!< The numpad 1 key
  Numpad2,    //!< The numpad 2 key
  Numpad3,    //!< The numpad 3 key
  Numpad4,    //!< The numpad 4 key
  Numpad5,    //!< The numpad 5 key
  Numpad6,    //!< The numpad 6 key
  Numpad7,    //!< The numpad 7 key
  Numpad8,    //!< The numpad 8 key
  Numpad9,    //!< The numpad 9 key
  F1,         //!< The F1 key
  F2,         //!< The F2 key
  F3,         //!< The F3 key
  F4,         //!< The F4 key
  F5,         //!< The F5 key
  F6,         //!< The F6 key
  F7,         //!< The F7 key
  F8,         //!< The F8 key
  F9,         //!< The F9 key
  F10,        //!< The F10 key
  F11,        //!< The F11 key
  F12,        //!< The F12 key
  F13,        //!< The F13 key
  F14,        //!< The F14 key
  F15,        //!< The F15 key
  Pause,      //!< The Pause key

  KeyCount, //!< Keep last -- the total number of keyboard keys

  // Deprecated values:

  Tilde = Grave,         //!< \deprecated Use Grave instead
  Dash = Hyphen,         //!< \deprecated Use Hyphen instead
  BackSpace = Backspace, //!< \deprecated Use Backspace instead
  BackSlash = Backslash, //!< \deprecated Use Backslash instead
  SemiColon = Semicolon, //!< \deprecated Use Semicolon instead
  Return = Enter,        //!< \deprecated Use Enter instead
  Quote = Apostrophe     //!< \deprecated Use Apostrophe instead
};

struct State {
  bool held = false, pressed = false, released = false;
};

// data --------------------------------------------------
struct Data {
  sf::RectangleShape rect;
  sf::CircleShape circle;
  sf::Text text;
  sf::RenderWindow win;
  sf::RenderTexture ren_tex;
  sf::RectangleShape ren_rect;
  sf::Clock clock;
  float delta = 0.f;
  std::string title = "sfml-helper";
  sf::Vector2f _mpos;
  float _mouse_scroll = 0.f;
  Resource_manager res_man;
  int s_width, s_height, width, height, scale;
  sf::Vector2f camera = {0.f, 0.f}, to_camera = {0.f, 0.f};
  sf::View _camera_view;
  float _camera_zoom = 1.f;
  bool mouse_pressed[sf::Mouse::Button::ButtonCount],
      mouse_held[sf::Mouse::Button::ButtonCount],
      mouse_released[sf::Mouse::Button::ButtonCount];
  bool prev_mouse_pressed[sf::Mouse::Button::ButtonCount],
      prev_mouse_held[sf::Mouse::Button::ButtonCount],
      prev_mouse_released[sf::Mouse::Button::ButtonCount];
  State _keys[size_t(Key::KeyCount)];
  State _prev_keys[size_t(Key::KeyCount)];

  // main functions
  void clear(const sf::Color &col = sf::Color(0, 0, 0, 255));
  bool init(int s_w, int s_h, int scl, const std::string &title);
  void display();

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

  // drawing function
  void draw_rect(const sf::Vector2f &pos, const sf::Vector2f &size,
                 sf::Color fill_col = sf::Color::Transparent,
                 sf::Color out_col = sf::Color::White, float out_thic = 1);
  void draw_circle(const sf::Vector2f &pos, float radius,
                   sf::Color fill_col = sf::Color::Transparent,
                   sf::Color out_col = sf::Color::White, float out_thic = 1);
  void draw_text(const sf::Vector2f &pos, const std::string &str,
                 const Text_align &align = Text_align::TopLeft,
                 int character_size = 16, sf::Color fill_col = sf::Color::White,
                 sf::Color out_col = sf::Color::White, float out_thic = 0.f);
  void draw_line(const sf::Vector2f &p1, const sf::Vector2f &p2,
                 sf::Color col = sf::Color::White, float out_thic = 1.f);
  void draw_line_ex(const sf::Vector2f &p1, const sf::Vector2f &p2,
                    sf::Color col1 = sf::Color::White,
                    sf::Color col2 = sf::Color::White, float out_thic = 1.f);
  void draw_arrow(const sf::Vector2f &p1, const sf::Vector2f &p2,
                  sf::Color col = sf::Color::White, float out_thic = 1.f,
                  float shaft_len = 10.f);
  void draw_point(const sf::Vector2f &p, sf::Color col = sf::Color::White,
                  float thic = 1.f);

  // mouse functions
  void update_mouse_event(sf::Event &e);
  void update_mouse();
  bool m_pressed(MB btn);
  bool m_held(MB btn);
  bool m_released(MB btn);
  sf::Vector2f &mpos();
  sf::Vector2f mpos_w();
  float mouse_scroll();

  // key functions
  void update_key();
  bool k_pressed(Key key);
  bool k_held(Key key);
  bool k_released(Key key);

  // screen functions
  sf::Vector2f ss() const;
  sf::Vector2f ss_f() const;
  sf::Vector2i ss_i() const;
  sf::Vector2f scr_to_wrld(const sf::Vector2f &p);
  sf::Vector2f wrld_to_scr(const sf::Vector2f &p);

  // utility functions
  void handle_close(sf::Event &e);
  float calc_delta();
  void update_title();

  // view functions
  void camera_follow(const sf::Vector2f &pos, float rate = 1.f);
  void camera_view();
  float &camera_zoom();
  void default_view();
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

#endif /* _SFML-HELPER_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SFML_HELPER_IMPLEMENTATION
// macro functions
void d_info(const std::string &_msg) { info(_msg, true); }

void info(const std::string &_msg, bool debug) {
  if (debug) {
#ifdef DEBUG
    INFO(_msg);
#endif
  } else {
    INFO(_msg);
  }
}

void d_warn(const std::string &_msg) { warn(_msg, true); }

void warn(const std::string &_msg, bool debug) {
#ifndef NO_WARNING
  if (debug) {
#ifdef DEBUG
    WARNING(_msg);
#endif
  } else {
    WARNING(_msg);
  }
#endif
}

// data.dat --------------------------------------------------
void Data_chunk::free() {
  type = Data_type::None;
  data_size = 0;
  name_size = 0;
#ifdef LOG_DATA_CHUNK_FREE
  d_info(std::format("Chunk `{}` freed!", name));
#endif
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

size_t Data_chunk::total_size() const {
  return (sizeof(type) + sizeof(data_size) + sizeof(name_size) + name.size() +
          data_size);
}

size_t Data_chunk::data_allocated = 0;

std::vector<std::string> list_of_names_in_data() {
  std::ifstream ifs;
  std::vector<std::string> names;
  if (!fs::exists("data.dat")) {
    error("`data.dat` doesn't exist");
  }
  ifs.open("data.dat", std::ios::binary | std::ios::in);
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
      delete data;

      if (name_size > 0) {
        names.push_back(name);
      }
    }
  } else {
    error("Could not open `data.dat` for input");
    return names;
  }

  ifs.close();
  return names;
}

std::vector<Data_chunk> list_of_chunks_in_data() {
  std::vector<Data_chunk> chunks;

  if (!fs::exists("data.dat")) {
    error("`data.dat` doesn't exist");
  }

  std::ifstream ifs;
  ifs.open("data.dat", std::ios::binary);

  if (!ifs.is_open()) {
    error("Could not open `data.dat` for input");
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
  bool found = false;
  for (auto &name : list_of_names_in_data()) {
    found |= name == _name;
  }
  if (!found) {
    d_warn(std::format("Chunk named `{}` doesn't exist!", _name));
    return true;
  }

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
      error("`data.dat` is empty!");
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

          d_info(std::format(
              "Successfully removed `{}` ({} bytes) from `data.dat`", _name,
              found_size));
          return true;
          ofs.close();
        } else {
          error("Could not open `data.dat` for output");
          return false;
        }
      }
    }

    error(std::format("Could not find `{}` in `data.dat`", _name));
    return false;
  } else {
    error("Could not open `data.dat` for input");
    return false;
  }
}

bool remove_all_chunks_from_data() {
  std::ofstream ofs;
  ofs.open("data.dat", std::ios::binary);
  if (!ofs.is_open()) {
    error("Could not open `data.dat` for output");
    return false;
  }
  d_warn("`data.dat` cleared");
  ofs.close();
  return true;
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
    error(std::format("Could not open `{}` for input", filename));
    return false;
  }

  std::ofstream ofs;
  ofs.open("data.dat", std::ios::app | std::ios::binary);

  if (ofs.is_open()) {
    ofs.seekp(0, std::ios::end);
    // d_info(std::format<size_t>(
    //     "`data.dat` contains {} bytes of data before writing `{}`",
    //     ofs.tellp(), filename));
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

    d_info(std::format("Successfully written `{}` ({} bytes) to `data.dat`",
                       filename, bytes_written));
    return true;
    ofs.close();
  } else {
    error("Could not open `data.dat` for output");
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

bool write_shader_to_data(const std::string &filename) {
  return write_chunk_to_data(Data_type::Shader, filename);
}

bool read_chunk_from_data(Data_chunk &chunk, const std::string &name,
                          Data_type type) {
  auto chunks = list_of_chunks_in_data();
  if (chunks.empty()) {
    error("No chunk(s) found in `data.dat`");
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
  case Data_type::Shader:
    type_str = "shader";
    break;
  default:
    ASSERT(0);
    break;
  }

  if (!found) {
    error(std::format("Could not find {} `{}` in `data.dat`", type_str, name));
    return false;
  } else {
    d_info(std::format("Successfully read {} `{}` ({} bytes) from `data.dat`",
                       type_str, name, chunk.total_size()));
    return true;
  }
}

bool read_font_from_data(Data_chunk &chunk, const std::string &filename) {
  return read_chunk_from_data(chunk, filename, Data_type::Font);
}

bool read_texture_from_data(Data_chunk &chunk, const std::string &filename) {
  return read_chunk_from_data(chunk, filename, Data_type::Texture);
}

bool read_sound_from_data(Data_chunk &chunk, const std::string &filename) {
  return read_chunk_from_data(chunk, filename, Data_type::Sound);
}

bool read_shader_from_data(Data_chunk &chunk, const std::string &filename) {
  return read_chunk_from_data(chunk, filename, Data_type::Shader);
}

bool chunk_exists_in_data(const std::string &filename) {
  std::vector<Data_chunk> chunks = list_of_chunks_in_data();
  bool found = false;

  if (chunks.empty()) {
    d_info(std::format("Chunk `{}` doesn't exist!", filename));
    return found;
  }

  for (auto &ch : chunks) {
    found |= ch.name == filename;
    ch.free();
  }

  if (found) {
    d_info(std::format("Chunk `{}` exist!", filename));
  }

  return found;
}

// data --------------------------------------------------

void Data::clear(const sf::Color &col) {
  win.clear(col);
  ren_tex.clear(col);
}

bool Data::init(int s_w, int s_h, int scl, const std::string &_title) {
  title = _title;
  s_width = s_w;
  s_height = s_h;
  scale = scl;
  width = s_width / scale;
  height = s_height / scale;

  srand(unsigned int(time(0)));

  // std::cout auto-flushes on every output
  std::cout << std::unitbuf;

  // create window
  win.create(sf::VideoMode(s_width, s_height), title,
             sf::Style::Close | sf::Style::Titlebar);
  win.setVerticalSyncEnabled(true);

  // create render texture
  if (!ren_tex.create(width, height)) {
    error("Could not create render texture!");
    return false;
  }

  // init mouse btns
  for (size_t i = 0; i < sf::Mouse::Button::ButtonCount; ++i) {
    mouse_released[i] = false;
    prev_mouse_released[i] = false;
    mouse_held[i] = false;
    prev_mouse_held[i] = false;
    mouse_pressed[i] = false;
    prev_mouse_pressed[i] = false;
  }

  // init keys

  for (size_t i = 0; i < static_cast<size_t>(Key::KeyCount); ++i) {
    _keys[i].pressed = false;
    _keys[i].held = false;
    _keys[i].released = false;
    _prev_keys[i].pressed = false;
    _prev_keys[i].held = false;
    _prev_keys[i].released = false;
  }

  // load default font
  text.setFont(res_man.load_font("res/font/PressStart2P-Regular.ttf"));

  return res_man.load_all_textures();
}

void Data::display() {
  ren_tex.display();

  ren_rect.setSize(sf::Vector2f((float)s_width, (float)s_height));
  ren_rect.setTexture(&ren_tex.getTexture());

  win.draw(ren_rect);
  win.display();
}

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

void Data::draw_rect(const sf::Vector2f &pos, const sf::Vector2f &size,
                     sf::Color fill_col, sf::Color out_col, float out_thic) {
  if (size.x <= 0.f || size.y <= 0.f)
    return;
  rect.setPosition(pos + sf::Vector2f(out_thic, out_thic));
  rect.setSize(size - sf::Vector2f(out_thic, out_thic));
  rect.setFillColor(fill_col);
  rect.setOutlineColor(out_col);
  rect.setOutlineThickness(out_thic);

  draw(rect);
}

void Data::draw_circle(const sf::Vector2f &pos, float radius,
                       sf::Color fill_col, sf::Color out_col, float out_thic) {
  if (radius <= 0.f)
    return;
  circle.setPosition(pos);
  circle.setOrigin({radius, radius});
  circle.setRadius(radius - out_thic);
  circle.setFillColor(fill_col);
  circle.setOutlineColor(out_col);
  circle.setOutlineThickness(out_thic);

  draw(circle);
}

void Data::draw_text(const sf::Vector2f &pos, const std::string &str,
                     const Text_align &align, int character_size,
                     sf::Color fill_col, sf::Color out_col, float out_thic) {
  text.setPosition(pos);
  text.setString(str);
  text.setCharacterSize(character_size - uint64_t(out_thic));
  text.setFillColor(fill_col);
  text.setOutlineColor(out_col);
  text.setOutlineThickness(out_thic);

  sf::FloatRect bound = text.getLocalBounds();

  switch (align) {
  case TopLeft:
    text.setOrigin({0.f, 0.f});
    break;
  case TopCenter:
    text.setOrigin({bound.width / 2.f, 0.f});
    break;
  case TopRight:
    text.setOrigin({bound.width, 0.f});
    break;
  case CenterLeft:
    text.setOrigin({0.f, bound.height / 2.f});
    break;
  case CenterCenter:
    text.setOrigin({bound.width / 2.f, bound.height / 2.f});
    break;
  case CenterRight:
    text.setOrigin({bound.width, bound.height / 2.f});
    break;
  case BottomLeft:
    text.setOrigin({0.f, bound.height});
    break;
  case BottomCenter:
    text.setOrigin({bound.width / 2.f, bound.height});
    break;
  case BottomRight:
    text.setOrigin({bound.width, bound.height});
    break;
  default:
    ASSERT_MSG(0, "Unreachable state reached in `draw_text`");
  }

  draw(text);
}

void Data::draw_line(const sf::Vector2f &p1, const sf::Vector2f &p2,
                     sf::Color col, float out_thic) {
  sf::Vertex q[4];
  // 0------------1
  // p1          p2
  // 2------------3
  sf::Vector2f n = v2f::normal(v2f::normalize(p2 - p1));
  q[0].position = p1 + n * (out_thic / 2.f);
  q[1].position = p2 + n * (out_thic / 2.f);
  q[2].position = p1 - n * (out_thic / 2.f);
  q[3].position = p2 - n * (out_thic / 2.f);
  for (size_t i = 0; i < 4; ++i)
    q[i].color = col;

  draw(q, 4, sf::PrimitiveType::TriangleStrip);
}

void Data::draw_line_ex(const sf::Vector2f &p1, const sf::Vector2f &p2,
                        sf::Color col1, sf::Color col2, float out_thic) {
  sf::Vertex q[4];
  // 0------------1
  // p1          p2
  // 2------------3
  sf::Vector2f n = v2f::normal(v2f::normalize(p2 - p1));
  q[0].position = p1 + n * (out_thic / 2.f);
  q[2].position = p1 - n * (out_thic / 2.f);
  q[0].color = col1;
  q[2].color = col1;
  q[1].position = p2 + n * (out_thic / 2.f);
  q[3].position = p2 - n * (out_thic / 2.f);
  q[1].color = col2;
  q[3].color = col2;

  draw(q, 4, sf::PrimitiveType::TriangleStrip);
}

void Data::draw_arrow(const sf::Vector2f &p1, const sf::Vector2f &p2,
                      sf::Color col, float out_thic, float shaft_len) {

  draw_line(p1, p2, col, out_thic);
  sf::Vector2f n = v2f::normal(v2f::normalize(p1 - p2));
  sf::Vector2f t = v2f::normalize(p1 - p2);
  sf::Vector2f sh1 = p2 + (n * shaft_len) + (t * shaft_len);
  draw_line(p2, sh1, col, out_thic);
  sf::Vector2f sh2 = p2 - (n * shaft_len) + (t * shaft_len);
  draw_line(p2, sh2, col, out_thic);
}

void Data::draw_point(const sf::Vector2f &p, sf::Color col, float thic) {
  thic = std::fmaxf(0.1f, thic);
  sf::Vertex q[4];
  q[0].position = p + sf::Vector2f(-(thic / 2.f), -(thic / 2.f));
  q[1].position = p + sf::Vector2f((thic / 2.f), -(thic / 2.f));
  q[2].position = p + sf::Vector2f(-(thic / 2.f), (thic / 2.f));
  q[3].position = p + sf::Vector2f((thic / 2.f), (thic / 2.f));

  ren_tex.draw(q, 4, sf::PrimitiveType::TriangleStrip);
}

void Data::update_mouse_event(sf::Event &e) {
  if (e.type == sf::Event::MouseMoved) {
    _mpos.x = float(e.mouseMove.x / scale);
    _mpos.y = float(e.mouseMove.y / scale);
  }

  if (e.type == sf::Event::MouseWheelScrolled) {
    _mouse_scroll = e.mouseWheelScroll.delta;
  }
}

void Data::update_mouse() {
  memcpy(prev_mouse_pressed, mouse_pressed,
         sizeof(bool) * static_cast<size_t>(MB::ButtonCount));
  memcpy(prev_mouse_held, mouse_held,
         sizeof(bool) * static_cast<size_t>(MB::ButtonCount));
  memcpy(prev_mouse_released, mouse_released,
         sizeof(bool) * static_cast<size_t>(MB::ButtonCount));
  for (size_t i = 0; i < sf::Mouse::Button::ButtonCount; ++i) {
    mouse_held[i] = sf::Mouse::isButtonPressed(sf::Mouse::Button(i));
    mouse_pressed[i] = mouse_held[i] && !prev_mouse_held[i];
    mouse_released[i] = !mouse_held[i] && prev_mouse_held[i];
  }
}

bool Data::m_pressed(MB btn) {
  ASSERT(size_t(btn) < size_t(MB::ButtonCount));
  return mouse_pressed[static_cast<size_t>(btn)];
}

bool Data::m_held(MB btn) {
  ASSERT(size_t(btn) < size_t(MB::ButtonCount));
  return mouse_held[static_cast<size_t>(btn)];
}

bool Data::m_released(MB btn) {
  ASSERT(size_t(btn) < size_t(MB::ButtonCount));
  return mouse_released[static_cast<size_t>(btn)];
}

sf::Vector2f &Data::mpos() { return _mpos; }

sf::Vector2f Data::mpos_w() { return scr_to_wrld(mpos()); }

float Data::mouse_scroll() { return _mouse_scroll; }

void Data::update_key() {
  for (size_t i = 0; i < static_cast<size_t>(Key::KeyCount); ++i) {
    memcpy(_prev_keys, _keys,
           sizeof(State) * static_cast<size_t>(Key::KeyCount));

    _keys[i].held =
        sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));

    _keys[i].pressed = !_prev_keys[i].held && _keys[i].held;
    _keys[i].released = _prev_keys[i].held && !_keys[i].held;
  }
}

bool Data::k_pressed(Key key) {
  ASSERT(0 <= static_cast<size_t>(key) &&
         static_cast<size_t>(key) < static_cast<size_t>(Key::KeyCount));
  return _keys[static_cast<size_t>(key)].pressed;
}

bool Data::k_held(Key key) {
  ASSERT(0 <= static_cast<size_t>(key) &&
         static_cast<size_t>(key) < static_cast<size_t>(Key::KeyCount));
  return _keys[static_cast<size_t>(key)].held;
}

bool Data::k_released(Key key) {
  ASSERT(0 <= static_cast<size_t>(key) &&
         static_cast<size_t>(key) < static_cast<size_t>(Key::KeyCount));
  return _keys[static_cast<size_t>(key)].released;
}

sf::Vector2f Data::ss() const { return ss_f(); }

sf::Vector2f Data::ss_f() const {
  return sf::Vector2f(float(width), float(height));
}

sf::Vector2i Data::ss_i() const { return sf::Vector2i(width, height); }

sf::Vector2f Data::scr_to_wrld(const sf::Vector2f &p) {
  sf::Vector2f res = ren_tex.mapPixelToCoords(
      sf::Vector2i(int(std::floorf(p.x)), int(std::floorf(p.y))), _camera_view);
  return res;
}

sf::Vector2f Data::wrld_to_scr(const sf::Vector2f &p) {
  sf::Vector2i res_i =
      ren_tex.mapCoordsToPixel(sf::Vector2f(std::floorf(p.x), std::floorf(p.y)),
                               ren_tex.getDefaultView());
  sf::Vector2f res = sf::Vector2f(res_i);
  return res;
}

void Data::handle_close(sf::Event &e) {
  if (e.type == sf::Event::Closed) {
    win.close();
  }
}

float Data::calc_delta() {
  delta = clock.restart().asSeconds();
  return delta;
}

void Data::update_title() {
  const int fps = int(1.f / delta);
  win.setTitle(std::format("{} | {:.2f}s | {}fps", title, delta, fps));
  _mouse_scroll = 0.f;
}

void Data::camera_follow(const sf::Vector2f &pos, float rate) {
  camera = pos;
  to_camera += (camera - to_camera) * rate;

  _camera_view.setSize(float(width), float(height));
  _camera_view.setCenter(to_camera);
  _camera_zoom = std::fmaxf(0.1f, _camera_zoom);
  _camera_view.zoom(_camera_zoom);
}

float &Data::camera_zoom() { return _camera_zoom; }

void Data::camera_view() { ren_tex.setView(_camera_view); }

void Data::default_view() { ren_tex.setView(ren_tex.getDefaultView()); }

// resource_manager --------------------------------------------------
std::string Resource_manager::texture_path = "res/gfx/";

bool Resource_manager::load_all_textures() {
  std::vector<Data_chunk> chunks = list_of_chunks_in_data();

  if (chunks.empty()) {
    error("No chunk(s) found in `data.dat`");
    return false;
  }

  // loading texture data
  for (auto &ch : chunks) {
    if (ch.type == Data_type::Texture) {
      texture_chunks.push_back(ch);
    } else {
      ch.free();
    }
  }

  // loading texture
  for (auto &ch : texture_chunks) {
    sf::Texture tex;
    if (!tex.loadFromMemory(ch.data, ch.data_size)) {
      error(std::format("Could not load texture data `{}`", ch.name));
      return false;
    }
    textures[ch.name] = tex;
  }

  d_info(std::format("Loaded {} textures", texture_chunks.size()));
  return true;
}

bool Resource_manager::load_all_fonts() {
  std::vector<Data_chunk> chunks = list_of_chunks_in_data();

  if (chunks.empty()) {
    error("No chunk(s) found in `data.dat`");
    return false;
  }

  // loading font data
  for (auto &ch : chunks) {
    if (ch.type == Data_type::Font) {
      font_chunks.push_back(ch);
    } else {
      ch.free();
    }
  }

  // loading font
  for (auto &ch : font_chunks) {
    sf::Font font;
    if (!font.loadFromMemory(ch.data, ch.data_size)) {
      error(std::format("Could not load font data `{}`", ch.name));
      return false;
    }
    fonts[ch.name] = font;
  }

  d_info(std::format("Loaded {} Fonts", font_chunks.size()));
  return true;
}

sf::Font &Resource_manager::load_font(const std::string &filename) {
  std::vector<Data_chunk> chunks = list_of_chunks_in_data();

  if (chunks.empty()) {
    error("No chunk(s) found in `data.dat`");
    exit(1);
  }

  // loading font data
  for (auto &ch : chunks) {
    if (ch.type == Data_type::Font && ch.name == filename) {
      font_chunks.push_back(ch);
    } else {
      ch.free();
    }
  }

  // loading font
  for (auto &ch : font_chunks) {
    sf::Font font;
    if (!font.loadFromMemory(ch.data, ch.data_size)) {
      error(std::format("Could not load font data `{}`", ch.name));
      exit(1);
    }
    fonts[ch.name] = font;
  }

  d_info(std::format("Loaded font `{}`", font_chunks.back().name));
  return fonts[font_chunks.back().name];
}

sf::Texture &Resource_manager::get_texture(const std::string &filename) {
  // return the texture if it already exists
  if (!textures.contains(filename)) {
    error(std::format("the texture `{} doesn't exist!`", filename));
  }

  return textures.at(filename);
}

sf::Font &Resource_manager::get_font(const std::string &filename) {
  // return the font if it already exists
  if (!fonts.contains(filename)) {
    error(std::format("the font `{} doesn't exist!`", filename));
    exit(1);
  }

  return fonts.at(filename);
}

// timer ----------------------------------------

Timer::Timer() {}

Timer::Timer(Data &_d, float _time) { init(_d, _time); }

void Timer::init(Data &_d, float _time) {
  time = _time;
  d = &_d;
  initted = true;
}

void Timer::run() {
  ASSERT(initted);
  time += d->delta;
}

float Timer::s() const { return sf::seconds(time).asSeconds(); }

sf::Int32 Timer::ms() const { return sf::seconds(time).asMilliseconds(); }

sf::Int64 Timer::us() const { return sf::seconds(time).asMicroseconds(); }

Alarm::Alarm() {}

Alarm::Alarm(Data &_d, float _alarm_time, bool _one_time, float _time)
    : Timer(_d, _time) {
  init(_d, _alarm_time, _one_time, _time);
}

void Alarm::init(Data &_d, float _alarm_time, bool _one_time, float _time) {
  Timer::init(_d, _time);
  alarm_time = _alarm_time;
  one_time = _one_time;
  ran_one_time = false;
  initted = true;
}

bool Alarm::on_alarm() {
  ASSERT(initted);
  if (ran_one_time)
    return false;
  run();
  if (time >= alarm_time) {
    time -= alarm_time;
    if (one_time) {
      ran_one_time = true;
    }
    return true;
  }
  return false;
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

#endif
