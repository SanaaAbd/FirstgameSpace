set_compiler /usr/lib/mingw64-toolchain/bin/x86_64-w64-mingw32-gcc
set_target pixab.exe
set_main main.c
add_compiler_opt -L.
add_compiler_opt -lraylib
add_compiler_opt -O3
add_compiler_opt -lm
strip_target
