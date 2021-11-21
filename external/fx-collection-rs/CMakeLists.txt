cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    fx-collection-rs
    GIT_REPOSITORY ${HA_GIT_REPOSITORY_URL}/hansen-audio/fx-collection-rs.git
    GIT_TAG main
)

FetchContent_GetProperties(fx-collection-rs)
if(NOT fx-collection-rs_POPULATED)
    FetchContent_Populate(fx-collection-rs)
endif()

corrosion_import_crate(MANIFEST_PATH ${fx-collection-rs_SOURCE_DIR}/Cargo.toml)

target_include_directories(fx-collection-rs 
    INTERFACE 
        ${fx-collection-rs_SOURCE_DIR}
)