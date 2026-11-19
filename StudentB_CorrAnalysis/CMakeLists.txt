cmake_minimum_required(VERSION 3.20)
project(CorrAnalysisProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Статична бібліотека (Етап 1)
add_library(CorrAnalysisStatic STATIC src/CorrAnalysis.cpp)
target_include_directories(CorrAnalysisStatic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(TestStaticB app/main_static.cpp)
target_link_libraries(TestStaticB PRIVATE CorrAnalysisStatic)

# 2. Динамічна бібліотека (Етап 2)
add_library(CorrAnalysis SHARED src/CorrAnalysis.cpp)
target_compile_definitions(CorrAnalysis PRIVATE CORRANALYSIS_SHARED CORRANALYSIS_EXPORTS)
target_include_directories(CorrAnalysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
