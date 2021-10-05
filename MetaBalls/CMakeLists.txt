# CMakeList.txt : CMake project for MetaBalls, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (MetaBalls "MetaBalls.c" "MetaBalls.h" "source/window.c" "source/load.c" "source/shader.c")
target_link_libraries(MetaBalls OpenGL32.lib winmm.lib)
target_include_directories(MetaBalls PRIVATE "include")

# TODO: Add tests and install targets if needed.
