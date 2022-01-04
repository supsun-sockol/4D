cmake_minimum_required(VERSION 3.5)

project(4D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS graphics CONFIG REQUIRED)

add_executable(4D main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${SFML_ROOT}/include"
)


target_link_libraries(4D PUBLIC sfml-graphics)
