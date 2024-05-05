cmake_minimum_required(VERSION 3.20)
project(first_project)


set(CMAKE_CXX_STANDARD 23)

find_package(SFML COMPONENTS graphics window system REQUIRED)

# Set the directory containing resource files
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Copy resources to build directory
file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")

add_executable(first_project 
main.cpp
${SOURCES}
)

target_link_libraries(first_project PRIVATE sfml-graphics sfml-window sfml-system)

