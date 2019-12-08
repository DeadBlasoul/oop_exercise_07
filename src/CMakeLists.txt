file(GLOB_RECURSE Lib_SRC_FILES
    NAME "*.h" "*.hpp" "*.c" "*.cpp")

add_library(${Lib} ${Lib_SRC_FILES})