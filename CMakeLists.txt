cmake_minimum_required(VERSION 3.15)

project(cista)

add_executable(cista-example cista.h main.cpp)
target_compile_features(cista-example PRIVATE cxx_std_17)

set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT cista-example)