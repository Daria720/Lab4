cmake_minimum_required(VERSION 3.20)
project(StudentB_ExplicitClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ExplicitClientB main.cpp)

add_custom_command(TARGET ExplicitClientB POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/StatAnalysis.dll"
    "$<TARGET_FILE_DIR:ExplicitClientB>"
)
