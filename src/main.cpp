#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

struct UI {
  struct Layout {
    enum class Kind { Horz, Vert };
    Kind kind;
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Vector2f padding;
    Layout();

    sf::Vector2f available_pos() const;
    void push_widget(const sf::Vector2f &size);
  };

  int active_id;
  std::vector<Layout> layouts;
  Data *d_ptr;

  UI(Data &d);

  Layout *top_layout();
  void begin_layout(Layout::Kind kind = Layout::Kind::Vert);
  void end_layout();

  void begin(const sf::Vector2f &pos, Layout::Kind kind = Layout::Kind::Vert);
  bool btn(size_t id, const std::string &str, size_t char_size = 16,
           sf::Color col = sf::Color::White);
  void end();
};

UI::UI(Data &d) : active_id(-1) { d_ptr = &d; }

UI::Layout *UI::top_layout() {
  if (layouts.empty())
    return nullptr;
  return &layouts.back();
}

void UI::begin_layout(Layout::Kind kind) {
  ///
  Layout *prev = top_layout();
  ASSERT(prev != nullptr);

  Layout next;
  next.kind = kind;
  next.pos = prev->available_pos();
  layouts.push_back(next);
}

void UI::end_layout() {
  ///

  Layout child = layouts.back();
  layouts.pop_back();
  Layout *parent = top_layout();
  ASSERT(parent != nullptr);
  parent->push_widget(child.size);
}

void UI::begin(const sf::Vector2f &pos, Layout::Kind kind) {
  ///
  layout l;
  l.pos = pos;
  l.kind = kind;
  layouts.push_back(layout);
}

bool UI::btn(size_t id, const std::string &str, size_t char_size,
             sf::Color col) {
  ///
  Layout *l = top_layout();
  ASSERT(l != nullptr);

  const sf::Vector2f pos = l->available_pos();
  const sf::Vector2f size = {char_size * str.size(), char_size};
  bool click = false;
  bool hovering =
      // bool hovering;
      if (active_id == id) {}
  else {
    if ()
  }
}

void UI::end() {
  ///
}

UI::Layout::Layout() : pos(0.f, 0.f), size(0.f, 0.f), padding(4.f, 4.f) {}

sf::Vector2f UI::Layout::available_pos() const {
  switch (kind) {
  case Kind::Horz:
    return sf::Vector2f(pos.x + size.x + padding.x, pos.y);
    break;
  case Kind::Vert:
    return sf::Vector2f(pos.x, pos.y + size.y + padding.y);
    break;
  default:
    ASSERT(0);
    break;
  };
}

void UI::Layout::push_widget(const sf::Vector2f &_size) {
  switch (kind) {
  case Kind::Horz:
    size.x += _size.x + padding.x;
    size.y = std::max(size.y, _size.y);
    break;
  case Kind::Vert:
    size.x = std::max(size.x, _size.x);
    size.y += _size.y + padding.y;
    break;
  default:
    ASSERT(0);
    break;
  }
}

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

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

    // draw

    // display
    d.display();
  }

  return 0;
}
