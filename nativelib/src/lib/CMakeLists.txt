Python_add_library(mylib MODULE WITH_SOABI mylib.cpp mylib.h)


target_include_directories(mylib PRIVATE 
	${Python_INCLUDE_DIRS})

target_link_libraries(mylib PRIVATE
    ${Python_LIBRARY_RELEASE}
    Eigen3::Eigen
    pybind11::pybind11
    )
set_target_properties(mylib PROPERTIES DEBUG_POSTFIX _d)

if(UNIX)
#    set_target_properties(mylib PROPERTIES PREFIX "")
elseif(WIN32)
    set_target_properties(mylib PROPERTIES SUFFIX .pyd)
endif()

add_custom_command(TARGET mylib POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:mylib> ${CMAKE_SOURCE_DIR}/../pylib/$<TARGET_FILE_NAME:mylib>
)

