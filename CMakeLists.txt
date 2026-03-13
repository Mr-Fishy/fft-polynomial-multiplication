cmake_minimum_required(VERSION 3.10..4.2.3)

project(
    fft-polynomial-multiplication
    
    VERSION 0.1.0
    LANGUAGES C CXX
)

add_executable(
    ${PROJECT_NAME}

    src/MultiplyPolynomials.cpp
    main.cpp

    include/MultiplyPolynomials.hpp
)

target_include_directories(
    ${PROJECT_NAME}

    PRIVATE include
)
