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

## Dependencies
- [premake5 (version 5.0.0-beta2 and up)](https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip)
- [Visual Studio 17.4.4 (2022)](https://visualstudio.microsoft.com/vs/community/) with (Desktop development with C++ Workload Installed)
