cmake_minimum_required(VERSION 2.4.3)
project(block_application)
cmake_policy(SET CMP0022 NEW)

set(NUM_CORES 16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_PARALLEL_LEVEL ${NUM_CORES} CACHE STRING "Número de jobs paralelos" FORCE)

# Engine
add_subdirectory(block_engine)

target_include_directories(block_engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Application
add_subdirectory(block_application)

set_property(GLOBAL PROPERTY JOB_POOLS link_pool=${NUM_CORES})

set_property(TARGET block_application PROPERTY JOB_POOL_LINK link_pool)