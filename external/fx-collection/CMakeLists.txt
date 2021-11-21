cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    ha-fx-collection
    GIT_REPOSITORY ${HA_GIT_REPOSITORY_URL}/hansen-audio/fx-collection.git
    GIT_TAG master
)

FetchContent_MakeAvailable(ha-fx-collection)
