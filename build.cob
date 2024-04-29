set_compiler /usr/bin/gcc
set_target pixab
set_main main.c
add_compiler_opt -lraylib
add_compiler_opt -O3
add_compiler_opt -lm
strip_target
