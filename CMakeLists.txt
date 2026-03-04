cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(RGB_LED)

target_include_directories(app PRIVATE include)

target_sources(app PRIVATE 
    src/main.c
    src/peripheral_vals.c
)