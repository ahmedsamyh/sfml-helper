#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

struct Text_box {
  std::vector<std::string> texts{};
  sf::Vector2f pos{};
  sf::Vector2f size{}, actual_size{1280.f, 100.f};
  Data *d{nullptr};
  std::vector<std::string> text_buffer;
  int current_text_id{0};
  int current_char{0};
  int char_size{DEFAULT_CHAR_SIZE};
  Alarm char_alarm;
  const float side_padding{20.f};
  sf::Vector2f current_text_size{};

  Text_box(Data &_d, const sf::Vector2f &_pos = {},
           sf::Vector2f _size = {1280.f, 100.f})
      : pos(_pos) {
    d = &_d;
    set_size(_size);
    char_alarm.init(*d, 0.1f);
    texts.push_back(std::string());
    ///
  }

  void set_size(const sf::Vector2f &_size) {
    actual_size = _size;
    size = {};
  }

  void animate() {
    size.y += (actual_size.y - size.y) / 4.f;
    if (abs(size.y - actual_size.y) < 1.f) {
      size.y = actual_size.y;
      size.x += (actual_size.x - size.x) / 10.f;
    } else if (size.x < 10.f) {
      size.x += (actual_size.x - size.x) / 10.f;
    }
    if (abs(size.x - actual_size.x) < 1.f) {
      size.x = actual_size.x;
    }
  }

  void push_text() {
    current_text_size = d->get_text_size(texts.back(), char_size);
    if (current_text_size.x < size.x - side_padding) {
      texts.back().push_back(text_buffer.at(current_text_id).at(current_char));
      current_char++;
    } else {
      texts.push_back(std::string());
    }
  }

  bool text_fully_drawn() const {
    return texts.back() == text_buffer.at(current_text_id);
  }

  void update() {
    animate();
    ASSERT(0 <= current_text_id && current_text_id < text_buffer.size());

    if (!text_buffer.empty()) {
      if (current_char < text_buffer.at(current_text_id).size() &&
          char_alarm.on_alarm()) {
        push_text();
      }
      if (d->k_pressed(Key::Space)) {

        size_t current_text_size = text_buffer.at(current_text_id).size();
        // not fully drawn
        if (current_char < current_text_size) {
          while (!text_fully_drawn() && current_char < current_text_size) {
            push_text();
          }
        }
        // fully drawn
        else {
          if (current_text_id + 1 < text_buffer.size()) {
            current_text_id++;
            current_char = 0;
            texts.back().clear();
          }
        }
      }
    }
  }

  void draw() {
    //
    d->draw_rect(pos, size, TopCenter, sf::Color::Transparent, sf::Color::White,
                 2);

    float padding = 5.f;
    for (size_t i = 0; i < texts.size(); ++i) {
      auto &text = texts.at(i);
      if (!text.empty()) {
        d->draw_text(pos + sf::Vector2f{0.f, padding + float(i) * char_size +
                                                 float(i) * padding},
                     text, TopCenter, char_size);
        // d->draw_rect(pos, d->get_text_size(text, char_size), CenterCenter);
      }
    }
  }

  void add_text(const std::string &txt) { text_buffer.push_back(txt); }
};

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 1, "sfml-helper");

  Text_box tx(d, d.ss() / 2.f, {float(d.width) - 1.f, 100.f});
  tx.add_text("Hello! Niggers of planet Earth.");
  tx.add_text("This is the second text!");
  tx.add_text(
      "Lorem Ipsum is simply dummy text of the printing and typesetting "
      "industry. Lorem Ipsum has been the industry's standard dummy text "
      "ever "
      "since the 1500s, when an unknown printer took a galley of type and "
      "scrambled it to make a type specimen book. It has survived not only "
      "five centuries, but also the leap into electronic typesetting, "
      "remaining essentially unchanged. It was popularised in the 1960s "
      "with "
      "the release of Letraset sheets containing Lorem Ipsum passages, and "
      "more recently with desktop publishing software like Aldus PageMaker "
      "including versions of Lorem Ipsum");

  UI ui(d);

  // game loop
  while (d.win.isOpen()) {
    // calculate delta time
    float delta = d.calc_delta();

    // update window title
    d.update_title();

    // event loop
    sf::Event e;
    d.update_mouse();
    d.update_key();

    while (d.win.pollEvent(e)) {
      d.handle_close(e);
      d.update_mouse_event(e);
      d.update_key_event(e);
    }

    // clear
    d.clear();

    // update
    tx.update();

    // draw
    tx.draw();

    ui.begin({});

    // ui.text(std::format("text = {}", tx.texts.back()));
    // ui.text(std::format("pos = {}, {}", tx.pos.x, tx.pos.y));
    // ui.text(std::format("size = {}, {}", tx.size.x, tx.size.y));
    // ui.text(std::format("actual_size = {}, {}", tx.actual_size.x,
    //                     tx.actual_size.y));
    // ui.text(std::format("current_text_id = {}", tx.current_text_id));
    // ui.text(std::format("current_char = {}", tx.current_char));
    // if (tx.current_text_id >= 0)
    //   ui.text(std::format("text_buffer[tx.current_text_id].size() = {}",
    //                       tx.text_buffer[tx.current_text_id].size()));
    // ui.text(std::format("text size = {}, {}",
    //                     d.get_text_size(tx.texts.back(), tx.char_size).x,
    //                     d.get_text_size(tx.texts.back(), tx.char_size).y));

    ui.end();

    // display
    d.display();
  }

  return 0;
}
