cmake_minimum_required(VERSION 3.15.0)

if(NOT HA_GIT_REPOSITORY_URL)
    set(HA_GIT_REPOSITORY_URL "https://github.com")
endif()

add_subdirectory(corrosion)
add_subdirectory(fx-collection)
add_subdirectory(fx-collection-rs)#
add_subdirectory(nanobench)