project(nativelib_pb11)
cmake_minimum_required(VERSION 3.6)

include(${CMAKE_SOURCE_DIR}/_conan/conanbuildinfo.cmake)

set(Python_FIND_REGISTRY NEVER)
find_package(Python COMPONENTS Development)

message("PYTHON INC DIR: ${Python_INCLUDE_DIRS}")

add_subdirectory(src/lib)
# add_subdirectory(src/app)

