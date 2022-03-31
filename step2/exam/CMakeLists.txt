cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Step2Exam
    VERSION 0.0.1
    LANGUAGES CXX
)

add_library(step2_lib STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Job.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Programmer.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Pilot.cpp
)
target_include_directories(step2_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)

add_executable(Step2Exam src/main.cpp)

set_target_properties(Step2Exam PROPERTIES 
  CXX_STANDARD 11 
  OUTPUT_NAME "Step2Exam"
)

target_link_libraries(Step2Exam PRIVATE step2_lib)
