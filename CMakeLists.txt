cmake_minimum_required(VERSION 3.10)

project(EdgeKiller)

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.10.4)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(EdgeKiller WIN32 main.cpp)
target_link_libraries(EdgeKiller nlohmann_json::nlohmann_json)
configure_file(config.json Release\\config.json COPYONLY)
configure_file(config.json Debug\\config.json COPYONLY)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")