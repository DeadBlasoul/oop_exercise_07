cmake_minimum_required (VERSION 3.13)

set(ExerciseNumber 07)
set(ProjectName oop_exercise_${ExerciseNumber})
project(${ProjectName})

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(VERBOSE ON)

include(config)
include(lib)
include(app)
include(tests)
