project(nativelib_pb11)
cmake_minimum_required(VERSION 3.6)

include(${CMAKE_SOURCE_DIR}/_conan/conanbuildinfo.cmake)


if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
    find_package(PythonInterp)
    find_package(PythonLibs)

    set(Python_INCLUDE_DIRS ${PYTHON_INCLUDE_DIR})
    set(Python_LIBRARY_RELEASE ${PYTHON_LIBRARY})
else()
    set(Python_FIND_REGISTRY NEVER)
    find_package(Python COMPONENTS Development)

endif()

message("PYTHON INC DIR: ${Python_INCLUDE_DIRS}")
message("PYTHON LIB : ${Python_LIBRARY_RELEASE}")


add_subdirectory(src/lib)
# add_subdirectory(src/app)

