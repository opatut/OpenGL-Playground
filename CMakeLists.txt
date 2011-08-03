cmake_minimum_required(VERSION 2.8.0)

project(Playground)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/")

find_package(SFML 2 COMPONENTS window graphics REQUIRED)
find_package(OpenGL)
find_package(Noise)

add_definitions(-Wall -Wextra -g -pedantic -fPIC -std=c++0x)
set(CMAKE_BUILD_TYPE "Debug")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(
	"${CMAKE_SOURCE_DIR}/src/"
	${SFML_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${NOISE_INCLUDE_DIR}
)

aux_source_directory(src/ sources)
include_directories(src/)

add_executable(playground
	${sources}
)

target_link_libraries(playground
	${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${NOISE_LIBRARY}
)

