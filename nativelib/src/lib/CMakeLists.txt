add_library(mylib SHARED mylib.cpp mylib.h)

target_include_directories(mylib PRIVATE 
	${CONAN_INCLUDE_DIRS} 
	${Python_INCLUDE_DIRS})

target_link_libraries(mylib PRIVATE ${Python_LIBRARY_RELEASE})
set_target_properties(mylib PROPERTIES SUFFIX .pyd)
set_target_properties(mylib PROPERTIES DEBUG_POSTFIX _d)

add_custom_command(TARGET mylib POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:mylib> ${CMAKE_SOURCE_DIR}/../pylib/$<TARGET_FILE_NAME:mylib>
)

