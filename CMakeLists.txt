cmake_minimum_required(VERSION 3.10)

project(DecodificadorPRT7)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(DecodificadorPRT7
    main.cpp
    TramaLoad.cpp
    TramaMap.cpp
    RotorDeMapeo.cpp
    ListaDeCarga.cpp
)

if(WIN32)
    target_compile_definitions(DecodificadorPRT7 PRIVATE _WIN32)
endif()

install(TARGETS DecodificadorPRT7 DESTINATION bin)