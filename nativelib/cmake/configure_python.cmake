

if(CONDA_ENV_NAME)
    message(STATUS "Configuring with conda env ${CONDA_ENV_NAME}")

    execute_process(
        COMMAND conda run -n py311 python -c "import sys; print(sys.prefix)"
        OUTPUT_VARIABLE CONDA_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE

    )
    execute_process(
            COMMAND conda run -n py311 python -c "import sys; print(sys.executable)"
            OUTPUT_VARIABLE Python_EXECUTABLE
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )


    message(STATUS "${CONDA_PREFIX}")
    set(Python_ROOT_DIR ${CONDA_PREFIX})
else()
    message(STATUS "Using first python found in PATH")
endif()


if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
    find_package(PythonInterp)
    find_package(PythonLibs)

    set(Python_INCLUDE_DIRS ${PYTHON_INCLUDE_DIR})
    set(Python_LIBRARY_RELEASE ${PYTHON_LIBRARY})
else()
    set(Python_FIND_REGISTRY NEVER)
    find_package(Python COMPONENTS Development Interpreter)

endif()

message("PYTHON INC DIR: ${Python_INCLUDE_DIRS}")
message("PYTHON LIB : ${Python_LIBRARY_RELEASE}")