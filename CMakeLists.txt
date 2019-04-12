cmake_minimum_required(VERSION 3.13)
project(BloonsTDS)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-g -Wall)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)

file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE sources_imgui "lib/imgui/*")

add_executable(BloonsTDS ${sources} ${sources_imgui})
set_target_properties(BloonsTDS PROPERTIES OUTPUT_NAME "BloonsTDS.out")

target_include_directories(BloonsTDS PUBLIC "include/" "lib/" "lib/imgui/")
target_link_libraries(BloonsTDS sfml-graphics sfml-window sfml-audio sfml-network sfml-system GL stdc++fs)