#define NO_WARNING
#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 2, "sfml-helper");

  sf::Shader *shader = new sf::Shader();
  sf::Sprite spr;
  spr.setTexture(d.res_man.get_texture("res/gfx/momo.png"));
  spr.setOrigin(spr.getLocalBounds().width / 2.f,
                spr.getLocalBounds().height / 2.f);

  auto reload_shader_and_get_string = [](const std::string &filename) {
    if (chunk_exists_in_data(filename)) {
      remove_chunk_from_data(filename);
    }
    write_shader_to_data(filename);
    Data_chunk shader_ch;
    read_shader_from_data(shader_ch, filename);
    std::string shader_str;
    shader_str = shader_ch.data;
    shader_str.resize(shader_ch.data_size);
    shader_ch.free();
    return shader_str;
  };

  if (!shader->loadFromMemory(
          reload_shader_and_get_string("res/shaders/shader.frag"),
          sf::Shader::Type::Fragment))
    return 1;

  shader->setUniform("texture", sf::Shader::CurrentTexture);

  Timer t(d);

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
    if (d.k_pressed(Key::F1)) {
      sf::Shader *new_shader = new sf::Shader();

      if (!new_shader->loadFromMemory(
              reload_shader_and_get_string("res/shaders/shader.frag"),
              sf::Shader::Type::Fragment)) {
        // could not load new_shader
        delete new_shader;
        std::cout << "Could not load new shader!\n";
      } else {
        delete shader;
        shader = new_shader;

        std::cout << "Loaded new shader!\n";
      }
    }

    t.run();
    spr.setPosition(d.mpos());
    shader->setUniform("time", t.s());

    // draw
    d.draw(spr, shader);

    // display
    d.display();
  }

  if (shader)
    delete shader;

  return 0;
}
