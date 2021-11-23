cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG v4.3.6
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(nanobench)
