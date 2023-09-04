# SFML-Helper

Helper functions for use in SFML applications.

all the functions are in [sfml-helper.hpp](./include/sfml-helper.hpp) as a [single-header only](https://github.com/nothings/stb) format.

## Quick Start
```console
> premake5 vs2022
> msbuild -p:configuration=Debug build\sfml-helper.sln
> bin\Debug\sfml-helper.exe

```
Note: You can also open the VS solution file (.sln) directly and build with Visual Studio<s>(If you want to wait eternally for it to open)</s> and build it.

## Example
```c++
#define SFML_HELPER_IMPLEMENTATION
#include <sfml-helper.hpp>

int main(int argc, char *argv[]) {
  //  global
  Data d;
  d.init(1280, 720, 2, "sfml-helper");

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

    // draw

    // display
    d.display();
  }

  return 0;
}

```


## Dependencies
- [premake5 (version 5.0.0-beta2 and up)](https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip)
- [Visual Studio 17.4.4 (2022)](https://visualstudio.microsoft.com/vs/community/) with (Desktop development with C++ Workload Installed)
