add_executable(${App} main.cpp)

add_custom_command(TARGET ${App} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${PROJECT_SOURCE_DIR}/resources/fonts/Cascadia.ttf
                       $<TARGET_FILE_DIR:${App}>
                   )