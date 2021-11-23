cmake_minimum_required(VERSION 3.15.0)

project(fx-collection-bench)

add_subdirectory(external)

add_executable(fx-collection-bench
    source/main.cpp
)

target_link_libraries(fx-collection-bench
    PRIVATE
        fx-collection
        fx-collection-rs
        nanobench
)