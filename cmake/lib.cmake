set(Lib_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS})

add_subdirectory(src)

target_link_libraries(${Lib} PUBLIC SDL2-static SDL2main)
target_include_directories(${Lib} PUBLIC
                           ${Lib_INCLUDE_DIRS}
                           ${SDL2_INCLUDE_DIRS})