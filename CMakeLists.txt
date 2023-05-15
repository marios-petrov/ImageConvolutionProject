cmake_minimum_required(VERSION 3.24)
project(ImageConvolutionProject C)

set(CMAKE_C_STANDARD 99)

add_executable(image_processing
        main.c
        kernels.c
        kernels.h
        image_io.c
        image_io.h kernels.c kernels.h)

target_include_directories(image_processing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

