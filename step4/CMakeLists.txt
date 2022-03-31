cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Step4Exam
    VERSION 0.0.1
    LANGUAGES CXX
)

add_executable(Step3Exam CodeChallenge.cpp)

set_target_properties(Step3Exam PROPERTIES 
  CXX_STANDARD 11 
  OUTPUT_NAME "Step3Exam"
)
