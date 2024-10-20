cmake_minimum_required(VERSION 3.12)

project(Notepad VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: Change this
file(GLOB_RECURSE Notepad_SRC CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp")

add_executable(Notepad ${Notepad_SRC})

target_include_directories(Notepad PRIVATE ${CMAKE_SOURCE_DIR}/src/app)
target_include_directories(Notepad PRIVATE ${CMAKE_SOURCE_DIR}/src/ui/)

target_link_libraries(Notepad PRIVATE X11 GL)
