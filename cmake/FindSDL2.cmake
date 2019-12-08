add_subdirectory(${PROJECT_THIRD_PARTY_FOLDER}/SDL2)

foreach(SDL2_LIB SDL2 SDL2main SDL2-static)
    set_target_properties(${SDL2_LIB} PROPERTIES
                          FOLDER SDL2)
endforeach()