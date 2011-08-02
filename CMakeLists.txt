cmake_minimum_required(VERSION 2.8.0)

project(GL)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/")

find_package(SFML 2 COMPONENTS window REQUIRED)

add_definitions(-Wall -Wextra -g -pedantic -fPIC -std=c++0x)
set(CMAKE_BUILD_TYPE "Debug")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(
	"${CMAKE_SOURCE_DIR}/src/"
	${SFML_INCLUDE_DIRS}
)

aux_source_directory(src/ sources)
include_directories(src/)

add_executable(GL
	${sources}
)

target_link_libraries(GL
	${SFML_LIBRARIES}
    GLU
    GLw
    GLEW
    noise
)

