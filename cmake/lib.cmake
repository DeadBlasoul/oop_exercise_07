set(Lib_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS})

add_subdirectory(src)

target_include_directories(${Lib} PUBLIC ${Lib_INCLUDE_DIRS})