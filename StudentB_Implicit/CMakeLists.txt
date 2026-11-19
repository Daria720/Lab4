cmake_minimum_required(VERSION 3.20)
project(StudentB_ImplicitClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ImplicitClientB main.cpp)
target_compile_definitions(ImplicitClientB PRIVATE STATANALYSIS_SHARED)
target_include_directories(ImplicitClientB PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/StatAnalysis/include)
target_link_libraries(ImplicitClientB PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/StatAnalysis/lib/StatAnalysis.lib)

add_custom_command(TARGET ImplicitClientB POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/StatAnalysis/bin/StatAnalysis.dll"
    "$<TARGET_FILE_DIR:ImplicitClientB>"
)
