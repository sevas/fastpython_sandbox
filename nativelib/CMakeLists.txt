cmake_minimum_required(VERSION 3.19)

project(nativelib_pb11)
set(CMAKE_CXX_STANDARD 17)

message(">>>>>>> ${CONDA_ENV_NAME}")


list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

include(cmake/configure_python.cmake)
include(cmake/conan.cmake)

conan_cmake_configure(
    REQUIRES
        pybind11/2.9.2
        eigen/3.3.7
    GENERATORS
        CMakeDeps)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

find_package(pybind11 CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)




add_subdirectory(src/lib)
# add_subdirectory(src/app)

