Exectue the following commands to build raylib.
```
cmake -S. -B_build -DCMAKE_INSTALL_PREFIX=<raylib-install-dir> -DBUILD_SHARED_LIBS=ON
cmake --build _build
cmake --install _build
```
> It is important to set -DBUILD_SHARED_LIBS=ON and not use the external glfw library.

Exectue  the following commands to build the game.
```
cmake -S. -B_build -DRAYLIB_INSTALL_DIR=<raylib-install-dir>
cmake --build _build
```

Run the game with the following command:
```
./_build/music
```