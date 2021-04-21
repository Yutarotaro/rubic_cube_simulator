cmake_minimum_required(VERSION 3.11)
project(main CXX)
SET( CMAKE_CXX_COMPILER /usr/bin/clang++ )

add_definitions( -std=c++17 -Wall )



find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(main main.cpp )
set(HEADERS
    # main.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/config.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lib.hpp
)
include_directories(${OPENGL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/local/include/eigen3)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/include)
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )



