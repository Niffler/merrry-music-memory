EMCC = emcc
SOURCES = src/background.c src/card.c src/game.c src/music.c src/main.c

# -Os                        # size optimization
# -O2                        # optimization level 2, if used, also set --memory-init-file 0
# -s USE_GLFW=3              # Use glfw3 library (context/input management)
# -s ALLOW_MEMORY_GROWTH=1   # to allow memory resizing -> WARNING: Audio buffers could FAIL!
# -s TOTAL_MEMORY=16777216   # to specify heap memory size (default = 16MB)
# -s USE_PTHREADS=1          # multithreading support
# -s WASM=0                  # disable Web Assembly, emitted by default
# -s EMTERPRETIFY=1          # enable emscripten code interpreter (very slow)
# -s EMTERPRETIFY_ASYNC=1    # support synchronous loops by emterpreter
# -s FORCE_FILESYSTEM=1      # force filesystem to load/save files data
# -s ASSERTIONS=1            # enable runtime checks for common memory allocation errors (-O1 and above turn it off)
# --profiling                # include information for code profiling
# --memory-init-file 0       # to avoid an external memory initialization code file (.mem)
# --preload-file resources   # specify a resources folder for data compilation

# emflags2 works for firefox; not sure if use sdl 2 is really necessary

EMFLAGS2 = -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy --shell-file src/minimal_shell.html -I/home/leo/Documents/OSF/raylib/_install_web/include

EMFLAGS1 = -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s TOTAL_MEMORY=268435456 --shell-file src/minimal_shell.html -I/home/leo/Documents/OSF/raylib/_install_web/include

EMFLAGS = -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1 -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy --shell-file src/shell.html -Isrc -I/home/leo/Documents/OSF/raylib/_install_web/include

build: $(SOURCES)
	$(EMCC) $(EMFLAGS1) --preload-file resources@resources $(SOURCES) -DPLATFORM_WEB=1 /home/leo/Documents/OSF/raylib/_install_web/lib/libraylib.bc -o music.html
