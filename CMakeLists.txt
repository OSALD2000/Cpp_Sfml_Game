cmake_minimum_required(VERSION 3.20)
project(snake_game)


set(CMAKE_CXX_STANDARD 23)

find_package(SFML COMPONENTS graphics window system REQUIRED)

# Set the directory containing resource files
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Copy resources to build directory
file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_BINARY_DIR})

set(CONFIG_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONFIG_FILE_NAME keys.cfg)

configure_file(${CONFIG_FILES_DIR}/${CONFIG_FILE_NAME} ${CONFIG_FILE_NAME} COPYONLY)


file(GLOB SOURCES "src/*.cpp")

add_executable(snake_game 
main.cpp
${SOURCES}
)

target_link_libraries(snake_game PRIVATE sfml-graphics sfml-window sfml-system)

