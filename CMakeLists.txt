cmake_minimum_required(VERSION 3.20)
project(snake_game)


set(CMAKE_CXX_STANDARD 23)

find_package(SFML COMPONENTS graphics window system REQUIRED)
find_package(CURL REQUIRED)

set(JSON_INCLUDE_DIR /home/osa/c_libs/json/include)

include_directories(${CURL_INCLUDE_DIRS})

# Set the directory containing resource files
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Copy resources to build directory
file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_BINARY_DIR})


set(CONFIG_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES "src/*.cpp")

add_executable(snake_game 
main.cpp
${SOURCES}
)

target_link_libraries(snake_game PRIVATE sfml-graphics sfml-window sfml-system ${CURL_LIBRARIES})
target_include_directories(snake_game PRIVATE ${JSON_INCLUDE_DIR})

